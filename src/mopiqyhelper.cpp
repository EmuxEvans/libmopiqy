#include "mopiqyhelper.h"

#include "remoteclient.h"
#include "corecontroller.h"
#include "librarycontroller.h"
#include "playbackcontroller.h"
#include "playlistscontroller.h"
#include "tracklistcontroller.h"

using namespace Mopiqy;

// Internal class to store instances;
class MopiqyHelper::MopiqyHelperPrivate
{
public:
    RemoteClient* remoteClient;
    CoreController* coreController;
    LibraryController* libraryController;
    PlaybackController* playbackController;
    PlaylistsController* playlistsController;
    TracklistController* tracklistController;

    MopiqyHelper::MopiqyHelperPrivate()
    {
        remoteClient = new RemoteClient();
        coreController = new CoreController(remoteClient);
        libraryController = new LibraryController(remoteClient);
        playbackController = new PlaybackController(remoteClient);
        playlistsController = new PlaylistsController(remoteClient);
        tracklistController = new TracklistController(remoteClient);
    }
};

MopiqyHelper *MopiqyHelper::m_instance = 0;
MopiqyHelper *MopiqyHelper::instance()
{
    if(m_instance == 0)
        m_instance = new MopiqyHelper;
    return m_instance;
}

RemoteClient *MopiqyHelper::remoteClient()
{
    return m_d->remoteClient;
}

CoreController *MopiqyHelper::coreController()
{
    return m_d->coreController;
}

LibraryController *MopiqyHelper::libraryController()
{
    return m_d->libraryController;
}

PlaybackController *MopiqyHelper::playbackController()
{
    return m_d->playbackController;
}

PlaylistsController *MopiqyHelper::playlistsController()
{
    return m_d->playlistsController;
}

TracklistController *MopiqyHelper::tracklistController()
{
    return m_d->tracklistController;
}

MopiqyHelper::MopiqyHelper()
{
    m_d = new MopiqyHelperPrivate;
}


Mopiqy::MopiqyHelper *iMopidyHelper()
{
    return Mopiqy::MopiqyHelper::instance();
}
