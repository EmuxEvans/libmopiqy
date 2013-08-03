#ifndef TESTJSONRPCHANDLER_H
#define TESTJSONRPCHANDLER_H

#include <QtTest/QtTest>

class TestJsonRpcHandler : public QObject
{
    Q_OBJECT

private slots:
    void sendMessageSuccess();
    void noSocketSendMessage();
};

#endif //TESTJSONRPCHANDLER_H
