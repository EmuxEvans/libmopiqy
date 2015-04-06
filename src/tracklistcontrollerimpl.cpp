#include "tracklistcontrollerimpl.h"

TracklistControllerImpl::TracklistControllerImpl(MopidyClientPrivate *parent)
    : TracklistController(), BaseControllerImpl(parent)
{ }

TracklistControllerImpl::~TracklistControllerImpl()
{ }

void TracklistControllerImpl::pr_add(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_eotTrack(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_filter(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_consume(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_length(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_random(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_repeat(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_single(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_tlTracks(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_tracks(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_version(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_index(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_nextTrack(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_previousTrack(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_remove(const QJsonValue &response)
{

}

void TracklistControllerImpl::pr_slice(const QJsonValue &response)
{

}


void TracklistControllerImpl::add(const QStringList &uris, const int &atPosition)
{
}

void TracklistControllerImpl::clear()
{
}

void TracklistControllerImpl::eotTrack(const Mopidy::TlTrack &tltrack)
{
}

void TracklistControllerImpl::getConsume()
{
}

void TracklistControllerImpl::getLength()
{
}

void TracklistControllerImpl::getRandom()
{
}

void TracklistControllerImpl::getRepeat()
{
}

void TracklistControllerImpl::getSingle()
{
}

void TracklistControllerImpl::getTlTracks()
{
}

void TracklistControllerImpl::getTracks()
{
}

void TracklistControllerImpl::getVersion()
{
}

void TracklistControllerImpl::index(const Mopidy::TlTrack &tltrack)
{
}

void TracklistControllerImpl::move(const int &start, const int &end, const int &toPosition)
{
}

void TracklistControllerImpl::nextTrack(const Mopidy::TlTrack &tltrack)
{
}

void TracklistControllerImpl::previousTrack(const Mopidy::TlTrack &tltrack)
{
}

void TracklistControllerImpl::setConsume(const bool &consume)
{
}

void TracklistControllerImpl::setRandom(const bool &random)
{
}

void TracklistControllerImpl::setRepeat(const bool &repeat)
{
}

void TracklistControllerImpl::setSingle(const bool &single)
{
}

void TracklistControllerImpl::shuffle(const int &start, const int &stop)
{
}

void TracklistControllerImpl::slice(const int &start, const int &stop)
{
}
