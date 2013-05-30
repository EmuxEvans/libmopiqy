#include "tst_playback.h"
#include "tests_global.h"

#include <QCoreApplication>
#include <QDebug>

tst_playback::tst_playback(QObject *parent) : QObject(parent)
{
    m_client = new Mopidy::MopidyClient;
    connect(m_client, &Mopidy::MopidyClient::connected, this, &tst_playback::client_connected);
    connect(m_client, &Mopidy::MopidyClient::disconnected, this, &tst_playback::client_disconnected);
    connect(m_client, &Mopidy::MopidyClient::connectionError, this, &tst_playback::client_error);
    connect(m_client, &Mopidy::MopidyClient::messageError, this, &tst_playback::client_error);
}

tst_playback::~tst_playback()
{
    m_client->disconnectClient();
    delete m_client;
}

void tst_playback::run()
{
    m_client->connectTo(MOPIDY_HOST, MOPIDY_PORT, MOPIDY_PATH);
}

void tst_playback::client_connected()
{
    qWarning() << "client connected";
}

void tst_playback::client_disconnected()
{
    qWarning() << "client disconnected";
    qApp->exit(0);
}

void tst_playback::client_error(const int &code, const QString &message)
{
    qWarning() << "client error [" << code << "] :" << message;
}
