#include "corecontroller.h"
#include "mopidyparser.h"

#include <QtCore/QDebug>

using namespace Mopiqy;

CoreController::CoreController(RemoteClient *remoteClient) : ControllerInterface(remoteClient)
{ }

CoreController::~CoreController()
{ }

void CoreController::describe()
{
    QJsonObject jso = Parser::rpcEncode("core.describe");

    // send it
    sendMessage(jso, CC_DESCRIBE);
}

void CoreController::get_uri_schemes()
{
    QJsonObject jso = Parser::rpcEncode("core.get_uri_schemes");

    // send it
    sendMessage(jso, CC_URI_SCHEMES);
}

void CoreController::get_version()
{
    QJsonObject jso = Parser::rpcEncode("core.get_version");

    // send it
    sendMessage(jso, CC_VERSION);
}

void CoreController::processJsonResponse(const int &idt, const QJsonValue &jv)
{
    switch(idt)
    {
    case CC_DESCRIBE:
    {
        emit onDescribe(jv.toObject());
    }
        break;

    case CC_URI_SCHEMES:
    {
        QStringList uris;
        foreach(QJsonValue jv, jv.toArray())
            uris << jv.toString();
        emit onUriSchemes(uris);
    }
        break;

    case CC_VERSION:
    {
        emit onVersion(jv.toString());
    }
        break;

    default:
        qDebug() << "[CoreController]" << idt << jv;
        break;
    }
}
