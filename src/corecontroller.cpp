#include "corecontroller.h"
#include "corecontrollerimpl.h"
#include "mopidyclient_p.h"

#include <QJsonArray>

CoreControllerImpl::CoreControllerImpl(MopidyClientPrivate *parent)
    : CoreController(), m_mcp(parent)
{

}

CoreControllerImpl::~CoreControllerImpl()
{

}

void CoreControllerImpl::pr_describe(const QJsonValue &response)
{
    emit describeReceived(response.toObject());
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

/*
 *
 *
 *
 */
CoreController::CoreController(QObject *parent) : QObject(parent)
{ }

CoreController::~CoreController()
{ }

void CoreController::describe()
{ }

void CoreController::getUriSchemes()
{ }

void CoreController::getVersion()
{ }

//void CoreController::processJsonResponse(const int &idt, const QJsonValue &jv)
//{
//    switch(idt)
//    {
//    case CC_DESCRIBE:
//    {
//        emit onDescribe(jv.toObject());
//    }
//        break;

//    case CC_URI_SCHEMES:
//    {
//        QStringList uris;
//        foreach(QJsonValue jv, jv.toArray())
//            uris << jv.toString();
//        emit onUriSchemes(uris);
//    }
//        break;

//    case CC_VERSION:
//    {
//        emit onVersion(jv.toString());
//    }
//        break;

//    default:
//        qDebug() << "[CoreController]" << idt << jv;
//        break;
//    }
//}
