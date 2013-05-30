#include "tst_playlists.h"
#include "tests_global.h"

#include <QCoreApplication>
#include <QDebug>

tst_playlists::tst_playlists(QObject *parent) : QObject(parent)
{
    m_client = new Mopidy::MopidyClient;
    connect(m_client, &Mopidy::MopidyClient::connected, this, &tst_playlists::client_connected);
    connect(m_client, &Mopidy::MopidyClient::disconnected, this, &tst_playlists::client_disconnected);
    connect(m_client, &Mopidy::MopidyClient::connectionError, this, &tst_playlists::client_error);
    connect(m_client, &Mopidy::MopidyClient::messageError, this, &tst_playlists::client_error);

    connect(m_client->playlistsController(), &Mopidy::Core::PlaylistsController::onCreate, this, &tst_playlists::pc_onCreate);
    connect(m_client->playlistsController(), &Mopidy::Core::PlaylistsController::onFilter, this, &tst_playlists::pc_onFilter);
    connect(m_client->playlistsController(), &Mopidy::Core::PlaylistsController::onGetPlaylists, this, &tst_playlists::pc_onGetPlaylists);
    connect(m_client->playlistsController(), &Mopidy::Core::PlaylistsController::onLookup, this, &tst_playlists::pc_onLookup);
    connect(m_client->playlistsController(), &Mopidy::Core::PlaylistsController::onSave, this, &tst_playlists::pc_onSave);
}

tst_playlists::~tst_playlists()
{
    m_client->disconnectClient();
    delete m_client;
}

void tst_playlists::run()
{
    m_client->connectTo(MOPIDY_HOST, MOPIDY_PORT, MOPIDY_PATH);
}

void tst_playlists::client_connected()
{
    qWarning() << "client connected";
    m_client->playlistsController()->get_playlists();
}

void tst_playlists::client_disconnected()
{
    qWarning() << "client disconnected";
    qApp->exit(0);
}

void tst_playlists::client_error(const int &code, const QString &message)
{
    qWarning() << "client error [" << code << "] :" << message;
}

void tst_playlists::pc_onCreate(const Mopidy::Models::Playlist &pl)
{
    qWarning() << __FUNCTION__;
}

void tst_playlists::pc_onFilter(const Mopidy::Models::Playlists &pls)
{
    qWarning() << __FUNCTION__;
}

void tst_playlists::pc_onLookup(const Mopidy::Models::Playlist &pl)
{
    qWarning() << __FUNCTION__;
}

void tst_playlists::pc_onGetPlaylists(const Mopidy::Models::Playlists &pls)
{
    qWarning() << __FUNCTION__;
    foreach(Mopidy::Models::Playlist pl, pls)
    {
        qWarning() << pl.name << "[" << pl.tracks.count() << "tracks ]";
    }

    m_client->disconnectClient();
}

void tst_playlists::pc_onSave(const Mopidy::Models::Playlist &pl)
{
    qWarning() << __FUNCTION__;
}
