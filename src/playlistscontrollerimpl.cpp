#include "playlistscontrollerimpl.h"

PlaylistsControllerImpl::PlaylistsControllerImpl(MopidyClientPrivate *parent)
    : PlaylistsController(), m_mcp(parent)
{ }

PlaylistsControllerImpl::~PlaylistsControllerImpl()
{ }

void PlaylistsControllerImpl::pr_asList(const QJsonValue &response)
{

}

void PlaylistsControllerImpl::pr_create(const QJsonValue &response)
{

}

void PlaylistsControllerImpl::pr_deletePlaylist(const QJsonValue &response)
{

}

void PlaylistsControllerImpl::pr_getItems(const QJsonValue &response)
{

}

void PlaylistsControllerImpl::pr_lookup(const QJsonValue &response)
{

}

void PlaylistsControllerImpl::pr_refresh(const QJsonValue &response)
{

}

void PlaylistsControllerImpl::pr_save(const QJsonValue &response)
{

}

void PlaylistsControllerImpl::asList()
{

}

void PlaylistsControllerImpl::create(const QString &name, const QString &uri_scheme)
{

}

void PlaylistsControllerImpl::deletePlaylist(const QString &uri)
{

}

void PlaylistsControllerImpl::getItems(const QString &uri)
{

}

void PlaylistsControllerImpl::lookup(const QString &uri)
{

}

void PlaylistsControllerImpl::refresh(const QString &uri_scheme)
{

}

void PlaylistsControllerImpl::save(const Mopidy::Playlist &pl)
{

}
