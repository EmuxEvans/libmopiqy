#include "tracklistcontrollerimpl.h"
#include "modeltranslator.h"

TracklistControllerImpl::TracklistControllerImpl(MopidyClientPrivate *parent)
    : TracklistController(), BaseControllerImpl(parent)
{ }

TracklistControllerImpl::~TracklistControllerImpl()
{ }

void TracklistControllerImpl::pr_add(const QJsonValue &response)
{
    Mopidy::TlTracks tracks = ModelTranslator::fromJsonArray<Mopidy::TlTrack>(response.toArray());
    emit addDone(tracks);
}

void TracklistControllerImpl::pr_eotTrack(const QJsonValue &response)
{
    Mopidy::TlTrack tlTrack;
    if(ModelTranslator::fromJson(response.toObject(), tlTrack))
        emit eotTrackReceived(tlTrack);
}

void TracklistControllerImpl::pr_filter(const QJsonValue &response)
{
    Mopidy::TlTracks tracks = ModelTranslator::fromJsonArray<Mopidy::TlTrack>(response.toArray());
    emit filterDone(tracks);
}

void TracklistControllerImpl::pr_consume(const QJsonValue &response)
{
    emit consumeReceived(response.toBool());
}

void TracklistControllerImpl::pr_length(const QJsonValue &response)
{
    emit lengthReceived(response.toInt());
}

void TracklistControllerImpl::pr_random(const QJsonValue &response)
{
    emit randomReceived(response.toBool());
}

void TracklistControllerImpl::pr_repeat(const QJsonValue &response)
{
    emit repeatReceived(response.toBool());
}

void TracklistControllerImpl::pr_single(const QJsonValue &response)
{
    emit singleReceived(response.toBool());
}

void TracklistControllerImpl::pr_tlTracks(const QJsonValue &response)
{
    Mopidy::TlTracks tracks = ModelTranslator::fromJsonArray<Mopidy::TlTrack>(response.toArray());
    emit tlTracksReceived(tracks);
}

void TracklistControllerImpl::pr_tracks(const QJsonValue &response)
{
    Mopidy::Tracks tracks = ModelTranslator::fromJsonArray<Mopidy::Track>(response.toArray());
    emit tracksReceived(tracks);
}

void TracklistControllerImpl::pr_version(const QJsonValue &response)
{
    emit versionReceived(response.toInt());
}

void TracklistControllerImpl::pr_index(const QJsonValue &response)
{
    emit indexReceived(response.toInt());
}

void TracklistControllerImpl::pr_nextTrack(const QJsonValue &response)
{
    Mopidy::TlTrack tltrack;
    if(ModelTranslator::fromJson(response.toObject(), tltrack))
        emit nextTrackReceived(tltrack);
}

void TracklistControllerImpl::pr_previousTrack(const QJsonValue &response)
{
    Mopidy::TlTrack tltrack;
    if(ModelTranslator::fromJson(response.toObject(), tltrack))
        emit previousTrackReceived(tltrack);
}

void TracklistControllerImpl::pr_remove(const QJsonValue &response)
{
    Mopidy::TlTracks tracks = ModelTranslator::fromJsonArray<Mopidy::TlTrack>(response.toArray());
    emit removeDone(tracks);
}

void TracklistControllerImpl::pr_slice(const QJsonValue &response)
{
    Mopidy::TlTrack tltrack;
    if(ModelTranslator::fromJson(response.toObject(), tltrack))
        emit sliceDone(tltrack);
}


void TracklistControllerImpl::add(const QStringList &uris, const int &atPosition)
{
    QJsonObject params;
    params.insert("uris", QJsonArray::fromStringList(uris));
    if(atPosition >= 0)
        params.insert("at_position", atPosition);

    sendRequest(std::bind(&TracklistControllerImpl::pr_add, this, std::placeholders::_1),
                "core.tracklist.add", params);
}

void TracklistControllerImpl::clear()
{
    sendNotification("core.tracklist.clear");
}

void TracklistControllerImpl::eotTrack(const Mopidy::TlTrack &tltrack)
{
    QJsonObject params;
    params.insert("tl_track", ModelTranslator::toJson(tltrack));

    sendRequest(std::bind(&TracklistControllerImpl::pr_eotTrack, this, std::placeholders::_1),
                "core.tracklist.eot_track", params);
}

void TracklistControllerImpl::filter(const QMap<QString, QVariantList> &criteria)
{
    QJsonObject params;
    for(auto itCriteria = criteria.cbegin(); itCriteria != criteria.cend(); ++itCriteria)
    {
        QJsonArray criteriaValues = QJsonArray::fromVariantList(itCriteria.value());
        params.insert(itCriteria.key(), criteriaValues);
    }

    sendRequest(std::bind(&TracklistControllerImpl::pr_filter, this, std::placeholders::_1),
                "core.tracklist.filter", params);
}

