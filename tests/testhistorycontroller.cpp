#include "testhistorycontroller.h"
#include "libmopiqy/historycontroller.h"

void TestHistoryController::initTestCase()
{
    client.connectToServer("127.0.0.1", 6680, "/mopidy/ws");

    QSignalSpy spy(&client, &MopidyClient::clientConnected);
    QVERIFY(spy.wait(1000));
}

void TestHistoryController::tstGetHistory()
{
    QSharedPointer<HistoryController> controller = client.historyController();
    QSignalSpy spy(controller.data(), &HistoryController::historyReceived);

    controller->getHistory();

    QVERIFY(spy.wait(500));
}

void TestHistoryController::tstGetLength()
{
    QSharedPointer<HistoryController> controller = client.historyController();
    QSignalSpy spy(controller.data(), &HistoryController::lengthReceived);

    controller->getLength();

    QVERIFY(spy.wait(500));
}

void TestHistoryController::cleanupTestCase()
{
    client.disconnectFromServer();
}
