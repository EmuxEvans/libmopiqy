#ifndef MOPIDYMODELS_H
#define MOPIDYMODELS_H

#include <QDate>
#include <QList>
#include <QString>
#include <QStringList>

#include "mopiqy_export.h"

// just because 'Dict' is shorter
typedef QHash<QString, QStringList> Dict;

namespace Mopidy {

    namespace Models {

        struct MOPIQY_CORE_EXPORT Artist
        {
            QString uri;
            QString name;
            QString musicbrainz_id;
        };
        typedef QList<Artist> Artists;

        struct MOPIQY_CORE_EXPORT Album
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

        struct MOPIQY_CORE_EXPORT Track
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

        struct MOPIQY_CORE_EXPORT Playlist
        {
            QString uri;
            QString name;
            Tracks tracks;
            QDate last_modified;
        };
        typedef QList<Playlist> Playlists;

        struct MOPIQY_CORE_EXPORT SearchResult
        {
            QString uri;
            Tracks tracks;
            Albums albums;
            Artists artists;
        };

        struct  MOPIQY_CORE_EXPORT TlTrack
        {
            int tlid;
            Track track;
        };
        typedef QList<TlTrack> TlTracks;
    }
}

Q_DECLARE_METATYPE(Mopidy::Models::Artist)
Q_DECLARE_METATYPE(Mopidy::Models::Album)
Q_DECLARE_METATYPE(Mopidy::Models::Track)
Q_DECLARE_METATYPE(Mopidy::Models::Playlist)
Q_DECLARE_METATYPE(Mopidy::Models::SearchResult)
Q_DECLARE_METATYPE(Mopidy::Models::TlTrack)

#endif // MOPIDYMODELS_H