void TracklistControllerImpl::getConsume()
{
    sendRequest(std::bind(&TracklistControllerImpl::pr_consume, this, std::placeholders::_1),
                "core.tracklist.get_consume");
}

void TracklistControllerImpl::getLength()
{
    sendRequest(std::bind(&TracklistControllerImpl::pr_length, this, std::placeholders::_1),
                "core.tracklist.get_length");
}

void TracklistControllerImpl::getRandom()
{
    sendRequest(std::bind(&TracklistControllerImpl::pr_random, this, std::placeholders::_1),
                "core.tracklist.get_random");
}

void TracklistControllerImpl::getRepeat()
{
    sendRequest(std::bind(&TracklistControllerImpl::pr_repeat, this, std::placeholders::_1),
                "core.tracklist.get_repeat");
}

void TracklistControllerImpl::getSingle()
{
    sendRequest(std::bind(&TracklistControllerImpl::pr_single, this, std::placeholders::_1),
                "core.tracklist.get_single");
}

void TracklistControllerImpl::getTlTracks()
{
    sendRequest(std::bind(&TracklistControllerImpl::pr_tlTracks, this, std::placeholders::_1),
                "core.tracklist.get_tl_tracks");
}

void TracklistControllerImpl::getTracks()
{
    sendRequest(std::bind(&TracklistControllerImpl::pr_tracks, this, std::placeholders::_1),
                "core.tracklist.get_tracks");
}

void TracklistControllerImpl::getVersion()
{
    sendRequest(std::bind(&TracklistControllerImpl::pr_version, this, std::placeholders::_1),
                "core.tracklist.get_version");
}

void TracklistControllerImpl::index(const Mopidy::TlTrack &tltrack)
{
    QJsonObject params;
    params.insert("tl_track", ModelTranslator::toJson(tltrack));

    sendRequest(std::bind(&TracklistControllerImpl::pr_index, this, std::placeholders::_1),
                "core.tracklist.index", params);
}

void TracklistControllerImpl::move(const int &start, const int &end, const int &toPosition)
{
    QJsonObject params;
    params.insert("start", start);
    params.insert("end", end);
    params.insert("to_position", toPosition);

    sendNotification("core.tracklist.move", params);
}

void TracklistControllerImpl::nextTrack(const Mopidy::TlTrack &tltrack)
{
    QJsonObject params;
    if(tltrack.tlid >= 0)
        params.insert("tl_track", ModelTranslator::toJson(tltrack));
    else
        params.insert("tl_track", QJsonValue::Null);

    sendRequest(std::bind(&TracklistControllerImpl::pr_nextTrack, this, std::placeholders::_1),
                "core.tracklist.next_track", params);
}

void TracklistControllerImpl::previousTrack(const Mopidy::TlTrack &tltrack)
{
    QJsonObject params;
    if(tltrack.tlid >= 0)
        params.insert("tl_track", ModelTranslator::toJson(tltrack));
    else
        params.insert("tl_track", QJsonValue::Null);

    sendRequest(std::bind(&TracklistControllerImpl::pr_previousTrack, this, std::placeholders::_1),
                "core.tracklist.previous_track", params);
}

void TracklistControllerImpl::remove(const QMap<QString, QVariantList> &criteria)
{
    QJsonObject params;
    for(auto itCriteria = criteria.cbegin(); itCriteria != criteria.cend(); ++itCriteria)
    {
        QJsonArray criteriaValues = QJsonArray::fromVariantList(itCriteria.value());
        params.insert(itCriteria.key(), criteriaValues);
    }

    sendRequest(std::bind(&TracklistControllerImpl::pr_remove, this, std::placeholders::_1),
                "core.tracklist.remove", params);
}

void TracklistControllerImpl::setConsume(const bool &consume)
{
    QJsonObject params;
    params.insert("consume", consume);

    sendNotification("core.tracklist.set_consome", params);
}

void TracklistControllerImpl::setRandom(const bool &random)
{
    QJsonObject params;
    params.insert("random", random);

    sendNotification("core.tracklist.set_random", params);
}

void TracklistControllerImpl::setRepeat(const bool &repeat)
{
    QJsonObject params;
    params.insert("repeat", repeat);

    sendNotification("core.tracklist.set_repeat", params);
}

void TracklistControllerImpl::setSingle(const bool &single)
{
    QJsonObject params;
    params.insert("single", single);

    sendNotification("core.tracklist.set_single", params);
}

void TracklistControllerImpl::shuffle(const int &start, const int &stop)
{
    QJsonObject params;
    params.insert("start", start >= 0 ? start : QJsonValue::Null);
    params.insert("stop", stop >= 0 ? stop : QJsonValue::Null);

    sendNotification("core.tracklist.shuffle", params);
}

void TracklistControllerImpl::slice(const int &start, const int &stop)
{
    QJsonObject params;
    params.insert("start", start);
    params.insert("stop", stop);

    sendRequest(std::bind(&TracklistControllerImpl::pr_slice, this, std::placeholders::_1),
                "core.tracklist.slice", params);
}
