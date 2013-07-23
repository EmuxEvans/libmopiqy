#include "playbackcontroller.h"
#include "jsonrpchandler.h"
#include "mopidyparser.h"

using namespace Mopidy::Core;
using namespace Mopidy::Internal;

PlaybackController::PlaybackController(JsonRpcHandler *jrHandler, QObject *parent) : QObject(parent), ControllerInterface(jrHandler)
{
}

PlaybackController::~PlaybackController()
{
}

void PlaybackController::change_track(const Mopidy::Models::TlTrack &track, const int &on_error_step)
{
    // build request
    QJsonObject vparams;
    vparams.insert("track", Mopidy::Parser::encodeModel(track));
    vparams.insert("on_error_step", on_error_step);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.change_track", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaybackController::get_consume()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_consume");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETCONSUME);
}

void PlaybackController::set_consume(const bool &v)
{
    // build request
    QJsonObject vparams;
    vparams.insert("value", v);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.set_consume", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaybackController::get_current_tltrack()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_current_tl_track");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETCURRENTTLTRACK);
}

void PlaybackController::get_current_track()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_current_track");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETCURRENTTRACK);
}

void PlaybackController::next()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.next");

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaybackController::pause()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.pause");

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaybackController::play(const Mopidy::Models::TlTrack &tltrack, const int &on_error_step)
{
    // build request
    QJsonObject vparams;
    if(!tltrack.track.uri.isEmpty()) vparams.insert("tl_track", Mopidy::Parser::encodeModel(tltrack));
    vparams.insert("on_error_step", on_error_step);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.play", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaybackController::get_random()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_random");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETRANDOM);
}

void PlaybackController::set_random(const bool &v)
{
    // build request
    QJsonObject vparams;
    vparams.insert("value", v);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.set_random", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaybackController::get_repeat()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_repeat");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETREPEAT);
}

void PlaybackController::set_repeat(const bool &v)
{
    // build request
    QJsonObject vparams;
    vparams.insert("value", v);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.set_repeat", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaybackController::resume()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.resume");

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaybackController::seek(const int &time_position)
{
    // build request
    QJsonObject vparams;
    vparams.insert("time_position", time_position);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.seek", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso, true);

    // keep track
    m_idQuery.insert(id, PC_SEEK);
}

void PlaybackController::get_single()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_single");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETSINGLE);
}

void PlaybackController::set_single(const bool &v)
{
    // build request
    QJsonObject vparams;
    vparams.insert("value", v);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.set_single", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaybackController::get_state()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_state");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETSTATE);
}

void PlaybackController::stop(const bool &clear_current_track)
{
    // build request
    QJsonObject vparams;
    vparams.insert("clear_current_track", clear_current_track);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.stop", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaybackController::get_time_position()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_time_position");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETTIMEPOSITION);
}

void PlaybackController::get_tltrack_at_eot()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_tl_track_at_eot");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETTLTRACKATEOT);
}

void PlaybackController::get_tltrack_at_next()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_tl_track_at_next");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETTLTRACKATNEXT);
}

void PlaybackController::get_tltrack_at_previous()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_tl_track_at_previous");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETTLTRACKATPREVIOUS);
}

void PlaybackController::get_tracklist_position()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_tracklist_position");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETTRACKLISTPOSITION);
}

void PlaybackController::get_volume()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_volume");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PC_GETVOLUME);
}

void PlaybackController::processJsonResponse(const int &id, const QJsonValue &jo)
{
    if(m_idQuery.contains(id))
    {
        int idt = m_idQuery.take(id);
        switch(idt)
        {
        case PC_GETCONSUME:
            emit onGetConsume(jo.toBool());
            break;

        case PC_GETCURRENTTLTRACK:
            {
                Mopidy::Models::TlTrack tltrack;
                Mopidy::Parser::parseSingleObject(jo.toObject(), tltrack);
                emit onGetCurrentTlTrack(tltrack);
            }
            break;

        case PC_GETCURRENTTRACK:
            {
                Mopidy::Models::Track track;
                Mopidy::Parser::parseSingleObject(jo.toObject(), track);
                emit onGetCurrentTrack(track);
            }
            break;

        case PC_GETRANDOM:
            emit onGetRandom(jo.toBool());
            break;

        case PC_GETREPEAT:
            emit onGetRepeat(jo.toBool());
            break;

        case PC_GETSINGLE:
            emit onGetSingle(jo.toBool());
            break;

        case PC_SEEK:
            emit onSeek(jo.toBool());
            break;

        case PC_GETSTATE:
            emit onGetState((Mopidy::Core::PlaybackState)(int)jo.toDouble());
            break;

        case PC_GETTIMEPOSITION:
            emit onGetTimePosition(jo.toDouble());
            break;

        case PC_GETTLTRACKATEOT:
            {
                Mopidy::Models::TlTrack tltrack;
                Mopidy::Parser::parseSingleObject(jo.toObject(), tltrack);
                emit onGetTlTrackAtEot(tltrack);
            }
            break;

        case PC_GETTLTRACKATNEXT:
            {
                Mopidy::Models::TlTrack tltrack;
                Mopidy::Parser::parseSingleObject(jo.toObject(), tltrack);
                emit onGetTlTrackAtNext(tltrack);
            }
            break;

        case PC_GETTLTRACKATPREVIOUS:
            {
                Mopidy::Models::TlTrack tltrack;
                Mopidy::Parser::parseSingleObject(jo.toObject(), tltrack);
                emit onGetTlTrackAtPrevious(tltrack);
            }
            break;

        case PC_GETTRACKLISTPOSITION:
            emit onGetTracklistPosition(jo.toDouble());
            break;

        case PC_GETVOLUME:
            emit onGetVolume(jo.toDouble());
            break;

        default:
            qDebug() << "[PlaybackController]" << id << jo;
            break;
        }
    }
    else
    {
        qDebug() << tr("unmanaged query [PlaybackController]") << id << jo;
    }
}


