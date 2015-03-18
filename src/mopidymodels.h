#ifndef MOPIDYMODELS_H
#define MOPIDYMODELS_H

#include <QtCore/QDate>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "libmopiqy_export.h"

namespace Mopidy {

    enum class PlaybackState {
        Paused,
        Playing,
        Stopped
    };

    enum class RefType {
        Album,
        Artist,
        Directory,
        Playlist,
        Track
    };

    struct LIBMOPIQY_EXPORT Artist
    {
        QString uri;
        QString name;
        QString musicbrainz_id;
    };
    typedef QList<Artist> Artists;

    struct LIBMOPIQY_EXPORT Album
    {
        QString uri;
        QString name;
        Artists artists;
        int num_tracks;
        int num_discs;
        QDate date;
        QString musicbrainz_id;
        QStringList images;
    };
    typedef QList<Album> Albums;

    struct LIBMOPIQY_EXPORT Track
    {
        QString uri;
        QString name;
        Artists artists;
        Album album;
        int track_no;
        int disc_no;
        QDate date;
        int length;
        int bitrate;
        QString musicbrainz_id;
    };
    typedef QList<Track> Tracks;

    struct LIBMOPIQY_EXPORT Playlist
    {
        QString uri;
        QString name;
        Tracks tracks;
        QDate last_modified;
    };
    typedef QList<Playlist> Playlists;

    struct LIBMOPIQY_EXPORT SearchResult
    {
        QString uri;
        Tracks tracks;
        Albums albums;
        Artists artists;
    };

    struct LIBMOPIQY_EXPORT TlTrack
    {
        int tlid;
        Track track;

        TlTrack()
        {
            tlid = -1;
        }
    };
    typedef QList<TlTrack> TlTracks;

    /*
     * New since 0.18
     */
    struct LIBMOPIQY_EXPORT Ref
    {
        QString uri;
        QString name;
        RefType type;
    };
    typedef QList<Ref> Refs;
}

#endif // MOPIDYMODELS_H
