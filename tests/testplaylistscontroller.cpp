#include "testplaylistscontroller.h"
#include "libmopiqy/playlistscontroller.h"

void TestPlaylistsController::initTestCase()
{
    client.connectToServer("127.0.0.1", 6680, "/mopidy/ws");

    QSignalSpy spy(&client, &MopidyClient::clientConnected);
    QVERIFY(spy.wait(1000));
}

void TestPlaylistsController::cleanupTestCase()
{
    client.disconnectFromServer();
}
