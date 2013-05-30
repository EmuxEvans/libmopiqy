#ifndef JSONWEBSOCKET_H
#define JSONWEBSOCKET_H

#include <QObject>
#include <QFuture>

#include <Poco/Net/WebSocket.h>
#include <Poco/Net/HTTPClientSession.h>

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

        private slots:
            void socketDataWatcher();

        private:
            // Json
            void parseRawDdata(const QByteArray &rawData);

        private:
            bool m_stopRequest;
            QFuture<void> m_futureSocketWatcher;

            // WebSocket
            Poco::Net::HTTPClientSession m_http_session;
            Poco::Net::WebSocket *m_ws;

            // IDs
            int m_lastId;
        };
    }
}

#endif // JSONWEBSOCKET_H
