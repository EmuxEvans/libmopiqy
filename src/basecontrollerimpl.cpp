#include "basecontrollerimpl.h"
#include "mopidyclient_p.h"


BaseControllerImpl::BaseControllerImpl(MopidyClientPrivate *parent) : m_mcp(parent)
{ }

void BaseControllerImpl::sendRequest(std::function<void (QJsonValue)> processFx, const QString &method, const QJsonObject &params)
{
    m_mcp->sendRequest(processFx, method, params);
}

void BaseControllerImpl::sendNotification(const QString &method, const QJsonObject &params)
{
    m_mcp->sendNotification(method, params);
}
