#include "mopidymodelfactory.h"

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QStringList>

#define MOPIDY_SHORT_DATE QString("yyyy")
#define MOPIDY_LONG_DATE QString("yyyy-MM-dd")

using namespace Mopidy;

/*
 * Encoder
 */
//QJsonObject Parser::searchLikeEncode(const QString &method, const QHash<QString, QString> &query, const QStringList &uris)
//{
//    QJsonObject jso;
//    jso.insert("method", method);

//    if(query.isEmpty() && uris.isEmpty())
//    {
//        return jso;
//    }
//    else
//    {
//        QJsonObject jsoParams;
//        if(!query.isEmpty()) jsoParams.insert("query", toJsonDict(query));
//        if(!uris.isEmpty()) jsoParams.insert("uris", QJsonArray::fromStringList(uris));
//        jso.insert("params", jsoParams);

//        return jso;
//    }
//}

QJsonObject MopidyModelFactory::encodeModel(const Artist &artist)
{
    QJsonObject jo;
    jo.insert("__model__", QString("Artist"));
    jo.insert("uri", artist.uri);
    jo.insert("name", artist.name);
    jo.insert("musicbrainz_id", artist.musicbrainz_id);
    return jo;
}

QJsonObject MopidyModelFactory::encodeModel(const Album &album)
{
    QJsonObject jo;
    jo.insert("__model__", QString("Album"));
    jo.insert("uri", album.uri);
    jo.insert("artists", encodeArrayOf<Artist>(album.artists));
    jo.insert("date", toMopidyDate(album.date));
    jo.insert("images", QJsonArray::fromStringList(album.images));
    jo.insert("musicbrainz_id", album.musicbrainz_id);
    jo.insert("name", album.name);
    jo.insert("num_discs", album.num_discs);
    jo.insert("num_tracks", album.num_tracks);
    return jo;
}

QJsonObject MopidyModelFactory::encodeModel(const Track &track)
{
    QJsonObject jo;
    jo.insert("__model__", QString("Track"));
    jo.insert("uri", track.uri);
    jo.insert("album", encodeModel(track.album));
    jo.insert("artists", encodeArrayOf<Artist>(track.artists));
    jo.insert("bitrate", track.bitrate);
    jo.insert("date", toMopidyDate(track.date));
    jo.insert("disc_no", track.disc_no);
    jo.insert("length", track.length);
    jo.insert("musicbrainz_id", track.musicbrainz_id);
    jo.insert("name", track.name);
    jo.insert("track_no", track.track_no);
    return jo;
}

QJsonObject MopidyModelFactory::encodeModel(const Playlist &playlist)
{
    QJsonObject jo;
    jo.insert("__model__", QString("Playlist"));
    jo.insert("uri", playlist.uri);
    jo.insert("name", playlist.name);
    jo.insert("last_modified", toMopidyDate(playlist.last_modified));
    jo.insert("tracks", encodeArrayOf<Track>(playlist.tracks));
    return jo;
}

QJsonObject MopidyModelFactory::encodeModel(const TlTrack &tltrack)
{
    QJsonObject jo;
    jo.insert("__model__", QString("TlTrack"));
    jo.insert("tlid", tltrack.tlid);
    jo.insert("track", encodeModel(tltrack.track));
    return jo;
}


/*
 * Decoders
 */
bool MopidyModelFactory::parseSingleObject(const QJsonObject &jo, Artist &artist)
{
    if(jo.value("__model__").toString() == "Artist")
    {
        artist.uri = jo.value("uri").toString();
        artist.name = jo.value("name").toString();
        artist.musicbrainz_id = jo.value("musicbrainz_id").toString();
        return true;
    }
    return false;
}

bool MopidyModelFactory::parseSingleObject(const QJsonObject &jo, Album &album)
{
    if(jo.value("__model__").toString() == "Album")
    {
        album.uri = jo.value("uri").toString();
        album.name = jo.value("name").toString();
        album.artists = parseArrayOf<Artist>(jo.value("artists").toArray());
        album.num_tracks = jo.value("num_tracks").toDouble();
        album.num_discs = jo.value("num_discs").toDouble();
        album.date = getMopidyDate(jo.value("date").toString());
        album.musicbrainz_id = jo.value("musicbrainz_id").toString();
        foreach(QJsonValue jv, jo.value("images").toArray())
            album.images << jv.toString();
        return true;
    }
    return false;
}

