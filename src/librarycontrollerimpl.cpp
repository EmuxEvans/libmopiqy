#include "librarycontrollerimpl.h"
#include "modeltranslator.h"


LibraryControllerImpl::LibraryControllerImpl(MopidyClientPrivate *parent)
    : LibraryController(), BaseControllerImpl(parent)
{ }

LibraryControllerImpl::~LibraryControllerImpl()
{ }

void LibraryControllerImpl::pr_browse(const QJsonValue &response)
{
    Mopidy::Refs refs = ModelTranslator::fromJsonArray<Mopidy::Ref>(response.toArray());
    emit browseResult(refs);
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

void LibraryControllerImpl::pr_getImages(const QJsonValue &response)
{
    Mopidy::Images images = ModelTranslator::fromJsonArray<Mopidy::Image>(response.toArray());
    emit imagesResult(images);
}

void LibraryControllerImpl::browse(const QString &uri)
{
    QJsonObject params;
    if(!uri.isEmpty()) params.insert("uri", uri);
    else params.insert("uri", QJsonValue::Null);

    sendRequest(std::bind(&LibraryControllerImpl::pr_browse, this, std::placeholders::_1),
                "core.library.browse", params);
}

void LibraryControllerImpl::lookup(const QStringList &uris)
{
    QJsonObject params;
    if(!uris.isEmpty()) params.insert("uris", QJsonArray::fromStringList(uris));
    else params.insert("uris", QJsonValue::Null);

    sendRequest(std::bind(&LibraryControllerImpl::pr_lookup, this, std::placeholders::_1),
                "core.library.lookup", params);
}

void LibraryControllerImpl::refresh(const QString &uri)
{
    QJsonObject params;
    if(!uri.isEmpty()) params.insert("uri", uri);

    sendNotification("core.library.refresh", params);
}

void LibraryControllerImpl::search(const QHash<QString, QString> &query, const QStringList &uris, bool exact)
{

}

void LibraryControllerImpl::getImages(const QStringList &uris)
{
    QJsonObject params;
    params.insert("uris", QJsonArray::fromStringList(uris));

    sendRequest(std::bind(&LibraryControllerImpl::pr_getImages, this, std::placeholders::_1),
                "core.library.get_images", params);
}
