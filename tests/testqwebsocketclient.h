#ifndef TESTQWEBSOCKETCLIENT_H
#define TESTQWEBSOCKETCLIENT_H

#include <QtTest/QtTest>

class TestQWebSocketClient : public QObject
{
    Q_OBJECT

public:
    void setWebSocketServerParams(const QString &host, const quint16 &port, const QString &path);

private slots:
    void connectToHost();
    void disconnectFromHost();
    void ping();
    void writeTextMessage();

private:
    QString m_host;
    quint16 m_port;
    QString m_path;
};

#endif //TESTQWEBSOCKETCLIENT_H
