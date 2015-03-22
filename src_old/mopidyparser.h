#ifndef MOPIDYPARSER_H
#define MOPIDYPARSER_H

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "mopidymodels.h"

namespace Mopiqy {
    namespace Parser {

        /*
         * Encoders
         */
        QJsonObject rpcEncode(const QString &method, const QJsonValue &params = QJsonValue::Null);
        QJsonObject searchLikeEncode(const QString &method, const QHash<QString, QString> &query, const QStringList &uris);

        QJsonObject encodeModel(const Mopiqy::Models::Artist &artist);
        QJsonObject encodeModel(const Mopiqy::Models::Album &album);
        QJsonObject encodeModel(const Mopiqy::Models::Track &track);
        QJsonObject encodeModel(const Mopiqy::Models::Playlist &playlist);
        QJsonObject encodeModel(const Mopiqy::Models::TlTrack &tltrack);

        template<class T>
        QJsonArray encodeArrayOf(const QList<T> &lt);

        /*
         * Decoders
         */
        template<class T>
        QList<T> parseArrayOf(const QJsonArray &ja);

        // Parsers
        bool parseSingleObject(const QJsonObject &jo, Mopiqy::Models::Artist &artis);
        bool parseSingleObject(const QJsonObject &jo, Mopiqy::Models::Album &album);
        bool parseSingleObject(const QJsonObject &jo, Mopiqy::Models::Track &track);
        bool parseSingleObject(const QJsonObject &jo, Mopiqy::Models::Playlist &playlist);
        bool parseSingleObject(const QJsonObject &jo, Mopiqy::Models::SearchResult &searchResult);
        bool parseSingleObject(const QJsonObject &jo, Mopiqy::Models::TlTrack &tlTrack);
        bool parseSingleObject(const QJsonObject &jo, Mopiqy::Models::Ref &ref);

        // date
        QDate getMopidyDate(const QString &);
        QString toMopidyDate(const QDate &);

        // state
        Mopiqy::Core::PlaybackState getState(const QString &);

        // Ref type
        Mopiqy::Core::RefType getRefType(const QString &);

        // dict
        QJsonObject toJsonDict(const QHash<QString, QString> &);
    }
}

// Implementation
template<class T>
QJsonArray Mopiqy::Parser::encodeArrayOf(const QList<T> &lt)
{
    QJsonArray ja;

    foreach(T t, lt)
        ja.append(encodeModel(t));

    return ja;
}

template<class T>
QList<T> Mopiqy::Parser::parseArrayOf(const QJsonArray &ja)
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