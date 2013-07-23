#ifndef JSONWEBSOCKET_H
#define JSONWEBSOCKET_H

#include <QObject>

// See https://bugreports.qt-project.org/browse/QTBUG-29331
#ifndef Q_MOC_RUN
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#endif //Q_MOC_RUN

namespace Mopidy {
    namespace Internal {

        typedef websocketpp::client<websocketpp::config::asio_client> wsclient;
        typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

        /*
         * WebSocket to mopidy server
         */
        class JsonWebSocket : public QObject
        {
            Q_OBJECT

        public:
            JsonWebSocket(QObject *parent = 0);

            bool isConnected() const;

            // return request ID if not notification, else return 0
            int sendRequest(QJsonObject request, bool notification = false);

        public slots:
            bool openSocket(const QString &host, const qint16 &port, const QString &path);
            void closeSocket();

        signals:
            void eventReceived(const QByteArray &rawMsg);
            void responseReceived(const int &id, const QJsonValue &result);
            void responseError(const int &code, const QString &message);

            void socketConnected();
            void socketDisconnected();
            void socketError(const int &code, const QString &message);

        private:
            // Json
            void parseRawDdata(const QByteArray &rawData);

            // websocketpp handlers
            void ws_on_open(websocketpp::connection_hdl hdl);
            void ws_on_close(websocketpp::connection_hdl hdl);
            void ws_on_fail(websocketpp::connection_hdl hdl);
            void ws_on_message(websocketpp::connection_hdl hdl, message_ptr msg);

        private:
            // WebSocket
            wsclient m_wsclient;
            websocketpp::lib::thread m_wsthread;
            websocketpp::connection_hdl m_wshandle;
            bool m_connected;

            // IDs
            int m_lastId;
        };
    }
}

#endif // JSONWEBSOCKET_H
