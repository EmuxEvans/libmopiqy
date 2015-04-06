#include "playbackcontrollerimpl.h"
#include "modeltranslator.h"

PlaybackControllerImpl::PlaybackControllerImpl(MopidyClientPrivate *parent)
    : PlaybackController(), BaseControllerImpl(parent)
{ }

PlaybackControllerImpl::~PlaybackControllerImpl()
{ }

void PlaybackControllerImpl::pr_getCurrentTlTrack(const QJsonValue &response)
{
    Mopidy::TlTrack tltrack;
    if(ModelTranslator::fromJson(response.toObject(), tltrack))
        emit currentTlTrackReceived(tltrack);
}

void PlaybackControllerImpl::pr_getCurrentTrack(const QJsonValue &response)
{
    Mopidy::Track track;
    if(ModelTranslator::fromJson(response.toObject(), track))
        emit currentTrackReceived(track);
}

void PlaybackControllerImpl::pr_getState(const QJsonValue &response)
{
    Mopidy::PlaybackState state;
    if(ModelTranslator::fromJson(response.toObject(), state))
        emit stateReceived(state);
}

void PlaybackControllerImpl::pr_getStreamTitle(const QJsonValue &response)
{
    emit streamTitleReceived(response.toString());
}

void PlaybackControllerImpl::pr_getTimePosition(const QJsonValue &response)
{
    emit timePositionReceived(response.toInt());
}

void PlaybackControllerImpl::pr_seek(const QJsonValue &response)
{
    emit seekReceived(response.toBool());
}

void PlaybackControllerImpl::getCurrentTlTrack()
{
    sendRequest(std::bind(&PlaybackControllerImpl::pr_getCurrentTlTrack, this, std::placeholders::_1),
                "core.playback.get_current_tl_track");
}

void PlaybackControllerImpl::getCurrentTrack()
{
    sendRequest(std::bind(&PlaybackControllerImpl::pr_getCurrentTrack, this, std::placeholders::_1),
                "core.playback.get_current_track");
}

void PlaybackControllerImpl::getState()
{
    sendRequest(std::bind(&PlaybackControllerImpl::pr_getState, this, std::placeholders::_1),
                "core.playback.get_state");
}

void PlaybackControllerImpl::getStreamTitle()
{
    sendRequest(std::bind(&PlaybackControllerImpl::pr_getStreamTitle, this, std::placeholders::_1),
                "core.playback.get_stream_title");
}

void PlaybackControllerImpl::getTimePosition()
{
    sendRequest(std::bind(&PlaybackControllerImpl::pr_getTimePosition, this, std::placeholders::_1),
                "core.playback.get_time_position");
}

void PlaybackControllerImpl::next()
{
    sendNotification("core.playback.next");
}

void PlaybackControllerImpl::pause()
{
    sendNotification("core.playback.pause");
}

void PlaybackControllerImpl::play(const Mopidy::TlTrack &tltrack)
{
    QJsonObject params;

    if(tltrack.tlid >= 0)
        params.insert("tl_track", ModelTranslator::toJson(tltrack));
    else
        params.insert("tl_track", QJsonValue::Null);

    sendNotification("core.playback.play", params);
}

void PlaybackControllerImpl::previous()
{
    sendNotification("core.playback.previous");
}

void PlaybackControllerImpl::resume()
{
    sendNotification("core.playback.resume");
}

void PlaybackControllerImpl::seek(const int &timePosition)
{
    QJsonObject params;
    params.insert("time_position", timePosition);

    sendRequest(std::bind(&PlaybackControllerImpl::pr_seek, this, std::placeholders::_1),
                "core.playback.seek", params);
}

void PlaybackControllerImpl::stop()
{
    sendNotification("core.playback.stop");
}
