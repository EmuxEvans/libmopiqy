#include "corelistener.h"
#include "mopidyparser.h"
#include "jsonwebsocket.h"

#include <QJsonObject>
#include <QJsonDocument>

using namespace Mopidy::Core;

CoreListener::CoreListener(Internal::JsonWebSocket *jws, QObject *parent) : QObject(parent)
{
    connect(jws, &Mopidy::Internal::JsonWebSocket::eventReceived, this, &CoreListener::processJsonMessage);
}

CoreListener::~CoreListener()
{

}

void CoreListener::processJsonMessage(const QByteArray &rawMsg)
{
    QJsonParseError jpError;
    QJsonDocument jdoc = QJsonDocument::fromJson(rawMsg, &jpError);
    QJsonObject rootObject = jdoc.object();

    QString evtName = rootObject.value("event").toString();

    if(evtName == "options_changed")
    {
        emit options_changed();
    }
    else if(evtName == "playback_state_changed")
    {
        QString os = rootObject.value("old_state").toString();
        QString ns = rootObject.value("new_state").toString();
        emit playback_state_changed(os, ns);
    }
    else if(evtName == "playlist_changed")
    {
        Mopidy::Models::Playlist pl;
        Mopidy::Parser::parseSingleObject(rootObject.value("playlist").toObject(), pl);
        emit playlist_changed(pl);
    }
    else if(evtName == "playlists_loaded")
    {
        emit playlists_loaded();
    }
    else if(evtName == "seeked")
    {
        int tp = rootObject.value("time_position").toDouble();
        emit seeked(tp);
    }
    else if(evtName == "track_playback_ended")
    {
        Mopidy::Models::TlTrack tlt;
        Mopidy::Parser::parseSingleObject(rootObject.value("tl_track").toObject(), tlt);
        int tp = rootObject.value("time_position").toDouble();
        emit track_playback_ended(tlt, tp);
    }
    else if(evtName == "track_playback_paused")
    {
        Mopidy::Models::TlTrack tlt;
        Mopidy::Parser::parseSingleObject(rootObject.value("tl_track").toObject(), tlt);
        int tp = rootObject.value("time_position").toDouble();
        emit track_playback_paused(tlt, tp);
    }
    else if(evtName == "track_playback_resumed")
    {
        Mopidy::Models::TlTrack tlt;
        Mopidy::Parser::parseSingleObject(rootObject.value("tl_track").toObject(), tlt);
        int tp = rootObject.value("time_position").toDouble();
        emit track_playback_resumed(tlt, tp);
    }
    else if(evtName == "track_playback_started")
    {
        Mopidy::Models::TlTrack tlt;
        Mopidy::Parser::parseSingleObject(rootObject.value("tl_track").toObject(), tlt);
        emit track_playback_started(tlt);
    }
    else if(evtName == "tracklist_changed")
    {
        emit tracklist_changed();
    }
    else if(evtName == "volume_changed")
    {
        emit volume_changed();
    }
    // else... so what ?
}
