#include "librarycontroller.h"
#include "jsonrpchandler.h"
#include "mopidyparser.h"

using namespace Mopidy::Core;

LibraryController::LibraryController(MopidyClient *mopidyClient) : ControllerInterface(mopidyClient)
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
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.library.browse", vparams);

    // send it
    sendMessage(jso, LC_BROWSE);
}

void LibraryController::find_exact(const QHash<QString, QString> &query, const QStringList &uris)
{
    // build request
    QJsonObject jso = Mopidy::Parser::searchLikeEncode("core.library.find_exact", query, uris);

    // send it
    sendMessage(jso, LC_SEARCH);
}

void LibraryController::lookup(const QString &uri)
{
    // build request
    QJsonObject vparams;
    vparams.insert("uri", uri);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.library.lookup", vparams);

    // send it
    sendMessage(jso, LC_LOOKUP);
}

void LibraryController::refresh(const QString &uri)
{
    // build request
    QJsonObject vparams;
    if(!uri.isEmpty()) vparams.insert("uri", uri);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.library.refresh", vparams);

    // send it
    sendMessage(jso, 0, true);
}

void LibraryController::search(const QHash<QString, QString> &query, const QStringList &uris)
{
    // build request
    QJsonObject jso = Mopidy::Parser::searchLikeEncode("core.library.search", query, uris);

    // send it
    sendMessage(jso, LC_SEARCH);
}

void LibraryController::processJsonResponse(const int &idt, const QJsonValue &jv)
{
    switch(idt)
    {
    case LC_FINDEXACT:
    {
        Mopidy::Models::SearchResult sr;
        Mopidy::Parser::parseSingleObject(jv.toObject(), sr);
        emit onFindExact(sr);
    }
        break;

    case LC_LOOKUP:
    {
        Mopidy::Models::Tracks tracks = Mopidy::Parser::parseArrayOf<Mopidy::Models::Track>(jv.toArray());
        emit onLookup(tracks);
    }
        break;

    case LC_SEARCH:
    {
        Mopidy::Models::SearchResult sr;
        Mopidy::Parser::parseSingleObject(jv.toArray().at(0).toObject(), sr);
        emit onSearch(sr);
    }
        break;

    case LC_BROWSE:
    {
        Mopidy::Models::Refs refs = Mopidy::Parser::parseArrayOf<Mopidy::Models::Ref>(jv.toArray());
        emit onBrowse(refs);
    }
        break;

    default:
        break;
    }
}
