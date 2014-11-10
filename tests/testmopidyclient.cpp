#include "testmopidyclient.h"
#include "../src/mopidyclient.h"

void TestMopidyClient::initTestCase()
{
    m_host = "127.0.0.1";
    m_port = 6680;
    m_path = "/mopidy/ws";
}

void TestMopidyClient::tstConnectionOk()
{
    Mopidy::MopidyClient mc;
    QSignalSpy spy(&mc, SIGNAL(clientConnected()));

    mc.connectTo(m_host, m_port, m_path);
    QVERIFY(spy.wait(1000));
}

void TestMopidyClient::tstDeconnection()
{
    Mopidy::MopidyClient mc;
    QSignalSpy spyConnected(&mc, SIGNAL(clientConnected()));
    QSignalSpy spyDisconnected(&mc, SIGNAL(clientDisconnected()));

    mc.connectTo(m_host, m_port, m_path);
    if(spyConnected.wait(1000))
    {
        mc.disconnectClient();
        QVERIFY(spyDisconnected.wait(1000));
    }
    else
    {
        QSKIP("Not connected");
    }
}

void TestMopidyClient::tstConnectionFail()
{
    Mopidy::MopidyClient mc;
    QSignalSpy spy(&mc, SIGNAL(clientConnected()));

    mc.connectTo(m_host, m_port, "");
    QVERIFY(spy.wait(1000) == false);
}

void TestMopidyClient::cleanupTestCase()
{
}
