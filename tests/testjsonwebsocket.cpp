#include "testjsonwebsocket.h"
#include "../src/jsonwebsocket.h"

void TestJsonWebSocket::isConnectedTrue()
{
        Mopidy::Internal::JsonWebSocket jws;

        // have to wait for connection
        QSignalSpy connectedSignal(&jws, SIGNAL(socketConnected()));
        jws.openSocket("127.0.0.1", 6680, "/mopidy/ws/");
        if(!connectedSignal.wait()) QSKIP("Cannot connect to mopidy server");

        QCOMPARE(jws.isConnected(), true);
}

void TestJsonWebSocket::isConnectedFalse()
{
    Mopidy::Internal::JsonWebSocket jws;
    QCOMPARE(jws.isConnected(), false);
}

void TestJsonWebSocket::sendRequest()
{

}

void TestJsonWebSocket::openSocketValid()
{
        Mopidy::Internal::JsonWebSocket jws;
        QCOMPARE(jws.openSocket("127.0.0.1", 6680, "/mopidy/ws/"), true);
}

void TestJsonWebSocket::openSocketInvalid()
{
        Mopidy::Internal::JsonWebSocket jws;
        QCOMPARE(jws.openSocket("127.0", 6680, "/mopidy/ws/"), false);
        QCOMPARE(jws.openSocket("127.0.0.1", 0, "/mopidy/ws/"), false);
        QCOMPARE(jws.openSocket("127.0.0.A", 6680, "/mopidy/ws/"), false);
        QCOMPARE(jws.openSocket("127.0.0.1", 6680, ""), false);
}
