#ifndef JSONWEBSOCKET_H
#define JSONWEBSOCKET_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

namespace Mopidy {
    namespace Internal {

        /*
         * WebSocket to mopidy server
         */
        class JsonWebSocket : public QObject
        {
            Q_OBJECT

        public:
            JsonWebSocket(QObject *parent = 0);
            ~JsonWebSocket();

            bool isConnected() const;

            // return request ID if not notification, else return 0
            int sendRequest(QJsonObject request, bool notification = false);

        public slots:
            void openSocket(const QString &host, const qint16 &port, const QString &path);
            void closeSocket();

        signals:
            void eventReceived(const QByteArray &rawMsg);
            void responseReceived(const int &id, const QJsonValue &result);
            void responseError(const int &code, const QString &message);

            void socketConnected();
            void socketDisconnected();
            void socketError(const int &code, const QString &message);

        private slots:
            // WebSocket
            void onSocketError(QAbstractSocket::SocketError error);
            // Json
            void parseRawDdata(const QString &rawData);

        private:
            // WebSocket
            QWebSocket m_wsclient;

            // IDs
            int m_lastId;
        };
    }
}

#endif // JSONWEBSOCKET_H
