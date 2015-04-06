#include "testcorecontroller.h"
#include "libmopiqy/corecontroller.h"

void TestCoreController::initTestCase()
{
    client.connectToServer("127.0.0.1", 6680, "/mopidy/ws");

    QSignalSpy spy(&client, &MopidyClient::clientConnected);
    QVERIFY(spy.wait(1000));
}

void TestCoreController::tstDescribe()
{
    QSharedPointer<CoreController> core = client.coreController();
    QSignalSpy spy(core.data(), &CoreController::describeReceived);

    core->describe();

    QVERIFY(spy.wait(500));
    QVERIFY(spy.takeFirst().at(0).toString().isEmpty() == false);
}

void TestCoreController::tstGetUriSchemes()
{
    QSharedPointer<CoreController> core = client.coreController();
    QSignalSpy spy(core.data(), &CoreController::uriSchemesReceived);

    core->getUriSchemes();

    QVERIFY(spy.wait(500));
    QVERIFY(spy.takeFirst().at(0).toStringList().isEmpty() == false);
}

void TestCoreController::tstGetVersion()
{
    QSharedPointer<CoreController> core = client.coreController();
    QSignalSpy spy(core.data(), &CoreController::versionReceived);

    core->getVersion();

    QVERIFY(spy.wait(500));
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toString().isEmpty() == false);
    QCOMPARE(arguments.at(0).toString(), QString("1.0.0"));
}

void TestCoreController::cleanupTestCase()
{
    client.disconnectFromServer();
}
