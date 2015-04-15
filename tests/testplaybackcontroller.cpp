#include "testplaybackcontroller.h"
#include "libmopiqy/playbackcontroller.h"

void TestPlaybackController::initTestCase()
{
    client.connectToServer("127.0.0.1", 6680, "/mopidy/ws");

    QSignalSpy spy(&client, &MopidyClient::clientConnected);
    QVERIFY(spy.wait(1000));
}

void TestPlaybackController::tstCurrentTlTrack()
{
    QSharedPointer<PlaybackController> controller = client.playbackController();
    QSignalSpy spy(controller.data(), &PlaybackController::currentTlTrackReceived);

    controller->getCurrentTlTrack();
    QVERIFY(spy.wait(500));
}

void TestPlaybackController::tstCurrentTrack()
{
    QSharedPointer<PlaybackController> controller = client.playbackController();
    QSignalSpy spy(controller.data(), &PlaybackController::currentTrackReceived);

    controller->getCurrentTrack();
    QVERIFY(spy.wait(500));
}

void TestPlaybackController::tstState()
{
    QSharedPointer<PlaybackController> controller = client.playbackController();
    QSignalSpy spy(controller.data(), &PlaybackController::stateReceived);

    controller->getState();
    QVERIFY(spy.wait(500));
}

void TestPlaybackController::tstStreamTitle()
{
    QSharedPointer<PlaybackController> controller = client.playbackController();
    QSignalSpy spy(controller.data(), &PlaybackController::streamTitleReceived);

    controller->getStreamTitle();
    QVERIFY(spy.wait(500));
}

void TestPlaybackController::tstTimePosition()
{
    QSharedPointer<PlaybackController> controller = client.playbackController();
    QSignalSpy spy(controller.data(), &PlaybackController::timePositionReceived);

    controller->getTimePosition();
    QVERIFY(spy.wait(500));
}

void TestPlaybackController::tstSeek()
{
    QSharedPointer<PlaybackController> controller = client.playbackController();
    QSignalSpy spy(controller.data(), &PlaybackController::seekReceived);

    controller->seek(0);
    QVERIFY(spy.wait(500));
}


void TestPlaybackController::cleanupTestCase()
{
    client.disconnectFromServer();
}
