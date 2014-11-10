#ifndef MOPIDYMODELS_H
#define MOPIDYMODELS_H

#include <QtCore/QDate>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "mopiqy_export.h"

namespace Mopiqy {

    namespace Core {
        enum PlaybackState {
            PAUSED,
            PLAYING,
            STOPPED
        };

        enum RefType {
            ALBUM,
            ARTIST,
            DIRECTORY,
            PLAYLIST,
            TRACK
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
            Core::RefType type;
        };
        typedef QList<Ref> Refs;
    }
}

// allow cast with QVariant
Q_DECLARE_METATYPE(Mopiqy::Models::Artist)
Q_DECLARE_METATYPE(Mopiqy::Models::Album)
Q_DECLARE_METATYPE(Mopiqy::Models::Track)
Q_DECLARE_METATYPE(Mopiqy::Models::Playlist)
Q_DECLARE_METATYPE(Mopiqy::Models::SearchResult)
Q_DECLARE_METATYPE(Mopiqy::Models::TlTrack)
Q_DECLARE_METATYPE(Mopiqy::Models::Ref)

#endif // MOPIDYMODELS_H
