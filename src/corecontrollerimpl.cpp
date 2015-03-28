#include "corecontrollerimpl.h"
#include "mopidyclient_p.h"

#include <QJsonArray>
#include <QJsonDocument>

CoreController::CoreController(QObject *parent) : QObject(parent)
{ }

CoreControllerImpl::CoreControllerImpl(MopidyClientPrivate *parent)
    : CoreController(), m_mcp(parent)
{ }

CoreControllerImpl::~CoreControllerImpl()
{ }

void CoreControllerImpl::pr_describe(const QJsonValue &response)
{
    QJsonDocument jdoc(response.toObject());
    emit describeReceived(jdoc.toJson());
}

void CoreControllerImpl::pr_getUriSchemes(const QJsonValue &response)
{
    QStringList uris;
    foreach(QJsonValue jv, response.toArray())
        uris << jv.toString();
    emit uriSchemesReceived(uris);
}

void CoreControllerImpl::pr_getVersion(const QJsonValue &response)
{
    emit versionReceived(response.toString());
}

void CoreControllerImpl::describe()
{
    m_mcp->sendRequest(
                std::bind(&CoreControllerImpl::pr_describe, this, std::placeholders::_1),
                "core.describe");
}

void CoreControllerImpl::getUriSchemes()
{
    m_mcp->sendRequest(
                std::bind(&CoreControllerImpl::pr_getUriSchemes, this, std::placeholders::_1),
                "core.get_uri_schemes");
}

void CoreControllerImpl::getVersion()
{
    m_mcp->sendRequest(
                std::bind(&CoreControllerImpl::pr_getVersion, this, std::placeholders::_1),
                "core.get_version");
}
