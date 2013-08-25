#include "qwebsocketclient.h"
#include "qwebsocketclient_p.h"

using namespace Mopidy::Internal;

QWebSocketClient::QWebSocketClient(QObject *parent) : QObject(parent)
{
    m_d = new QWebSocketClientPrivate(this);
    connect(m_d, &QWebSocketClientPrivate::socket_connected, this, &QWebSocketClient::connected);
    connect(m_d, &QWebSocketClientPrivate::socket_disconnected, this, &QWebSocketClient::disconnected);
    connect(m_d, &QWebSocketClientPrivate::socket_error, this, &QWebSocketClient::error);
    connect(m_d, &QWebSocketClientPrivate::textMessageReceived, this, &QWebSocketClient::textMessageReceived);
    connect(m_d, &QWebSocketClientPrivate::pong, this, &QWebSocketClient::pong);
}

QWebSocketClient::~QWebSocketClient()
{
    m_d->disconnectFromHost();
}

bool QWebSocketClient::connectToHost(const QString &host, const quint16 &port, const QString &path)
{
    return m_d->connectToHost(host, port, path);
}

bool QWebSocketClient::isConnected() const
{
    return m_d->isConnected();
}

void QWebSocketClient::disconnectFromHost()
{
    m_d->disconnectFromHost();
}

void QWebSocketClient::ping()
{
    m_d->ping();
}

void QWebSocketClient::writeTextMessage(const QString &message)
{
    m_d->writeTextMessage(message);
}
