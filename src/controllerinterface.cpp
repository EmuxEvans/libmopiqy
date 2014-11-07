#include "controllerinterface.h"
#include "mopidyclient.h"

using namespace Mopidy::Core;

ControllerInterface::ControllerInterface(MopidyClient *mopidyClient) : QObject(mopidyClient)
{
    m_client = mopidyClient;
}

void ControllerInterface::processResponse(const QString &id, const QJsonValue &jv)
{
    if(m_idQuery.contains(id))
    {
        int idt = m_idQuery.take(id);
        processJsonResponse(idt, jv);
    }
}

void ControllerInterface::sendMessage(const QJsonObject &msg, const int &requestType, bool notification)
{
    if(m_client)
    {
        QString id = m_client->sendRequest(msg, notification, this);
        if(!notification)
        {
            m_idQuery.insert(id, requestType);
        }
    }
}
