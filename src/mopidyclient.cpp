#include "mopidyclient.h"
#include "jsonwebsocket.h"
#include "jsonrpchandler.h"

using namespace Mopidy;

MopidyClient::MopidyClient(QObject *parent) : QObject(parent)
{
    m_jwSocket = 0;

    m_jrHandler = new Internal::JsonRpcHandler(this);
    m_eventListener = new Core::EventListener(this);
    m_playlistsController = new Core::PlaylistsController(m_jrHandler, this);
    m_tracklistController = new Core::TracklistController(m_jrHandler, this);
    m_playbackController = new Core::PlaybackController(m_jrHandler, this);
    m_libraryController = new Core::LibraryController(m_jrHandler, this);
}

MopidyClient::~MopidyClient()
{
    delete m_playbackController;
    delete m_playlistsController;
    delete m_tracklistController;
    delete m_libraryController;
    delete m_eventListener;
    delete m_jrHandler;
    delete m_jwSocket;
}

QString MopidyClient::clientVersion() const
{
    return LIBMOPIQY_VERSION;
}

bool MopidyClient::connectTo(const QString &host, const qint16 &port, const QString &path)
{
    if(m_jwSocket)
    {
        delete m_jwSocket;
        m_jwSocket = 0;
    }

    m_jwSocket = new Internal::JsonWebSocket(this);
    connect(m_jwSocket, &Internal::JsonWebSocket::socketError, this, &MopidyClient::connectionError);
    connect(m_jwSocket, &Internal::JsonWebSocket::responseError, this, &MopidyClient::messageError);
    connect(m_jwSocket, &Internal::JsonWebSocket::socketDisconnected, this, &MopidyClient::onJwsDisconnected);
    connect(m_jwSocket, &Internal::JsonWebSocket::socketConnected, this, &MopidyClient::onJwsConnected);

    return m_jwSocket->openSocket(host, port, path);
}

void MopidyClient::disconnectClient()
{
    m_jwSocket->closeSocket();
}

Core::EventListener *MopidyClient::eventListener() const
{
    return m_eventListener;
}

Core::PlaybackController *MopidyClient::playbackController() const
{
    return m_playbackController;
}

Core::PlaylistsController *MopidyClient::playlistsController() const
{
    return m_playlistsController;
}

Core::TracklistController *MopidyClient::tracklistController() const
{
    return m_tracklistController;
}

Mopidy::Core::LibraryController *MopidyClient::libraryController() const
{
    return m_libraryController;
}

void MopidyClient::onJwsConnected()
{
    m_jrHandler->setJsonWebSocket(m_jwSocket);
    m_eventListener->setJsonWebSocket(m_jwSocket);
    emit connected();
}

void MopidyClient::onJwsDisconnected()
{
    m_jrHandler->setJsonWebSocket(0);
    m_eventListener->setJsonWebSocket(0);
    emit disconnected();
}
