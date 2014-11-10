#include "playbackcontroller.h"
#include "mopidyparser.h"

using namespace Mopidy;
using namespace Mopidy::Core;

PlaybackController::PlaybackController(MopidyClient *mopidyClient) : ControllerInterface(mopidyClient) { }

PlaybackController::~PlaybackController() { }

void PlaybackController::change_track(const Mopidy::Models::TlTrack &track, const int &on_error_step)
{
    // build request
    QJsonObject vparams;
    vparams.insert("track", Mopidy::Parser::encodeModel(track));
    vparams.insert("on_error_step", on_error_step);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.change_track", vparams);

    // send it
    sendMessage(jso, PC_NONE, true);
}

void PlaybackController::get_current_tltrack()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_current_tl_track");

    // send it
    sendMessage(jso, PC_GETCURRENTTLTRACK);
}

void PlaybackController::get_current_track()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_current_track");

    // send it
    sendMessage(jso, PC_GETCURRENTTRACK);
}

void PlaybackController::set_mute(const bool &mute)
{
    // build request
    QJsonObject vparams;
    vparams.insert("mute", mute);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.set_mute", vparams);

    // send it
    sendMessage(jso, PC_NONE);
}

void PlaybackController::get_mute()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_mute");

    // send it
    sendMessage(jso, PC_GETMUTE);
}

void PlaybackController::next()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.next");

    // send it
    sendMessage(jso, PC_NONE, true);
}

void PlaybackController::pause()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.pause");

    // send it
    sendMessage(jso, PC_NONE, true);
}

void PlaybackController::play(const Mopidy::Models::TlTrack &tltrack, const int &on_error_step)
{
    // build request
    QJsonObject vparams;
    if(!tltrack.track.uri.isEmpty()) vparams.insert("tl_track", Mopidy::Parser::encodeModel(tltrack));
    vparams.insert("on_error_step", on_error_step);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.play", vparams);

    // send it
    sendMessage(jso, PC_NONE, true);
}

void PlaybackController::previous()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.previous");

    // send it
    sendMessage(jso, PC_NONE, true);
}

void PlaybackController::resume()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.resume");

    // send it
    sendMessage(jso, PC_NONE, true);
}

void PlaybackController::seek(const int &time_position)
{
    // build request
    QJsonObject vparams;
    vparams.insert("time_position", time_position);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.seek", vparams);

    // send it
    sendMessage(jso, PC_SEEK, true);
}

void PlaybackController::get_state()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_state");

    // send it
    sendMessage(jso, PC_GETSTATE);
}

void PlaybackController::stop(const bool &clear_current_track)
{
    // build request
    QJsonObject vparams;
    vparams.insert("clear_current_track", clear_current_track);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.stop", vparams);

    // send it
    sendMessage(jso, PC_NONE, true);
}

void PlaybackController::get_time_position()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_time_position");

    // send it
    sendMessage(jso, PC_GETTIMEPOSITION);
}

void PlaybackController::set_volume(const int &volume)
{
    // build request
    QJsonObject vparams;
    vparams.insert("volume", volume);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.set_volume", vparams);

    // send it
    sendMessage(jso, PC_NONE, true);
}

void PlaybackController::get_volume()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playback.get_volume");

    // send it
    sendMessage(jso, PC_GETVOLUME);
}

void PlaybackController::processJsonResponse(const int &idt, const QJsonValue &jo)
{
    switch(idt)
    {
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

    case PC_SEEK:
        emit onSeek(jo.toBool());
        break;

    case PC_GETSTATE:
        emit onGetState(Parser::getState(jo.toString()));
        break;

    case PC_GETTIMEPOSITION:
        emit onGetTimePosition(jo.toDouble());
        break;

    case PC_GETVOLUME:
        emit onGetVolume(jo.toDouble());
        break;

    default:
        qDebug() << "[PlaybackController]" << idt << jo;
        break;
    }
}


