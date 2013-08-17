#include "testqwebsocketclient.h"
#include "../src/qwebsocketclient.h"

#include <QtTest/QSignalSpy>

void TestQWebSocketClient::setWebSocketServerParams(const QString &host, const quint16 &port, const QString &path)
{
    m_port = port;
    m_path = path;
    m_host = host;
}

void TestQWebSocketClient::connectToHost()
{
    Mopidy::Internal::QWebSocketClient wsc;
    QSignalSpy sp(&wsc, SIGNAL(connected()));

    QCOMPARE(wsc.connectToHost(m_host, m_port, m_path), true);
    QCOMPARE(sp.wait(), true);
    QCOMPARE(wsc.isConnected(), true);
}

void TestQWebSocketClient::disconnectFromHost()
{
    Mopidy::Internal::QWebSocketClient wsc;
    QSignalSpy spConnect(&wsc, SIGNAL(connected()));
    QSignalSpy spDisconnect(&wsc, SIGNAL(disconnected()));

    wsc.connectToHost(m_host, m_port, m_path);
    if(!spConnect.wait()) QSKIP("Connection failed, cannot test disconnect function.");

    QCOMPARE(wsc.disconnectFromHost(), true);
    QCOMPARE(spDisconnect.wait(), true);
    QCOMPARE(wsc.isConnected(), false);
}

void TestQWebSocketClient::ping()
{
    Mopidy::Internal::QWebSocketClient wsc;
    QSignalSpy spConnect(&wsc, SIGNAL(connected()));
    QSignalSpy spPong(&wsc, SIGNAL(pong()));

    wsc.connectToHost(m_host, m_port, m_path);
    if(!spConnect.wait()) QSKIP("Connection failed, cannot test disconnect function.");

    wsc.ping();
    QCOMPARE(spPong.wait(), true);
}

void TestQWebSocketClient::writeTextMessage()
{
    // be sure to have echo ws server
    Mopidy::Internal::QWebSocketClient wsc;
    QSignalSpy spConnect(&wsc, SIGNAL(connected()));
    QSignalSpy spRead(&wsc, SIGNAL(textMessageReceived(QString)));

    wsc.connectToHost(m_host, m_port, m_path);
    if(!spConnect.wait()) QSKIP("Connection failed, cannot test disconnect function.");

    QString str("Hello world !");

    wsc.writeTextMessage(str);
    QCOMPARE(spRead.wait(), true);

    QList<QVariant> arguments = spRead.takeFirst();
    QCOMPARE(arguments.at(0).type(), QVariant::String);
    QVERIFY(arguments.at(0).toString() == str);
}

void TestQWebSocketClient::writeBinaryMessage()
{
    // be sure to have echo ws server
    Mopidy::Internal::QWebSocketClient wsc;
    QSignalSpy spConnect(&wsc, SIGNAL(connected()));
    QSignalSpy spRead(&wsc, SIGNAL(binaryMessageReceived(QByteArray)));

    wsc.connectToHost(m_host, m_port, m_path);
    if(!spConnect.wait()) QSKIP("Connection failed, cannot test disconnect function.");

    QByteArray ba;
    for(int i = 0; i < 20; ++i) ba.append(char(i));

    wsc.writeBinaryMessage(ba);
    QCOMPARE(spRead.wait(), true);

    QList<QVariant> arguments = spRead.takeFirst();
    QCOMPARE(arguments.at(0).type(), QVariant::ByteArray);
    QVERIFY(arguments.at(0).toByteArray() == ba);
}
