#include "testlibrarycontroller.h"
#include "libmopiqy/librarycontroller.h"

void TestLibraryController::initTestCase()
{
    client.connectToServer("127.0.0.1", 6680, "/mopidy/ws");

    QSignalSpy spy(&client, &MopidyClient::clientConnected);
    QVERIFY(spy.wait(1000));
}

void TestLibraryController::tstBrowse()
{
    QSharedPointer<LibraryController> controller = client.libraryController();
    QSignalSpy spy(controller.data(), &LibraryController::browseResult);

    controller->browse();

    QVERIFY(spy.wait(500));
}

void TestLibraryController::tstLookup()
{
    QSharedPointer<LibraryController> controller = client.libraryController();
    QSignalSpy spy(controller.data(), &LibraryController::lookupResult);

    controller->lookup();

    QVERIFY(spy.wait(500));
}

void TestLibraryController::tstRefresh()
{
    QSharedPointer<LibraryController> controller = client.libraryController();
    QSignalSpy spy(&client, &MopidyClient::playlistsLoaded);

    controller->refresh();

    QSKIP("Not implemented");
}

void TestLibraryController::tstSearch()
{
    QSKIP("Not implemented");
}

void TestLibraryController::tstGetImages()
{
    QSKIP("Not implemented");
}

void TestLibraryController::cleanupTestCase()
{
    client.disconnectFromServer();
}
