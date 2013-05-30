#include "tst_library.h"
#include "tests_global.h"

#include <QCoreApplication>
#include <QDebug>

tst_library::tst_library(QObject *parent) : QObject(parent)
{
    m_client = new Mopidy::MopidyClient;
    connect(m_client, &Mopidy::MopidyClient::connected, this, &tst_library::client_connected);
    connect(m_client, &Mopidy::MopidyClient::disconnected, this, &tst_library::client_disconnected);
    connect(m_client, &Mopidy::MopidyClient::connectionError, this, &tst_library::client_error);
    connect(m_client, &Mopidy::MopidyClient::messageError, this, &tst_library::client_error);

    connect(m_client->libraryController(), &Mopidy::Core::LibraryController::onFindExact, this, &tst_library::lc_onFindExact);
    connect(m_client->libraryController(), &Mopidy::Core::LibraryController::onLookup, this, &tst_library::lc_onLookup);
    connect(m_client->libraryController(), &Mopidy::Core::LibraryController::onSearch, this, &tst_library::lc_onSearch);
}

tst_library::~tst_library()
{
    m_client->disconnectClient();
    delete m_client;
}

void tst_library::run()
{
    m_client->connectTo(MOPIDY_HOST, MOPIDY_PORT, MOPIDY_PATH);
}

void tst_library::client_connected()
{
    qWarning() << "client connected";
}

void tst_library::client_disconnected()
{
    qWarning() << "client disconnected";
    qApp->exit(0);
}

void tst_library::client_error(const int &code, const QString &message)
{
    qWarning() << "client error [" << code << "] :" << message;
}

void tst_library::lc_onFindExact(const Mopidy::Models::SearchResult &searchResult)
{
}

void tst_library::lc_onLookup(const Mopidy::Models::Tracks &tracks)
{
}

void tst_library::lc_onSearch(const Mopidy::Models::SearchResult &searchResult)
{
}
