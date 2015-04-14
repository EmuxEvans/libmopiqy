#include "testplaybackcontroller.h"
#include "libmopiqy/playbackcontroller.h"

void TestPlaybackController::initTestCase()
{
    client.connectToServer("127.0.0.1", 6680, "/mopidy/ws");

    QSignalSpy spy(&client, &MopidyClient::clientConnected);
    QVERIFY(spy.wait(1000));
}

void TestPlaybackController::cleanupTestCase()
{
    client.disconnectFromServer();
}
