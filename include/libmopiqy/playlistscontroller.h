#ifndef PLAYLISTSCONTROLLER_H
#define PLAYLISTSCONTROLLER_H

#include <QObject>
#include <libmopiqy/mopidymodels.h>

class LIBMOPIQY_EXPORT PlaylistsController : public QObject
{
    Q_OBJECT

public slots:
    virtual void asList() = 0;
    virtual void create(const QString &name, const QString &uri_scheme = "") = 0;
    virtual void deletePlaylist(const QString &uri) = 0;
    virtual void getItems(const QString &uri) = 0;
    virtual void lookup(const QString &uri) = 0;
    virtual void refresh(const QString &uri_scheme = "") = 0;
    virtual void save(const Mopidy::Playlist &pl) = 0;

signals:
    void asListResponse(const Mopidy::Refs &);
    void createResponse(const Mopidy::Playlist &pl);
    void getItemsResponse(const Mopidy::Refs &);
    void lookupResponse(const Mopidy::Playlist &pl);
    void saveResponse(const Mopidy::Playlist &pl);
};

#endif //PLAYLISTSCONTROLLER_H