bool MopidyModelFactory::parseSingleObject(const QJsonObject &jo, Track &track)
{
    if(jo.value("__model__").toString() == "Track")
    {
        track.uri = jo.value("uri").toString();
        track.name = jo.value("name").toString();
        track.artists = parseArrayOf<Artist>(jo.value("artists").toArray());
        parseSingleObject(jo.value("album").toObject(), track.album);
        track.track_no = jo.value("track_no").toDouble();
        track.disc_no = jo.value("disc_no").toDouble();
        track.date = getMopidyDate(jo.value("date").toString());
        track.length = jo.value("length").toDouble();
        track.bitrate = jo.value("bitrate").toDouble();
        track.musicbrainz_id = jo.value("musicbrainz_id").toString();
        return true;
    }
    return false;
}

bool MopidyModelFactory::parseSingleObject(const QJsonObject &jo, Playlist &playlist)
{
    if(jo.value("__model__").toString() == "Playlist")
    {
        playlist.uri  = jo.value("uri").toString();
        playlist.name = jo.value("name").toString();
        playlist.tracks = parseArrayOf<Track>(jo.value("tracks").toArray());
        playlist.last_modified = getMopidyDate(jo.value("last_modified").toString());
        return true;
    }
    return false;
}

bool MopidyModelFactory::parseSingleObject(const QJsonObject &jo, SearchResult &searchResult)
{
    if(jo.value("__model__").toString() == "SearchResult")
    {
        searchResult.uri  = jo.value("uri").toString();
        searchResult.tracks = parseArrayOf<Track>(jo.value("tracks").toArray());
        searchResult.albums = parseArrayOf<Album>(jo.value("albums").toArray());
        searchResult.artists = parseArrayOf<Artist>(jo.value("artists").toArray());
        return true;
    }
    return false;
}

bool MopidyModelFactory::parseSingleObject(const QJsonObject &jo, TlTrack &tlTrack)
{
    if(jo.value("__model__").toString() == "TlTrack")
    {
        tlTrack.tlid  = jo.value("tlid").toDouble();
        parseSingleObject(jo.value("track").toObject(), tlTrack.track);
        return true;
    }
    return false;
}

bool MopidyModelFactory::parseSingleObject(const QJsonObject &jo, Ref &ref)
{
    if(jo.value("__model__").toString() == "Ref")
    {
        ref.uri = jo.value("uri").toString();
        ref.name = jo.value("name").toString();
        ref.type = getRefType(jo.value("type").toString());
        return true;
    }
    return false;
}

QDate MopidyModelFactory::getMopidyDate(const QString &strDate)
{
    if(strDate.isEmpty()) return QDate();

    if(strDate.length() == MOPIDY_SHORT_DATE.size()) return QDate::fromString(strDate, MOPIDY_SHORT_DATE);
    return QDate::fromString(strDate, MOPIDY_LONG_DATE);
}

QString MopidyModelFactory::toMopidyDate(const QDate &date)
{
    if(!date.isValid()) return "";
    if(date.isNull()) return "";
    if((date.day() == 1) && (date.month() == 1)) return date.toString(MOPIDY_SHORT_DATE);
    return date.toString(MOPIDY_LONG_DATE);
}

PlaybackState MopidyModelFactory::getState(const QString &stateStr)
{
    if(stateStr.toLower() == "paused") return PlaybackState::Paused;
    if(stateStr.toLower() == "playing") return PlaybackState::Playing;
    if(stateStr.toLower() == "stopped") return PlaybackState::Stopped;
    return PlaybackState::Stopped;
}

QJsonObject MopidyModelFactory::toJsonDict(const QHash<QString, QString> &d)
{
    QJsonObject jo;

    for(QHash<QString, QString>::const_iterator it = d.begin(); it != d.end(); ++it)
        jo.insert(it.key(), it.value());

    return jo;
}

RefType MopidyModelFactory::getRefType(const QString &typeStr)
{
    if(typeStr.toLower() == "album") return RefType::Album;
    if(typeStr.toLower() == "artist") return RefType::Artist;
    if(typeStr.toLower() == "directory") return RefType::Directory;
    if(typeStr.toLower() == "playlist") return RefType::Playlist;
    if(typeStr.toLower() == "track") return RefType::Track;
    return RefType::Directory;
}
