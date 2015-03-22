#include "librarycontroller.h"
#include "librarycontrollerimpl.h"
#include "mopidyclient_p.h"
#include "modeltranslator.h"


LibraryControllerImpl::LibraryControllerImpl(MopidyClientPrivate *parent)
    : LibraryController(), m_mcp(parent)
{ }

LibraryControllerImpl::~LibraryControllerImpl()
{ }

void LibraryControllerImpl::pr_browse(const QJsonValue &response)
{
    Mopidy::Refs refs = ModelTranslator::fromJsonArray<Mopidy::Ref>(response.toArray());
    emit browseResult(refs);
}

void LibraryControllerImpl::pr_findExact(const QJsonValue &response)
{
    Mopidy::SearchResult sr;
    ModelTranslator::fromJson(response.toObject(), sr);
    emit findResult(sr);
}

void LibraryControllerImpl::pr_lookup(const QJsonValue &response)
{
    Mopidy::Tracks tracks = ModelTranslator::fromJsonArray<Mopidy::Track>(response.toArray());
    emit lookupResult(tracks);
}

void LibraryControllerImpl::pr_search(const QJsonValue &response)
{
    Mopidy::SearchResult sr;
    ModelTranslator::fromJson(response.toObject(), sr);
    emit searchResult(sr);
}

void LibraryControllerImpl::browse(const QString &uri)
{
    QJsonObject params;
    if(!uri.isEmpty()) params.insert("uri", uri);
    else params.insert("uri", QJsonValue::Null);

    m_mcp->sendRequest(
                std::bind(&LibraryControllerImpl::pr_browse, this, std::placeholders::_1),
                "core.library.browse", params);
}

void LibraryControllerImpl::findExact(const QHash<QString, QString> &query, const QStringList &uris)
{
//"core.library.find_exact"
}

void LibraryControllerImpl::lookup(const QString &uri)
{
    QJsonObject params;
    if(!uri.isEmpty()) params.insert("uri", uri);

    m_mcp->sendRequest(
                std::bind(&LibraryControllerImpl::pr_lookup, this, std::placeholders::_1),
                "core.library.lookup", params);
}

void LibraryControllerImpl::refresh(const QString &uri)
{
    QJsonObject params;
    if(!uri.isEmpty()) params.insert("uri", uri);

    m_mcp->sendNotification("core.library.refresh", params);
}

void LibraryControllerImpl::search(const QHash<QString, QString> &query, const QStringList &uris)
{
    // QJsonObject params;
    // params.insert(query, )

    // m_mcp->sendRequest(
    //             std::bind(&CoreControllerImpl::pr_getVersion, this, std::placeholders::_1),
    //             "core.library.search");
}



LibraryController::LibraryController(QObject *parent) : QObject(parent)
{ }

LibraryController::~LibraryController()
{ }

void LibraryController::browse(const QString &uri)
{
    Q_UNUSED(uri)
}

void LibraryController::findExact(const QHash<QString, QString> &query, const QStringList &uris)
{
    Q_UNUSED(query)
    Q_UNUSED(uris)
}

void LibraryController::lookup(const QString &uri)
{
    Q_UNUSED(uri)
}

void LibraryController::refresh(const QString &uri)
{
    Q_UNUSED(uri)
}

void LibraryController::search(const QHash<QString, QString> &query, const QStringList &uris)
{
    Q_UNUSED(query)
    Q_UNUSED(uris)
}
