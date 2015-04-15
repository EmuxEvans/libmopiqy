#include "testtracklistcontroller.h"
#include "libmopiqy/tracklistcontroller.h"

void TestTracklistController::initTestCase()
{
    client.connectToServer("127.0.0.1", 6680, "/mopidy/ws");

    QSignalSpy spy(&client, &MopidyClient::clientConnected);
    QVERIFY(spy.wait(1000));
}

void TestTracklistController::tstAdd()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::addDone);

    QStringList uris;

    controller->add(uris);
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstEotTrack()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::eotTrackReceived);

    //controller->eotTrack();
    //QVERIFY(spy.wait(500));
    QSKIP("Not implemented");
}

void TestTracklistController::tstFilter()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::filterDone);

//    controller->filter();
//    QVERIFY(spy.wait(500));
    QSKIP("Not implemented");
}

void TestTracklistController::tstConsume()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::consumeReceived);

    controller->getConsume();
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstLength()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::lengthReceived);

    controller->getLength();
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstRandom()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::randomReceived);

    controller->getRandom();
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstRepeat()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::repeatReceived);

    controller->getRepeat();
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstSingle()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::singleReceived);

    controller->getSingle();
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstTlTracks()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::tlTracksReceived);

    controller->getTlTracks();
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstTracks()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::tracksReceived);

    controller->getTracks();
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstVersion()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::versionReceived);

    controller->getVersion();
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstIndex()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::indexReceived);

//    controller->index();
//    QVERIFY(spy.wait(500));
    QSKIP("Not implemented");
}

void TestTracklistController::tstNextTrack()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::nextTrackReceived);

    controller->nextTrack();
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstPreviousTrack()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::previousTrackReceived);

    controller->previousTrack();
    QVERIFY(spy.wait(500));
}

void TestTracklistController::tstRemove()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::removeDone);

//    controller->remove();
//    QVERIFY(spy.wait(500));
    QSKIP("Not implemented");
}

void TestTracklistController::tstSlice()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::sliceDone);

//    controller->slice();
//    QVERIFY(spy.wait(500));
    QSKIP("Not implemented");
}


void TestTracklistController::cleanupTestCase()
{
    client.disconnectFromServer();
}
