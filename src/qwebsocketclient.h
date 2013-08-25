#ifndef QWEBSOCKETCLIENT_H
#define QWEBSOCKETCLIENT_H

#include <QObject>

namespace Mopidy {
namespace Internal {

class QWebSocketClientPrivate;

class QWebSocketClient : public QObject
{
    Q_OBJECT

public:
    explicit QWebSocketClient(QObject *parent = 0);
    ~QWebSocketClient();

    bool connectToHost(const QString &host, const quint16 &port = 80, const QString &path = QString(""));
    bool isConnected() const;
    void disconnectFromHost();

    void ping();

    void writeTextMessage(const QString &message);

signals:
    void connected();
    void disconnected();
    void textMessageReceived(const QString &);
    void pong();
    void error(int code, QString message);

private:
    QWebSocketClientPrivate *m_d;
};
}
}

#endif //QWEBSOCKETCLIENT_H
