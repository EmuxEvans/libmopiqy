#include "testplaylistscontroller.h"
#include "libmopiqy/playlistscontroller.h"

void TestPlaylistsController::initTestCase()
{
    client.connectToServer("127.0.0.1", 6680, "/mopidy/ws");

    QSignalSpy spy(&client, &MopidyClient::clientConnected);
    QVERIFY(spy.wait(1000));
}

void TestPlaylistsController::tstAsListResponse()
{
    QSharedPointer<PlaylistsController> controller = client.playlistsController();
    QSignalSpy spy(controller.data(), &PlaylistsController::asListResponse);

    controller->asList();
    QVERIFY(spy.wait(500));
}

void TestPlaylistsController::tstCreateResponse()
{
    QSharedPointer<PlaylistsController> controller = client.playlistsController();
    QSignalSpy spy(controller.data(), &PlaylistsController::createResponse);

    controller->create("tst_create_playlist");
    QVERIFY(spy.wait(500));

    QList<QVariant> parameters = spy.takeFirst();
    Mopidy::Playlist mplaylist = qvariant_cast<Mopidy::Playlist>(parameters.at(0));
    QCOMPARE(mplaylist.name, QString("tst_create_playlist"));
}

void TestPlaylistsController::tstGetItemsResponse()
{
    QSharedPointer<PlaylistsController> controller = client.playlistsController();
    QSignalSpy spy(controller.data(), &PlaylistsController::getItemsResponse);

    controller->getItems("m3u:tst_create_playlist");
    QVERIFY(spy.wait(500));
}

void TestPlaylistsController::tstLookupResponse()
{
    QSharedPointer<PlaylistsController> controller = client.playlistsController();
    QSignalSpy spy(controller.data(), &PlaylistsController::lookupResponse);

    controller->lookup("m3u:tst_create_playlist.m3u");
    QVERIFY(spy.wait(500));

    QList<QVariant> parameters = spy.takeFirst();
    Mopidy::Playlist mplaylist = qvariant_cast<Mopidy::Playlist>(parameters.at(0));
    QCOMPARE(mplaylist.name, QString("tst_create_playlist"));
}

void TestPlaylistsController::tstSaveResponse()
{
    QSharedPointer<PlaylistsController> controller = client.playlistsController();
    QSignalSpy spy(controller.data(), &PlaylistsController::saveResponse);

    Mopidy::Playlist pl;
    pl.name = "tst_save_playlist";
    pl.uri = "m3u:tst_save_playlist.m3u";

    controller->save(pl);
    QVERIFY(spy.wait(500));

    QList<QVariant> parameters = spy.takeFirst();
    Mopidy::Playlist mplaylist = qvariant_cast<Mopidy::Playlist>(parameters.at(0));
    QCOMPARE(mplaylist.name, pl.name);
    QCOMPARE(mplaylist.uri, pl.uri);
}


void TestPlaylistsController::cleanupTestCase()
{
    client.disconnectFromServer();
}
