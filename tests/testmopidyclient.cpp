#include "testmopidyclient.h"
#include "libmopiqy/mopidyclient.h"

void TestMopidyClient::initTestCase()
{
    m_host = "127.0.0.1";
    m_port = 6680;
    m_path = "/mopidy/ws";
}

void TestMopidyClient::tstConnectionOk()
{
    MopidyClient client;
    QSignalSpy spy(&client, &MopidyClient::clientConnected);

    client.connectToServer(m_host, m_port, m_path);
    QVERIFY(spy.wait(1000));
}

void TestMopidyClient::tstDeconnection()
{
    MopidyClient client;
    QSignalSpy spyConnected(&client, &MopidyClient::clientConnected);
    QSignalSpy spyDisconnected(&client, &MopidyClient::clientDisconnected);

    client.connectToServer(m_host, m_port, m_path);
    if(spyConnected.wait(1000))
    {
        client.disconnectFromServer();
        QVERIFY(spyDisconnected.wait(1000));
    }
    else
    {
        QSKIP("Not connected");
    }
}

void TestMopidyClient::tstConnectionFail()
{
    MopidyClient client;
    QSignalSpy spy(&client, &MopidyClient::clientConnected);

    client.connectToServer(m_host, m_port, "");
    QVERIFY(spy.wait(500) == false);
}

void TestMopidyClient::cleanupTestCase()
{
}
