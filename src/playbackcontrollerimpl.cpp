#include "playbackcontrollerimpl.h"


PlaybackControllerImpl::PlaybackControllerImpl(MopidyClientPrivate *parent)
    : PlaybackController(), m_mcp(parent)
{ }

PlaybackControllerImpl::~PlaybackControllerImpl()
{ }

void PlaybackControllerImpl::pr_getCurrentTlTrack(const QJsonValue &response)
{

}

void PlaybackControllerImpl::pr_getCurrentTrack(const QJsonValue &response)
{

}

void PlaybackControllerImpl::pr_getState(const QJsonValue &response)
{

}

void PlaybackControllerImpl::pr_getStreamTitle(const QJsonValue &response)
{

}

void PlaybackControllerImpl::pr_getTimePosition(const QJsonValue &response)
{

}

void PlaybackControllerImpl::getCurrentTlTrack()
{
}

void PlaybackControllerImpl::getCurrentTrack()
{
}

void PlaybackControllerImpl::getState()
{
}

void PlaybackControllerImpl::getStreamTitle()
{
}

void PlaybackControllerImpl::getTimePosition()
{
}

void PlaybackControllerImpl::next()
{
}

void PlaybackControllerImpl::pause()
{
}

void PlaybackControllerImpl::play(const Mopidy::TlTrack &tltrack)
{
}

void PlaybackControllerImpl::previous()
{
}

void PlaybackControllerImpl::resume()
{
}

void PlaybackControllerImpl::seek(const int &timePosition)
{
}

void PlaybackControllerImpl::stop()
{
}
