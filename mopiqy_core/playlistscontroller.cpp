#include "playlistscontroller.h"
#include "jsonrpchandler.h"
#include "mopidyparser.h"

using namespace Mopidy::Core;

PlaylistsController::PlaylistsController(Mopidy::Internal::JsonRpcHandler *jrHandler, QObject *parent) : QObject(parent), ControllerInterface(jrHandler)
{
}

PlaylistsController::~PlaylistsController()
{
}

void PlaylistsController::create(const QString &name, const QString &uri_scheme)
{
    // build request
    QJsonObject vparams;
    vparams.insert("name", name);
    if(!uri_scheme.isEmpty()) vparams.insert("uri_scheme", uri_scheme);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.create", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PLS_CREATE);
}

void PlaylistsController::deletePl(const QString &uri)
{
    // build request
    QJsonObject vparams;
    vparams.insert("uri", uri);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.delete", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaylistsController::filter(const Dict &criteria)
{
    // TODO: implement PlaylistsController::filter
}

void PlaylistsController::lookup(const QString &uri)
{
    // build request
    QJsonObject vparams;
    vparams.insert("uri", uri);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.lookup", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PLS_LOOKUP);
}

void PlaylistsController::get_playlists()
{
    // build request
    QJsonObject vparams;
    vparams.insert("include_tracks", true);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.get_playlists", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PLS_GETPLAYLISTS);
}

void PlaylistsController::refresh(const QString &uri)
{
    // build request
    QJsonObject vparams;
    if(!uri.isEmpty()) vparams.insert("uri_scheme", uri);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.refresh", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void PlaylistsController::save(const Mopidy::Models::Playlist &pl)
{
    // build request
    QJsonObject vparams;
    vparams.insert("playlist", Mopidy::Parser::encodeModel(pl));
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.save", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, PLS_SAVE);
}

void PlaylistsController::processJsonResponse(const int &id, const QJsonValue &jv)
{
    if(m_idQuery.contains(id))
    {
        int idt = m_idQuery.take(id);
        switch(idt)
        {
        case PLS_CREATE:
            {
                Mopidy::Models::Playlist pl;
                Mopidy::Parser::parseSingleObject(jv.toObject(), pl);
                emit onCreate(pl);
            }
            break;

        case PLS_FILTER:
            {
                Mopidy::Models::Playlists pls = Mopidy::Parser::parseArrayOf<Mopidy::Models::Playlist>(jv.toArray());
                emit onFilter(pls);
            }
            break;

        case PLS_LOOKUP:
            {
                Mopidy::Models::Playlist pl;
                Mopidy::Parser::parseSingleObject(jv.toObject(), pl);
                emit onLookup(pl);
            }
            break;

        case PLS_GETPLAYLISTS:
            {
                Mopidy::Models::Playlists pls = Mopidy::Parser::parseArrayOf<Mopidy::Models::Playlist>(jv.toArray());
                emit onGetPlaylists(pls);
            }
            break;

        case PLS_SAVE:
            {
                Mopidy::Models::Playlist pl;
                Mopidy::Parser::parseSingleObject(jv.toObject(), pl);
                emit onSave(pl);
            }
            break;

        default:
            break;
        }
    }
}
