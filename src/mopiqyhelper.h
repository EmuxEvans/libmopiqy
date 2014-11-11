#ifndef MOPIQY_HELPER_H
#define MOPIQY_HELPER_H

#include "mopiqy_export.h"

/*
 * Helper class to store in one instance all controller with attached client
 */

namespace Mopiqy {

class RemoteClient;
class CoreController;
class LibraryController;
class PlaybackController;
class PlaylistsController;
class TracklistController;

class LIBMOPIQY_EXPORT MopiqyHelper
{
public:
    static MopiqyHelper* instance();

    RemoteClient* remoteClient();
    CoreController* coreController();
    LibraryController* libraryController();
    PlaybackController* playbackController();
    PlaylistsController* playlistsController();
    TracklistController* tracklistController();

private:
    static MopiqyHelper* m_instance;
    MopiqyHelper();

    // Internal class to store instances
    class MopiqyHelperPrivate;
    MopiqyHelperPrivate *m_d;
};

}

// Shortcuts
LIBMOPIQY_EXPORT Mopiqy::MopiqyHelper* iMopidyHelper();

#endif //MOPIQY_HELPER_H
