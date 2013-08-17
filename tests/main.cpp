#include <QCoreApplication>
#include <QtTest/QtTest>

#include "testqwebsocketclient.h"
#include "testjsonwebsocket.h"
#include "testjsonrpchandler.h"
#include "testmopidyparser.h"

int main(int argc, char *argv[])
{
    // init application for timers and threads
    QCoreApplication app(argc, argv);

    /*
     * run tests
     */
    TestJsonWebSocket tJsonWebSocket;
    QTest::qExec(&tJsonWebSocket);

    TestQWebSocketClient tQWebSocketClient;
    tQWebSocketClient.setWebSocketServerParams("127.0.0.1", 9000, "/ws");
    QTest::qExec(&tQWebSocketClient);

    TestJsonRpcHandler tJsonRpcHandler;
    QTest::qExec(&tJsonRpcHandler);

    TestMopidyParser tMopidyParser;
    QTest::qExec(&tMopidyParser);
}
