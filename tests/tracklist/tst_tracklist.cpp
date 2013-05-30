#include "tst_tracklist.h"
#include "tests_global.h"

#include <QCoreApplication>
#include <QDebug>

tst_tracklist::tst_tracklist(QObject *parent) : QObject(parent)
{
    m_client = new Mopidy::MopidyClient;
    connect(m_client, &Mopidy::MopidyClient::connected, this, &tst_tracklist::client_connected);
    connect(m_client, &Mopidy::MopidyClient::disconnected, this, &tst_tracklist::client_disconnected);
    connect(m_client, &Mopidy::MopidyClient::connectionError, this, &tst_tracklist::client_error);
    connect(m_client, &Mopidy::MopidyClient::messageError, this, &tst_tracklist::client_error);
}

tst_tracklist::~tst_tracklist()
{
    m_client->disconnectClient();
    delete m_client;
}

void tst_tracklist::run()
{
    m_client->connectTo(MOPIDY_HOST, MOPIDY_PORT, MOPIDY_PATH);
}

void tst_tracklist::client_connected()
{
    qWarning() << "client connected";
}

void tst_tracklist::client_disconnected()
{
    qWarning() << "client disconnected";
    qApp->exit(0);
}

void tst_tracklist::client_error(const int &code, const QString &message)
{
    qWarning() << "client error [" << code << "] :" << message;
}
