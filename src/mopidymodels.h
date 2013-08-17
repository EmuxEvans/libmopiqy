#ifndef MOPIDYMODELS_H
#define MOPIDYMODELS_H

#include <QDate>
#include <QList>
#include <QString>
#include <QStringList>

#include "mopiqy_export.h"

typedef QHash<QString, QString> Dict;

namespace Mopidy {

    namespace Core {
        enum PlaybackState {
            PAUSED,
            PLAYING,
            STOPPED
        };
    }

    namespace Models {

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

        struct  LIBMOPIQY_EXPORT TlTrack
        {
            int tlid;
            Track track;
        };
        typedef QList<TlTrack> TlTracks;
    }
}

// allow cast with QVariant
Q_DECLARE_METATYPE(Mopidy::Models::Artist)
Q_DECLARE_METATYPE(Mopidy::Models::Album)
Q_DECLARE_METATYPE(Mopidy::Models::Track)
Q_DECLARE_METATYPE(Mopidy::Models::Playlist)
Q_DECLARE_METATYPE(Mopidy::Models::SearchResult)
Q_DECLARE_METATYPE(Mopidy::Models::TlTrack)

#endif // MOPIDYMODELS_H
