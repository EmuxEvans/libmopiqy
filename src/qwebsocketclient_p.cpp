#include "qwebsocketclient_p.h"

#include <QUrl>

using namespace Mopidy::Internal;

QWebSocketClientPrivate::QWebSocketClientPrivate(QObject *parent) : QObject(parent)
{
    m_connected = false;

    // Initialize ASIO
    m_wsclient.init_asio();

    // We expect there to be a lot of errors, so suppress them
    m_wsclient.clear_access_channels(websocketpp::log::alevel::all);
    m_wsclient.clear_error_channels(websocketpp::log::elevel::all);

    // Register our handlers
    using websocketpp::lib::placeholders::_1;
    using websocketpp::lib::placeholders::_2;
    using websocketpp::lib::bind;
    m_wsclient.set_open_handler(bind(&QWebSocketClientPrivate::ws_on_open, this, ::_1));
    m_wsclient.set_close_handler(bind(&QWebSocketClientPrivate::ws_on_close, this, ::_1));
    m_wsclient.set_fail_handler(bind(&QWebSocketClientPrivate::ws_on_fail, this, ::_1));
    m_wsclient.set_message_handler(bind(&QWebSocketClientPrivate::ws_on_message, this, ::_1, ::_2));
    m_wsclient.set_pong_handler(bind(&QWebSocketClientPrivate::ws_on_pong, this, ::_1));
}

QWebSocketClientPrivate::~QWebSocketClientPrivate()
{
    disconnectFromHost();
    m_wsthread.join();
}

bool QWebSocketClientPrivate::connectToHost(const QString &host, const quint16 &port, const QString &path)
{
    // just in case...
    if(isConnected())
    {
        disconnectFromHost();
        m_wsthread.join();
    }

    QUrl url = QUrl::fromUserInput(host);
    url.setPort(port);
    url.setPath(path);

    if(!url.isValid()) return false;

    // create connection
    websocketpp::lib::error_code ec;
    wsclient::connection_ptr con = m_wsclient.get_connection(url.toString().toStdString().c_str(), ec);
    if (ec) {
        emit socket_error(ec.value(), QString::fromStdString(ec.message()));
        return false;
    }

    // get handle to be able to send message, good idea, isn't it ?
    m_wshandle = con->get_handle();

    // connect then run in thread
    m_wsclient.connect(con);
    m_wsthread = websocketpp::lib::thread(&wsclient::run, &m_wsclient);

    return true;
}

bool QWebSocketClientPrivate::isConnected() const
{
    return m_connected;
}

void QWebSocketClientPrivate::disconnectFromHost()
{
    if(m_connected)
    {
        websocketpp::lib::error_code ec;
        m_wsclient.close(m_wshandle, websocketpp::close::status::normal, "goodbye", ec);
        if(ec) {
            emit socket_error(ec.value(), QString::fromStdString(ec.message()));
        }
        m_connected = false;
    }
}

void QWebSocketClientPrivate::ping()
{
    websocketpp::lib::error_code ec;
    m_wsclient.ping(m_wshandle, "", ec);
    if(ec) {
        emit socket_error(ec.value(), QString::fromStdString(ec.message()));
        return;
    }
}

void QWebSocketClientPrivate::writeTextMessage(const QString &message)
{
    websocketpp::lib::error_code ec;
    m_wsclient.send(m_wshandle, message.toUtf8().data(), websocketpp::frame::opcode::text, ec);
    if(ec) {
        emit socket_error(ec.value(), QString::fromStdString(ec.message()));
        return;
    }
}


void QWebSocketClientPrivate::ws_on_open(websocketpp::connection_hdl hdl)
{
    Q_UNUSED(hdl)
    m_connected = true;
    emit socket_connected();
}

void QWebSocketClientPrivate::ws_on_close(websocketpp::connection_hdl hdl)
{
    Q_UNUSED(hdl)
    m_connected = false;
    emit socket_disconnected();
}

void QWebSocketClientPrivate::ws_on_fail(websocketpp::connection_hdl hdl)
{
    Q_UNUSED(hdl)
    emit socket_error(0, "Websocket connection fail");
}

void QWebSocketClientPrivate::ws_on_message(websocketpp::connection_hdl hdl, message_ptr msg)
{
    Q_UNUSED(hdl)
    emit textMessageReceived(QString::fromUtf8(msg->get_raw_payload().c_str()));
}

void QWebSocketClientPrivate::ws_on_pong(websocketpp::connection_hdl hdl)
{
    Q_UNUSED(hdl)
    emit pong();
}
