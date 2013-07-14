#include "tracklistcontroller.h"
#include "jsonrpchandler.h"
#include "mopidyparser.h"

using namespace Mopidy::Core;

TracklistController::TracklistController(Mopidy::Internal::JsonRpcHandler *jrHandler, QObject *parent)
    : QObject(parent), ControllerInterface(jrHandler)
{
}

TracklistController::~TracklistController()
{
}

void TracklistController::add(const Mopidy::Models::Tracks &tracks, const int &at_position)
{
    // build request
    QJsonObject vparams;
    vparams.insert("tracks", Mopidy::Parser::encodeArrayOf<Mopidy::Models::Track>(tracks));
    if(at_position > -1) vparams.insert("at_position", at_position);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.add", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, TC_ADD);
}

void TracklistController::add(const QString &uri, const int &at_position)
{
    // build request
    QJsonObject vparams;
    vparams.insert("uri", uri);
    if(at_position > -1) vparams.insert("at_position", at_position);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.add", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, TC_ADD);
}

void TracklistController::clear()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.clear");

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void TracklistController::filter(const Dict &criteria)
{
    // // TODO: implemented but not tested
    QJsonObject vparams;
    vparams.insert("criteria", Mopidy::Parser::toJsonDict(criteria));
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.filter", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, TC_FILTER);
}

void TracklistController::index(const Mopidy::Models::TlTrack &tl)
{
    // build request
    QJsonObject vparams;
    vparams.insert("tl_track", Mopidy::Parser::encodeModel(tl));
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.index", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, TC_INDEX);
}

void TracklistController::get_length()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.get_length");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, TC_GETLENGTH);
}

void TracklistController::move(const int &start, const int &end, const int &to_position)
{
    // build request
    QJsonObject vparams;
    vparams.insert("start", start);
    vparams.insert("end", end);
    vparams.insert("to_position", to_position);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.move", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void TracklistController::remove(const Dict &criteria)
{
    // TODO: implemented but not tested
    QJsonObject vparams;
    vparams.insert("criteria", Mopidy::Parser::toJsonDict(criteria));
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.index", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, TC_REMOVE);
}

void TracklistController::shuffle(const int &start, const int &end)
{
    // build request
    QJsonObject vparams;
    if(start > -1) vparams.insert("start", start);
    if(end > -1) vparams.insert("end", end);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.shuffle", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void TracklistController::slice(const int &start, const int &end)
{
    // build request
    QJsonObject vparams;
    vparams.insert("start", start);
    vparams.insert("end", end);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.slice", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, TC_SLICE);
}

void TracklistController::get_tltracks()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.get_tl_tracks");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, TC_GETTLTRACKS);
}

void TracklistController::get_tracks()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.get_tracks");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, TC_GETTRACKS);
}

void TracklistController::get_version()
{
    // build request
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.tracklist.get_version");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, TC_GETVERSION);
}

void TracklistController::processJsonResponse(const int &id, const QJsonValue &jv)
{
    if(m_idQuery.contains(id))
    {
        int idt = m_idQuery.take(id);
        switch(idt)
        {
        case TC_ADD:
            {
                Mopidy::Models::TlTracks tls = Mopidy::Parser::parseArrayOf<Mopidy::Models::TlTrack>(jv.toArray());
                emit onAdd(tls);
            }
            break;

        case TC_FILTER:
            {
                Mopidy::Models::TlTracks tls = Mopidy::Parser::parseArrayOf<Mopidy::Models::TlTrack>(jv.toArray());
                emit onFilter(tls);
            }
            break;

        case TC_INDEX:
            emit onIndex(jv.toDouble());
            break;

        case TC_GETLENGTH:
            emit onGetLength(jv.toDouble());
            break;

        case TC_REMOVE:
            {
                Mopidy::Models::TlTracks tls = Mopidy::Parser::parseArrayOf<Mopidy::Models::TlTrack>(jv.toArray());
                emit onRemove(tls);
            }
            break;

        case TC_SLICE:
            {
                Mopidy::Models::TlTrack tltrack;
                Mopidy::Parser::parseSingleObject(jv.toObject(), tltrack);
                emit onSlice(tltrack);
            }
            break;

        case TC_GETTLTRACKS:
            {
                Mopidy::Models::TlTracks tls = Mopidy::Parser::parseArrayOf<Mopidy::Models::TlTrack>(jv.toArray());
                emit onGetTlTracks(tls);
            }
            break;

        case TC_GETTRACKS:
            {
                Mopidy::Models::Tracks tracks = Mopidy::Parser::parseArrayOf<Mopidy::Models::Track>(jv.toArray());
                emit onGetTracks(tracks);
            }
            break;

        case TC_GETVERSION:
            emit onGetVersion(jv.toDouble());
            break;

        default:
            break;
        }
    }
}

