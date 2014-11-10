#include "librarycontroller.h"
#include "mopidyparser.h"

#include <QtCore/QDebug>

using namespace Mopiqy;

LibraryController::LibraryController(RemoteClient *remoteClient) : ControllerInterface(remoteClient)
{
}

LibraryController::~LibraryController()
{
}

void LibraryController::browse(const QString &uri)
{
    // build request
    QJsonObject vparams;
    if(!uri.isEmpty())
        vparams.insert("uri", uri);
    else
        vparams.insert("uri", QJsonValue::Null);
    QJsonObject jso = Parser::rpcEncode("core.library.browse", vparams);

    // send it
    sendMessage(jso, LC_BROWSE);
}

void LibraryController::find_exact(const QHash<QString, QString> &query, const QStringList &uris)
{
    // build request
    QJsonObject jso = Parser::searchLikeEncode("core.library.find_exact", query, uris);

    // send it
    sendMessage(jso, LC_SEARCH);
}

void LibraryController::lookup(const QString &uri)
{
    // build request
    QJsonObject vparams;
    vparams.insert("uri", uri);
    QJsonObject jso = Parser::rpcEncode("core.library.lookup", vparams);

    // send it
    sendMessage(jso, LC_LOOKUP);
}

void LibraryController::refresh(const QString &uri)
{
    // build request
    QJsonObject vparams;
    if(!uri.isEmpty()) vparams.insert("uri", uri);
    QJsonObject jso = Parser::rpcEncode("core.library.refresh", vparams);

    // send it
    sendMessage(jso, 0, true);
}

void LibraryController::search(const QHash<QString, QString> &query, const QStringList &uris)
{
    // build request
    QJsonObject jso = Parser::searchLikeEncode("core.library.search", query, uris);

    // send it
    sendMessage(jso, LC_SEARCH);
}

void LibraryController::processJsonResponse(const int &idt, const QJsonValue &jv)
{
    switch(idt)
    {
    case LC_FINDEXACT:
    {
        Models::SearchResult sr;
        Parser::parseSingleObject(jv.toObject(), sr);
        emit onFindExact(sr);
    }
        break;

    case LC_LOOKUP:
    {
        Models::Tracks tracks = Parser::parseArrayOf<Models::Track>(jv.toArray());
        emit onLookup(tracks);
    }
        break;

    case LC_SEARCH:
    {
        Models::SearchResult sr;
        Parser::parseSingleObject(jv.toArray().at(0).toObject(), sr);
        emit onSearch(sr);
    }
        break;

    case LC_BROWSE:
    {
        Models::Refs refs = Parser::parseArrayOf<Models::Ref>(jv.toArray());
        emit onBrowse(refs);
    }
        break;

    default:
        qDebug() << "[LibraryController]" << idt << jv;
        break;
    }
}
