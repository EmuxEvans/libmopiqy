#ifndef MOPIDYMODELFACTORY_H
#define MOPIDYMODELFACTORY_H

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "mopidymodels.h"

class MopidyModelFactory
{
public:
    /*
     * Encoders
     */
    //QJsonObject searchLikeEncode(const QString &method, const QHash<QString, QString> &query, const QStringList &uris);

    QJsonObject encodeModel(const Mopidy::Artist &artist);
    QJsonObject encodeModel(const Mopidy::Album &album);
    QJsonObject encodeModel(const Mopidy::Track &track);
    QJsonObject encodeModel(const Mopidy::Playlist &playlist);
    QJsonObject encodeModel(const Mopidy::TlTrack &tltrack);

    template<class T>
    QJsonArray encodeArrayOf(const QList<T> &lt)
    {
        QJsonArray ja;
        foreach(T t, lt)
            ja.append(encodeModel(t));
        return ja;
    }

    /*
     * Decoders
     */
    template<class T>
    QList<T> parseArrayOf(const QJsonArray &ja)
    {
        QList<T> lst;
        bool convOk;

        foreach(QJsonValue jv, ja)
        {
            QJsonObject jso = jv.toObject();

            if(jso.contains("__model__"))
            {
                T t;
                convOk = parseSingleObject(jso, t);
                if(convOk) lst << t;
            }
        }

        return lst;
    }

    // Parsers
    bool parseSingleObject(const QJsonObject &jo, Mopidy::Artist &artist);
    bool parseSingleObject(const QJsonObject &jo, Mopidy::Album &album);
    bool parseSingleObject(const QJsonObject &jo, Mopidy::Track &track);
    bool parseSingleObject(const QJsonObject &jo, Mopidy::Playlist &playlist);
    bool parseSingleObject(const QJsonObject &jo, Mopidy::SearchResult &searchResult);
    bool parseSingleObject(const QJsonObject &jo, Mopidy::TlTrack &tlTrack);
    bool parseSingleObject(const QJsonObject &jo, Mopidy::Ref &ref);

    // date
    QDate getMopidyDate(const QString &);
    QString toMopidyDate(const QDate &);

    // state
    Mopidy::PlaybackState getState(const QString &);

    // Ref type
    Mopidy::RefType getRefType(const QString &);

    // dict
    QJsonObject toJsonDict(const QHash<QString, QString> &);
};

#endif // MOPIDYMODELFACTORY_H
