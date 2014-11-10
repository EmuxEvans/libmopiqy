#ifndef REMOTECLIENT_H
#define REMOTECLIENT_H

#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

#include "controllerinterface.h"
#include "mopidymodels.h"
#include "mopiqy_export.h"

namespace Mopiqy {
class LIBMOPIQY_EXPORT RemoteClient : public QObject
{
    Q_OBJECT

public:
    RemoteClient(QObject *parent = 0);
    ~RemoteClient();

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
    QString sendRequest(QJsonObject request, const bool &isNotification, ControllerInterface *ci);

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
    void playback_state_changed(const Core::PlaybackState &oldState, const Core::PlaybackState &newState);
    void playlist_changed(const Mopiqy::Models::Playlist &playlist);
    void playlists_loaded();
    void seeked(const int &time_position);
    void track_playback_ended(const Mopiqy::Models::TlTrack &tl_track, const int &time_position);
    void track_playback_paused(const Mopiqy::Models::TlTrack &tl_track, const int &time_position);
    void track_playback_resumed(const Mopiqy::Models::TlTrack &tl_track, const int &time_position);
    void track_playback_started(const Mopiqy::Models::TlTrack &tl_track);
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
    QMap<QString, ControllerInterface*> m_mapMsg;
};
}

#endif // REMOTECLIENT_H
