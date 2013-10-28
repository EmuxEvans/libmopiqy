#include "eventlistener.h"
#include "mopidyparser.h"
#include "jsonwebsocket.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

using namespace Mopidy::Core;

EventListener::EventListener(QObject *parent) : QObject(parent)
{ }

EventListener::~EventListener()
{ }

void EventListener::setJsonWebSocket(Mopidy::Internal::JsonWebSocket *jws)
{
    if(jws)
    {
        connect(jws, &Mopidy::Internal::JsonWebSocket::eventReceived, this, &EventListener::processJsonMessage);
    }
}

void EventListener::processJsonMessage(const QByteArray &rawMsg)
{
    QJsonParseError jpError;
    QJsonDocument jdoc = QJsonDocument::fromJson(rawMsg, &jpError);
    QJsonObject rootObject = jdoc.object();

    if(rootObject.contains("event"))
    {
        QString evtName = rootObject.value("event").toString();

        if(evtName == "options_changed")
        {
            emit options_changed();
        }
        else if(evtName == "playback_state_changed")
        {
            QString os = rootObject.value("old_state").toString();
            QString ns = rootObject.value("new_state").toString();
            emit playback_state_changed(Mopidy::Parser::getState(os), Mopidy::Parser::getState(ns));
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
        else if(evtName == "mute_changed")
        {
            emit mute_changed(rootObject.value("mute").toBool());
        }
        else
        {
            qCritical() << __FUNCTION__ << QObject::tr("Unknown event:") << evtName;
        }
    }
}
