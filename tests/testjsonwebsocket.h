#ifndef TESTJSONWEBSOCKET_H
#define TESTJSONWEBSOCKET_H

#include <QtTest/QtTest>

class TestJsonWebSocket : public QObject
{
    Q_OBJECT

private slots:
    void isConnectedTrue();
    void isConnectedFalse();
    void sendRequest();
    void openSocketValid();
    void openSocketInvalid();

//signals:
//    void eventReceived(const QByteArray &rawMsg);
//    void responseReceived(const int &id, const QJsonValue &result);
//    void responseError(const int &code, const QString &message);

//    void socketConnected();
//    void socketDisconnected();
//    void socketError(const int &code, const QString &message);
};

#endif //TESTJSONWEBSOCKET_H
