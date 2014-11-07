#include "playlistscontroller.h"
#include "mopidyparser.h"

using namespace Mopidy::Core;

PlaylistsController::PlaylistsController(MopidyClient *mopidyClient) : ControllerInterface(mopidyClient)
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
    sendMessage(jso, PLS_CREATE);
}

void PlaylistsController::deletePl(const QString &uri)
{
    // build request
    QJsonObject vparams;
    vparams.insert("uri", uri);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.delete", vparams);

    // send it
    sendMessage(jso, 0, true);
}

void PlaylistsController::filter(const QHash<QString, QString> &criteria)
{
    // TODO: implemented but not tested
    QJsonObject vparams;
    vparams.insert("criteria", Mopidy::Parser::toJsonDict(criteria));
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.filter", vparams);

    // send it
    sendMessage(jso, PLS_FILTER);
}

void PlaylistsController::lookup(const QString &uri)
{
    // build request
    QJsonObject vparams;
    vparams.insert("uri", uri);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.lookup", vparams);

    // send it
    sendMessage(jso, PLS_LOOKUP);
}

void PlaylistsController::get_playlists(const bool &include_tracks)
{
    // build request
    QJsonObject vparams;
    vparams.insert("include_tracks", include_tracks);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.get_playlists", vparams);

    // send it
    sendMessage(jso, PLS_GETPLAYLISTS);
}

void PlaylistsController::refresh(const QString &uri)
{
    // build request
    QJsonObject vparams;
    if(!uri.isEmpty()) vparams.insert("uri_scheme", uri);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.refresh", vparams);

    // send it
    sendMessage(jso, 0, true);
}

void PlaylistsController::save(const Mopidy::Models::Playlist &pl)
{
    // build request
    QJsonObject vparams;
    vparams.insert("playlist", Mopidy::Parser::encodeModel(pl));
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.playlists.save", vparams);

    // send it
    sendMessage(jso, PLS_SAVE);
}

void PlaylistsController::processJsonResponse(const int &idt, const QJsonValue &jv)
{
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
