#include <QCoreApplication>
#include <QtTest/QtTest>

#include "testmopidyparser.h"
#include "testjsonrpchandler.h"

int main(int argc, char *argv[])
{
    // init application for timers and threads
    QCoreApplication app(argc, argv);

    /*
     * run tests
     */
    TestJsonRpcHandler tJsonRpcHandler;
    QTest::qExec(&tJsonRpcHandler);

    TestMopidyParser tMopidyParser;
    QTest::qExec(&tMopidyParser);
}
