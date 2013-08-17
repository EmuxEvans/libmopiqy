#include "jsonwebsocket.h"
#include "qwebsocketclient.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include <limits>

using namespace Mopidy::Internal;

JsonWebSocket::JsonWebSocket(QObject *parent) : QObject(parent)
{
    m_lastId = 0;
    m_wsclient = new QWebSocketClient(this);

    connect(m_wsclient, &QWebSocketClient::connected, this, &JsonWebSocket::socketConnected);
    connect(m_wsclient, &QWebSocketClient::disconnected, this, &JsonWebSocket::socketDisconnected);
    connect(m_wsclient, &QWebSocketClient::textMessageReceived, this, &JsonWebSocket::parseRawDdata);
    connect(m_wsclient, SIGNAL(error(int,QString)), this, SIGNAL(socketError(int,QString)));
}

JsonWebSocket::~JsonWebSocket()
{
    closeSocket();
}

bool JsonWebSocket::isConnected() const
{
    return m_wsclient->isConnected();
}

int JsonWebSocket::sendRequest(QJsonObject request, bool notification)
{
    int id = 0;
    // update to JsonRpc
    request.insert("jsonrpc", QString("2.0"));

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

    m_wsclient->writeTextMessage(st2Send);

    // ...
    return id;
}

bool JsonWebSocket::openSocket(const QString &host, const qint16 &port, const QString &path)
{
    // just in case...
    if(isConnected()) closeSocket();

    // create connection
    return m_wsclient->connectToHost(host, port, path);
}

bool JsonWebSocket::closeSocket()
{
    return m_wsclient->disconnectFromHost();
}

void JsonWebSocket::parseRawDdata(const QString &rawData)
{
    // try to read json document
    QJsonParseError jpError;
    QJsonDocument jdoc = QJsonDocument::fromJson(rawData.toLatin1(), &jpError);
    if(jpError.error != QJsonParseError::NoError)
    {
        emit responseError(jpError.error, jpError.errorString());
        return;
    }

    QJsonObject rootObject = jdoc.object();

    // event or answer to request ?
    if(rootObject.contains("event"))
    {
        emit eventReceived(rawData.toLatin1());
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
