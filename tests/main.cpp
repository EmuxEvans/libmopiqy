#include <QCoreApplication>
#include <QtTest/QtTest>

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

    TestJsonRpcHandler tJsonRpcHandler;
    QTest::qExec(&tJsonRpcHandler);

    TestMopidyParser tMopidyParser;
    QTest::qExec(&tMopidyParser);
}
