#ifndef MOPIDYCLIENT_H
#define MOPIDYCLIENT_H

/*
 * This is the main entry point to Mopidy server.
 * When connected, all controllers and the eventlistener are ready to send message
 */

#include <QJsonValue>
#include <QJsonObject>
#include <QtWebSockets/QWebSocket>

#include <QHash>
#include <QObject>

#include "mopidymodels.h"

#include "playbackcontroller.h"
#include "playlistscontroller.h"
#include "tracklistcontroller.h"
#include "librarycontroller.h"
#include "corecontroller.h"

#include "mopiqy_export.h"

namespace Mopidy {

    class LIBMOPIQY_EXPORT MopidyClient : public QObject
    {
        Q_OBJECT

    public:
        MopidyClient(QObject *parent = 0);
        ~MopidyClient();

        QString clientVersion() const;

        /*
         * Connection handling
         */
        void connectTo(const QString &host, const qint16 &port, const QString &path);
        void disconnectClient();

        /*
         * Send message
         * return message's ID (random string) if not a notification
         */
        QString sendRequest(QJsonObject request, const bool &isNotification, Core::ControllerInterface *ci);

    signals:
        /*
         * Connection handling
         */
        void clientConnected();
        void clientDisconnected();
        void connectionError(const int &code, const QString &message);

        /*
         * Mopidy's event
         */
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
        void mute_changed(bool muted);

        /*
         * JsonRpc
         */
        void messageError(const int &code, const QString &message);

    private slots:
        void onTextMessageReceived(const QString &rawData);
        void onSocketError(QAbstractSocket::SocketError error);

    private:
        void parseEvent(const QJsonObject &eventObj);
        void parseResponse(const QString &id, const QJsonValue &responseValue);
        QString generateRandomString();

    private:
        QWebSocket *m_webSocket;
        QMap<QString, Mopidy::Core::ControllerInterface*> m_mapMsg;
    };
}

#endif // MOPIDYCLIENT_H
