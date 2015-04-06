#ifndef MODELTRANSLATOR_H
#define MODELTRANSLATOR_H

#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>

#include "libmopiqy/mopidymodels.h"

class ModelTranslator
{
public:
    /*
     * Encoders
     */
    static QJsonObject toJson(const Mopidy::Artist &artist);
    static QJsonObject toJson(const Mopidy::Album &album);
    static QJsonObject toJson(const Mopidy::Track &track);
    static QJsonObject toJson(const Mopidy::Playlist &playlist);
    static QJsonObject toJson(const Mopidy::TlTrack &tltrack);

    template<class T>
    static QJsonArray toJsonArray(const QList<T> &lt)
    {
        QJsonArray ja;
        foreach(T t, lt)
            ja.append(toJson(t));
        return ja;
    }

    /*
     * Decoders
     */
    static bool fromJson(const QJsonObject &jo, Mopidy::Artist &artist);
    static bool fromJson(const QJsonObject &jo, Mopidy::Album &album);
    static bool fromJson(const QJsonObject &jo, Mopidy::Track &track);
    static bool fromJson(const QJsonObject &jo, Mopidy::Playlist &playlist);
    static bool fromJson(const QJsonObject &jo, Mopidy::SearchResult &searchResult);
    static bool fromJson(const QJsonObject &jo, Mopidy::TlTrack &tlTrack);
    static bool fromJson(const QJsonObject &jo, Mopidy::Ref &ref);
    static bool fromJson(const QJsonObject &jo, Mopidy::PlaybackState &state);
    static bool fromJson(const QJsonObject &jo, Mopidy::Image &image);

    template<class T>
    static QList<T> fromJsonArray(const QJsonArray &ja)
    {
        QList<T> lst;
        foreach(QJsonValue jv, ja)
        {
            QJsonObject jso = jv.toObject();
            T t;
            if(fromJson(jso, t)) lst << t;
        }
        return lst;
    }

    // date
    static QDate getMopidyDate(const QString &);
    static QString toMopidyDate(const QDate &);

    // state
    static Mopidy::PlaybackState getState(const QString &);

    // Ref type
    static Mopidy::RefType getRefType(const QString &);

    // dict
    static QJsonObject toJsonDict(const QHash<QString, QString> &);
};

#endif // MODELTRANSLATOR_H
