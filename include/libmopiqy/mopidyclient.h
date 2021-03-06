#ifndef MOPIDY_CLIENT_H
#define MOPIDY_CLIENT_H

#include <QObject>

#include <libmopiqy/mopidymodels.h>

// All available controllers since Mopidy 1.0.0
class CoreController;
class HistoryController;
class LibraryController;
class MixerController;
class PlaybackController;
class PlaylistsController;
class TracklistController;

class MopidyClientPrivate;
class LIBMOPIQY_EXPORT MopidyClient : public QObject
{
    Q_OBJECT

public:
    MopidyClient(QObject *parent = 0);
    ~MopidyClient();

    void connectToServer(const QString &host, const quint16 &port, const QString &path);
    void disconnectFromServer();

    QString clientVersion() const;

    QSharedPointer<CoreController> coreController();
    QSharedPointer<HistoryController> historyController();
    QSharedPointer<LibraryController> libraryController();
    QSharedPointer<MixerController> mixerController();
    QSharedPointer<PlaybackController> playbackController();
    QSharedPointer<PlaylistsController> playlistsController();
    QSharedPointer<TracklistController> tracklistController();

signals:
    // connections signals
    void clientConnected();
    void clientDisconnected();
    void connectionError(const int &code, const QString &message);

    //
    void protocolError(const int &code, const QString &message);

    // mopidy's events
    void optionsChanged();
    void playbackStateChanged(const Mopidy::PlaybackState &oldState, const Mopidy::PlaybackState &newState);
    void playlistChanged(const Mopidy::Playlist &playlist);
    void playlistsLoaded();
    void seeked(const int &time_position);
    void trackPlaybackEnded(const Mopidy::TlTrack &tl_track, const int &time_position);
    void trackPlaybackPaused(const Mopidy::TlTrack &tl_track, const int &time_position);
    void trackPlaybackResumed(const Mopidy::TlTrack &tl_track, const int &time_position);
    void trackPlaybackStarted(const Mopidy::TlTrack &tl_track);
    void tracklistChanged();
    void volumeChanged();
    void muteChanged(bool muted);

private:
    Q_DECLARE_PRIVATE(MopidyClient)
    QScopedPointer<MopidyClientPrivate> d_ptr;
};

#endif //MOPIDY_CLIENT_H
