#ifndef QWEBSOCKETCLIENT_P_H
#define QWEBSOCKETCLIENT_P_H

#include <QObject>

// See https://bugreports.qt-project.org/browse/QTBUG-29331
#ifndef Q_MOC_RUN
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#endif //Q_MOC_RUN

typedef websocketpp::client<websocketpp::config::asio_client> wsclient;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

namespace Mopidy {
namespace Internal {

class QWebSocketClientPrivate : public QObject
{
    Q_OBJECT

public:
    explicit QWebSocketClientPrivate(QObject *parent = 0);
    ~QWebSocketClientPrivate();

    bool connectToHost(const QString &host, const quint16 &port = 80, const QString &path = QString(""));
    bool isConnected() const;
    void disconnectFromHost();

    void ping();

    void writeTextMessage(const QString &message);

signals:
    void socket_connected();
    void socket_disconnected();
    void socket_error(int code, QString message);
    void textMessageReceived(const QString &);
    void pong();

private:
    void ws_on_open(websocketpp::connection_hdl hdl);
    void ws_on_close(websocketpp::connection_hdl hdl);
    void ws_on_fail(websocketpp::connection_hdl hdl);
    void ws_on_message(websocketpp::connection_hdl hdl, message_ptr msg);
    void ws_on_pong(websocketpp::connection_hdl hdl);

private:
    wsclient m_wsclient;
    websocketpp::lib::thread m_wsthread;
    websocketpp::connection_hdl m_wshandle;
    bool m_connected;
};
}
}

#endif //QWEBSOCKETCLIENT_P_H
