#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

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
        class LIBMOPIQY_EXPORT EventListener : public QObject
        {
            Q_OBJECT

        public:
            EventListener(QObject *parent = 0);
            ~EventListener();

            void setJsonWebSocket(Internal::JsonWebSocket *jws);

        signals:
            void options_changed();
            void playback_state_changed(const Mopidy::Core::PlaybackState &oldState, const Mopidy::Core::PlaybackState &newState);
            void playlist_changed(const Mopidy::Models::Playlist &playlist);
            void playlists_loaded();
            void seeked(const int &time_position);
            void track_playback_ended(const Mopidy::Models::TlTrack &tl_track, const int &time_position);
            void track_playback_paused(const Mopidy::Models::TlTrack &tl_track, const int &time_position);
            void track_playback_resumed(const Mopidy::Models::TlTrack &tl_track, const int &time_position);
            void track_playback_started(const Mopidy::Models::TlTrack &tl_track);
            void tracklist_changed();
            void volume_changed();
            void error(const int &code, const QString &msg);

        protected slots:
            void processJsonMessage(const QByteArray &rawMsg);
        };
    }
}

#endif //EVENTLISTENER_H
