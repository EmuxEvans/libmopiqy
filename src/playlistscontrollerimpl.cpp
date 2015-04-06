#include "playlistscontrollerimpl.h"
#include "modeltranslator.h"

PlaylistsControllerImpl::PlaylistsControllerImpl(MopidyClientPrivate *parent)
    : PlaylistsController(), BaseControllerImpl(parent)
{ }

PlaylistsControllerImpl::~PlaylistsControllerImpl()
{ }

void PlaylistsControllerImpl::pr_asList(const QJsonValue &response)
{
    Mopidy::Refs refs = ModelTranslator::fromJsonArray<Mopidy::Ref>(response.toArray());
    emit asListResponse(refs);
}

void PlaylistsControllerImpl::pr_create(const QJsonValue &response)
{
    Mopidy::Playlist playlist;
    if(ModelTranslator::fromJson(response.toObject(), playlist))
        emit createResponse(playlist);
}

void PlaylistsControllerImpl::pr_getItems(const QJsonValue &response)
{
    Mopidy::Refs refs = ModelTranslator::fromJsonArray<Mopidy::Ref>(response.toArray());
    emit getItemsResponse(refs);
}

void PlaylistsControllerImpl::pr_lookup(const QJsonValue &response)
{
    Mopidy::Playlist playlist;
    if(ModelTranslator::fromJson(response.toObject(), playlist))
        emit lookupResponse(playlist);
}

void PlaylistsControllerImpl::pr_save(const QJsonValue &response)
{
    Mopidy::Playlist playlist;
    if(ModelTranslator::fromJson(response.toObject(), playlist))
        emit saveResponse(playlist);
}

void PlaylistsControllerImpl::asList()
{
    sendRequest(std::bind(&PlaylistsControllerImpl::pr_asList, this, std::placeholders::_1),
                "core.playlists.as_list");
}

void PlaylistsControllerImpl::create(const QString &name, const QString &uri_scheme)
{
    QJsonObject params;
    params.insert("name", name);
    params.insert("uri_scheme", uri_scheme);

    sendRequest(std::bind(&PlaylistsControllerImpl::pr_create, this, std::placeholders::_1),
                "core.playlists.create", params);
}

void PlaylistsControllerImpl::deletePlaylist(const QString &uri)
{
    QJsonObject params;
    params.insert("uri", uri);

    sendNotification("core.playlists.delete", params);
}

void PlaylistsControllerImpl::getItems(const QString &uri)
{
    QJsonObject params;
    params.insert("uri", uri);

    sendRequest(std::bind(&PlaylistsControllerImpl::pr_getItems, this, std::placeholders::_1),
                "core.playlists.get_items", params);
}

void PlaylistsControllerImpl::lookup(const QString &uri)
{
    QJsonObject params;
    params.insert("uri", uri);

    sendRequest(std::bind(&PlaylistsControllerImpl::pr_lookup, this, std::placeholders::_1),
                "core.playlists.lookup", params);
}

void PlaylistsControllerImpl::refresh(const QString &uri_scheme)
{
    QJsonObject params;
    params.insert("uri_scheme", uri_scheme);

    sendNotification("core.playlists.refresh", params);
}

void PlaylistsControllerImpl::save(const Mopidy::Playlist &pl)
{
    QJsonObject params;
    params.insert("playlist", ModelTranslator::toJson(pl));

    sendRequest(std::bind(&PlaylistsControllerImpl::pr_save, this, std::placeholders::_1),
                "core.playlists.save", params);
}
