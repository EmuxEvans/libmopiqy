#include "playlistscontroller.h"
#include "mopidyparser.h"

#include <QtCore/QDebug>

using namespace Mopiqy;

PlaylistsController::PlaylistsController(RemoteClient *remoteClient) : ControllerInterface(remoteClient)
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
    QJsonObject jso = Parser::rpcEncode("core.playlists.create", vparams);

    // send it
    sendMessage(jso, PLS_CREATE);
}

void PlaylistsController::deletePl(const QString &uri)
{
    // build request
    QJsonObject vparams;
    vparams.insert("uri", uri);
    QJsonObject jso = Parser::rpcEncode("core.playlists.delete", vparams);

    // send it
    sendMessage(jso, 0, true);
}

void PlaylistsController::filter(const QHash<QString, QString> &criteria)
{
    // TODO: implemented but not tested
    QJsonObject vparams;
    vparams.insert("criteria", Parser::toJsonDict(criteria));
    QJsonObject jso = Parser::rpcEncode("core.playlists.filter", vparams);

    // send it
    sendMessage(jso, PLS_FILTER);
}

void PlaylistsController::lookup(const QString &uri)
{
    // build request
    QJsonObject vparams;
    vparams.insert("uri", uri);
    QJsonObject jso = Parser::rpcEncode("core.playlists.lookup", vparams);

    // send it
    sendMessage(jso, PLS_LOOKUP);
}

void PlaylistsController::get_playlists(const bool &include_tracks)
{
    // build request
    QJsonObject vparams;
    vparams.insert("include_tracks", include_tracks);
    QJsonObject jso = Parser::rpcEncode("core.playlists.get_playlists", vparams);

    // send it
    sendMessage(jso, PLS_GETPLAYLISTS);
}

void PlaylistsController::refresh(const QString &uri)
{
    // build request
    QJsonObject vparams;
    if(!uri.isEmpty()) vparams.insert("uri_scheme", uri);
    QJsonObject jso = Parser::rpcEncode("core.playlists.refresh", vparams);

    // send it
    sendMessage(jso, 0, true);
}

void PlaylistsController::save(const Models::Playlist &pl)
{
    // build request
    QJsonObject vparams;
    vparams.insert("playlist", Parser::encodeModel(pl));
    QJsonObject jso = Parser::rpcEncode("core.playlists.save", vparams);

    // send it
    sendMessage(jso, PLS_SAVE);
}

void PlaylistsController::processJsonResponse(const int &idt, const QJsonValue &jv)
{
    switch(idt)
    {
    case PLS_CREATE:
    {
        Models::Playlist pl;
        Parser::parseSingleObject(jv.toObject(), pl);
        emit onCreate(pl);
    }
        break;

    case PLS_FILTER:
    {
        Models::Playlists pls = Parser::parseArrayOf<Models::Playlist>(jv.toArray());
        emit onFilter(pls);
    }
        break;

    case PLS_LOOKUP:
    {
        Models::Playlist pl;
        Parser::parseSingleObject(jv.toObject(), pl);
        emit onLookup(pl);
    }
        break;

    case PLS_GETPLAYLISTS:
    {
        Models::Playlists pls = Parser::parseArrayOf<Models::Playlist>(jv.toArray());
        emit onGetPlaylists(pls);
    }
        break;

    case PLS_SAVE:
    {
        Models::Playlist pl;
        Parser::parseSingleObject(jv.toObject(), pl);
        emit onSave(pl);
    }
        break;

    default:
        qDebug() << "[PlaylistsController]" << idt << jv;
        break;
    }
}
