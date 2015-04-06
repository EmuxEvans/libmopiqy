#ifndef PLAYLISTSCONTROLLERIMPL_H
#define PLAYLISTSCONTROLLERIMPL_H

#include "libmopiqy/playlistscontroller.h"
#include "basecontrollerimpl.h"

class PlaylistsControllerImpl : public PlaylistsController, public BaseControllerImpl
{
    Q_OBJECT

public:
    PlaylistsControllerImpl(MopidyClientPrivate *parent);
    ~PlaylistsControllerImpl();

    // process responses
    void pr_asList(const QJsonValue &response);
    void pr_create(const QJsonValue &response);
    void pr_getItems(const QJsonValue &response);
    void pr_lookup(const QJsonValue &response);
    void pr_save(const QJsonValue &response);

public slots:
    void asList();
    void create(const QString &name, const QString &uri_scheme);
    void deletePlaylist(const QString &uri);
    void getItems(const QString &uri);
    void lookup(const QString &uri);
    void refresh(const QString &uri_scheme);
    void save(const Mopidy::Playlist &pl);
};

#endif //PLAYLISTSCONTROLLERIMPL_H
