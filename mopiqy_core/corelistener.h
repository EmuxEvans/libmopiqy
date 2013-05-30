#ifndef CORELISTENER_H
#define CORELISTENER_H

#include <QObject>
#include <QString>

#include "mopidymodels.h"
#include "mopiqy_export.h"

namespace Mopidy {

    namespace Internal {
        class JsonWebSocket;
    }

    /*
     * Listen to event from mopidy server
     */
    namespace Core {
        class MOPIQY_CORE_EXPORT CoreListener : public QObject
        {
            Q_OBJECT

        public:
            CoreListener(Internal::JsonWebSocket *jws, QObject *parent = 0);
            ~CoreListener();

        signals:
            void options_changed();
            void playback_state_changed(const QString &oldState, const QString &newState);
            void playlist_changed(const Mopidy::Models::Playlist &playlist);
            void playlists_loaded();
            void seeked(const int &time_position);
            void track_playback_ended(const Mopidy::Models::TlTrack &tl_track, const int &time_position);
            void track_playback_paused(const Mopidy::Models::TlTrack &tl_track, const int &time_position);
            void track_playback_resumed(const Mopidy::Models::TlTrack &tl_track, const int &time_position);
            void track_playback_started(const Mopidy::Models::TlTrack &tl_track);
            void tracklist_changed();
            void volume_changed();

        protected slots:
            void processJsonMessage(const QByteArray &rawMsg);
        };
    }
}

#endif //CORELISTENER_H
