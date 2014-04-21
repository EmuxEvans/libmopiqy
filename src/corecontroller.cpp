#include "corecontroller.h"
#include "jsonrpchandler.h"
#include "mopidyparser.h"

using namespace Mopidy::Core;
using namespace Mopidy::Internal;

CoreController::CoreController(JsonRpcHandler *jrHandler, QObject *parent) : QObject(parent), ControllerInterface(jrHandler)
{ }

CoreController::~CoreController()
{ }

void CoreController::describe()
{
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.describe");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, CC_DESCRIBE);
}

void CoreController::get_uri_schemes()
{
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.get_uri_schemes");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, CC_URI_SCHEMES);
}

void CoreController::get_version()
{
    QJsonObject jso = Mopidy::Parser::rpcEncode("core.get_version");

    // send it
    int id = m_jrHandler->sendMessage(this, jso);

    // keep track
    m_idQuery.insert(id, CC_VERSION);
}

void CoreController::processJsonResponse(const int &id, const QJsonValue &jv)
{
    if(m_idQuery.contains(id))
    {
        int idt = m_idQuery.take(id);
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
            qDebug() << "[CoreController]" << id << jv;
            break;
        }
    }
    else
    {
        qDebug() << tr("unmanaged query [CoreController]") << id << jv;
    }
}
