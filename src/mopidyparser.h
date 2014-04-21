#ifndef MOPIDYPARSER_H
#define MOPIDYPARSER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QDebug>

#include <QStringList>
#include <QString>

#include "mopidymodels.h"

namespace Mopidy {
    namespace Parser {

        /*
         * Encoders
         */
        QJsonObject rpcEncode(const QString &method, const QJsonValue &params = QJsonValue::Null);
        QJsonObject searchLikeEncode(const QString &method, const QHash<QString, QString> &query, const QStringList &uris);

        QJsonObject encodeModel(const Mopidy::Models::Artist &artist);
        QJsonObject encodeModel(const Mopidy::Models::Album &album);
        QJsonObject encodeModel(const Mopidy::Models::Track &track);
        QJsonObject encodeModel(const Mopidy::Models::Playlist &playlist);
        QJsonObject encodeModel(const Mopidy::Models::TlTrack &tltrack);

        template<class T>
        QJsonArray encodeArrayOf(const QList<T> &lt);

        /*
         * Decoders
         */
        template<class T>
        QList<T> parseArrayOf(const QJsonArray &ja);

        // Parsers
        bool parseSingleObject(const QJsonObject &jo, Mopidy::Models::Artist &artis);
        bool parseSingleObject(const QJsonObject &jo, Mopidy::Models::Album &album);
        bool parseSingleObject(const QJsonObject &jo, Mopidy::Models::Track &track);
        bool parseSingleObject(const QJsonObject &jo, Mopidy::Models::Playlist &playlist);
        bool parseSingleObject(const QJsonObject &jo, Mopidy::Models::SearchResult &searchResult);
        bool parseSingleObject(const QJsonObject &jo, Mopidy::Models::TlTrack &tlTrack);
        bool parseSingleObject(const QJsonObject &jo, Mopidy::Models::Ref &ref);

        // date
        QDate getMopidyDate(const QString &);
        QString toMopidyDate(const QDate &);

        // state
        Mopidy::Core::PlaybackState getState(const QString &);

        // dict
        QJsonObject toJsonDict(const QHash<QString, QString> &);
    }
}

// Implementation
template<class T>
QJsonArray Mopidy::Parser::encodeArrayOf(const QList<T> &lt)
{
    QJsonArray ja;

    foreach(T t, lt)
        ja.append(encodeModel(t));

    return ja;
}

template<class T>
QList<T> Mopidy::Parser::parseArrayOf(const QJsonArray &ja)
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

#endif // MOPIDYPARSER_H
