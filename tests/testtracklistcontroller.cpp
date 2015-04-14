#include "testtracklistcontroller.h"
#include "libmopiqy/tracklistcontroller.h"

void TestTracklistController::initTestCase()
{
    client.connectToServer("127.0.0.1", 6680, "/mopidy/ws");

    QSignalSpy spy(&client, &MopidyClient::clientConnected);
    QVERIFY(spy.wait(1000));
}

void TestTracklistController::cleanupTestCase()
{
    client.disconnectFromServer();
}
