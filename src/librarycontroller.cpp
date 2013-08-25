#include "librarycontroller.h"
#include "jsonrpchandler.h"
#include "mopidyparser.h"

using namespace Mopidy::Core;

LibraryController::LibraryController(Mopidy::Internal::JsonRpcHandler *jrHandler, QObject *parent)
    : QObject(parent), ControllerInterface(jrHandler)
{
}

LibraryController::~LibraryController()
{
}

void LibraryController::find_exact(const QHash<QString, QString> &query, const QStringList &uris)
{
    // build request
    QJsonObject jso = Mopidy::Parser::searchLikeEncode("core.library.find_exact", query, uris);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, LC_SEARCH);
}

void LibraryController::lookup(const QString &uri)
{
    // build request
    QJsonObject vparams;
    vparams.insert("uri", uri);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.library.lookup", vparams);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, LC_LOOKUP);
}

void LibraryController::refresh(const QString &uri)
{
    // build request
    QJsonObject vparams;
    if(!uri.isEmpty()) vparams.insert("uri", uri);
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.library.refresh", vparams);

    // send it
    m_jrHandler->sendMessage(this, jso, true);
}

void LibraryController::search(const QHash<QString, QString> &query, const QStringList &uris)
{
    // build request
    QJsonObject jso = Mopidy::Parser::searchLikeEncode("core.library.search", query, uris);

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, LC_SEARCH);
}

void LibraryController::processJsonResponse(const int &id, const QJsonValue &jv)
{
    if(m_idQuery.contains(id))
    {
        int idt = m_idQuery.take(id);
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

        default:
            break;
        }
    }
}
