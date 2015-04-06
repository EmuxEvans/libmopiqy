#include <QCoreApplication>
#include <QtTest/QtTest>

#include "testmopidyclient.h"
#include "testcorecontroller.h"
#include "testhistorycontroller.h"
#include "testmixercontroller.h"

int main(int argc, char *argv[])
{
    // init application for timers and threads
    QCoreApplication app(argc, argv);

    // run tests
    TestMopidyClient tMopidyclient;
    QTest::qExec(&tMopidyclient);

    TestCoreController tCoreController;
    QTest::qExec(&tCoreController);

    TestHistoryController tHistoryController;
    QTest::qExec(&tHistoryController);

    TestMixerController tMixerController;
    QTest::qExec(&tMixerController);
}
