#ifndef QWEBSOCKETCLIENT_H
#define QWEBSOCKETCLIENT_H

#include <QObject>
#include <QTcpSocket>

namespace Mopidy {
    namespace Internal {
        class QWebSocketClient : public QObject
        {
            Q_OBJECT

        public:
            explicit QWebSocketClient(QObject *parent = 0);
            ~QWebSocketClient();

            void connectToHost(const QString &host, const quint16 &port = 80, const QString &path = "");
            bool isConnected() const;
            bool disconnectFromHost();

            void ping();

            void writeTextMessage(const QString &message);
            void writeBinaryMessage(const QByteArray &message);

        signals:
            void connected();
            void disconnected();
            void textMessageReceived(const QString &);
            void binaryMessageReceived(const QByteArray &);
            void pong();
            void error(int code, QString message);

        private slots:
            void onTcpError(QAbstractSocket::SocketError);
            void onTcpStateChanged(QAbstractSocket::SocketState);
            void onTcpReadyRead();

            void processWsConnecting(const QByteArray &tcpData);
            void processWsRead(const QByteArray &tcpData);
            void writeMessage(const QByteArray &data, bool sendAsText);

            void sendPong();

        private:
            QAbstractSocket::SocketState m_wsState;
            QTcpSocket *m_tcpSocket;
            QString m_currentHost;
            QString m_currentPath;
            quint16 m_currentPort;
            QByteArray m_currentSessionHSKey;
        };
    }
}

#endif //QWEBSOCKETCLIENT_H
