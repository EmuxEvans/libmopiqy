#include "jsonwebsocket.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <limits>
#include <QUrl>
#include <QDebug>

using namespace Mopidy::Internal;

JsonWebSocket::JsonWebSocket(QObject *parent) : QObject(parent)
{
    m_connected = false;
    m_lastId = 0;

    // Initialize the Asio transport policy
    m_wsclient.init_asio();

    // remove logging things
    m_wsclient.clear_access_channels(websocketpp::log::alevel::all);
    m_wsclient.clear_error_channels(websocketpp::log::elevel::all);

    using websocketpp::lib::placeholders::_1;
    using websocketpp::lib::placeholders::_2;
    using websocketpp::lib::bind;
    m_wsclient.set_open_handler(bind(&JsonWebSocket::ws_on_open, this, ::_1));
    m_wsclient.set_close_handler(bind(&JsonWebSocket::ws_on_close, this, ::_1));
    m_wsclient.set_fail_handler(bind(&JsonWebSocket::ws_on_fail, this, ::_1));
    m_wsclient.set_message_handler(bind(&JsonWebSocket::ws_on_message, this, ::_1, ::_2));
}

bool JsonWebSocket::isConnected() const
{
    return m_connected;
}

int JsonWebSocket::sendRequest(QJsonObject request, bool notification)
{
    // update to JsonRpc
    request.insert("jsonrpc", QString("2.0"));

    int id = 0;
    if(!notification)
    {
        id = ++m_lastId;
        request.insert("id", id);

        // in case we reach int limit...
        if(m_lastId == std::numeric_limits<int>::max()) m_lastId = 0;
    }

    /*
     * Send to socket
     */
    QJsonDocument jsDoc(request);
    QString st2Send = jsDoc.toJson(QJsonDocument::Compact);
    m_wsclient.send(m_wshandle, st2Send.toStdString(), websocketpp::frame::opcode::text);

    // ...
    return id;
}

bool JsonWebSocket::openSocket(const QString &host, const qint16 &port, const QString &path)
{
    // just in case...
    if(isConnected())
    {
        closeSocket();
        m_wsthread.join();
    }

    QUrl url;
    url.setScheme("http");
    url.setHost(host);
    url.setPort(port);
    url.setPath(path);

    // create connection
    websocketpp::lib::error_code ec;
    wsclient::connection_ptr con = m_wsclient.get_connection(url.toString().toStdString().c_str(), ec);
    if (ec) {
        emit socketError(ec.value(), QString::fromStdString(ec.message()));
        return false;
    }

    // get handle to be able to send message, good idea, isn't it ?
    m_wshandle = con->get_handle();

    // connect then run in thread
    m_wsclient.connect(con);
    m_wsthread = websocketpp::lib::thread(&wsclient::run, &m_wsclient);

    return true;
}

void JsonWebSocket::closeSocket()
{
    websocketpp::lib::error_code ec;
    m_wsclient.close(m_wshandle, websocketpp::close::status::normal, "goodbye", ec);
    if(ec) {
        emit socketError(ec.value(), QString::fromStdString(ec.message()));
        return;
    }
    m_connected = false;

    emit socketDisconnected();
}

void JsonWebSocket::parseRawDdata(const QByteArray &rawData)
{
    // try to read json document
    QJsonParseError jpError;
    QJsonDocument jdoc = QJsonDocument::fromJson(rawData, &jpError);
    if(jpError.error != QJsonParseError::NoError)
    {
        emit responseError(jpError.error, jpError.errorString());
        return;
    }

    QJsonObject rootObject = jdoc.object();

    // event or answer to request ?
    if(rootObject.contains("event"))
    {
        emit eventReceived(rawData);
    }
    else
    {
        if(rootObject.contains("id") && rootObject.contains("jsonrpc"))
        {
            // we only use int id
            if(rootObject.value("id").type() == QJsonValue::String) return;

            int id = rootObject.value("id").toDouble();

            // error ?
            if(rootObject.contains("error"))
            {
                QJsonObject errObj = rootObject.value("error").toObject();

                QString errStr;
                if(errObj.contains("data"))
                    errStr = errObj.value("data").toString();

                if(errObj.contains("message"))
                    errStr += ", message: " + errObj.value("message").toString();

                emit responseError(errObj.value("code").toDouble(), errStr);
                return;
            }
            else
            {
                emit responseReceived(id, rootObject.value("result"));
            }
        }
        else
        {
            emit responseError(-1, QObject::tr("Neither a JsonRpc answer not an event..."));
            return;
        }
    }
}

void JsonWebSocket::ws_on_open(websocketpp::connection_hdl hdl)
{
    Q_UNUSED(hdl)
    m_connected = true;
    emit socketConnected();
}

void JsonWebSocket::ws_on_close(websocketpp::connection_hdl hdl)
{
    Q_UNUSED(hdl)
    m_connected = false;
    emit socketDisconnected();
}

void JsonWebSocket::ws_on_fail(websocketpp::connection_hdl hdl)
{
    Q_UNUSED(hdl)
    m_connected = false;
    emit socketError(0, "Websocket connection fail");
}

void JsonWebSocket::ws_on_message(websocketpp::connection_hdl hdl, message_ptr msg)
{
    Q_UNUSED(hdl)
    parseRawDdata(msg->get_raw_payload().c_str());
}
