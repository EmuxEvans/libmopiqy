#include "testmixercontroller.h"
#include "libmopiqy/mixercontroller.h"

void TestMixerController::initTestCase()
{
    client.connectToServer("127.0.0.1", 6680, "/mopidy/ws");

    QSignalSpy spy(&client, &MopidyClient::clientConnected);
    QVERIFY(spy.wait(1000));
}

void TestMixerController::tstGetMute()
{
    QSharedPointer<MixerController> controller = client.mixerController();
    QSignalSpy spy(controller.data(), &MixerController::getMuteReceived);

    controller->getMute();

    QVERIFY(spy.wait(500));
}

void TestMixerController::tstSetMute()
{
    QSharedPointer<MixerController> controller = client.mixerController();
    QSignalSpy spy(controller.data(), &MixerController::setMuteReceived);

    controller->setMute(true);

    QVERIFY(spy.wait(500));
}

void TestMixerController::tstGetVolume()
{
    QSharedPointer<MixerController> controller = client.mixerController();
    QSignalSpy spy(controller.data(), &MixerController::getVolumeReceived);

    controller->getVolume();

    QVERIFY(spy.wait(500));
    QList<QVariant> parameters = spy.takeFirst();
    double volume = parameters.at(0).toDouble();
    QVERIFY(volume >= 0);
    QVERIFY(volume <= 100);
}

void TestMixerController::tstSetVolume()
{
    QSharedPointer<MixerController> controller = client.mixerController();
    QSignalSpy spy(controller.data(), &MixerController::setVolumeReceived);

    controller->setVolume(45);

    QVERIFY(spy.wait(500));
}

void TestMixerController::cleanupTestCase()
{
    client.disconnectFromServer();
}
