#include "jsonrpchandler.h"
#include "jsonwebsocket.h"

using namespace Mopidy::Internal;
using namespace Mopidy::Core;

JsonRpcHandler::JsonRpcHandler(QObject *parent) : QObject(parent)
{
    m_socket = 0;
}

JsonRpcHandler::~JsonRpcHandler()
{
}

void JsonRpcHandler::setJsonWebSocket(JsonWebSocket *socket)
{
    m_socket = socket;
    if(socket)
    {
        connect(m_socket, &JsonWebSocket::responseReceived, this, &JsonRpcHandler::onResponse);
        connect(m_socket, &JsonWebSocket::socketDisconnected, this, &JsonRpcHandler::onSocketDisconnected);
    }
}

int JsonRpcHandler::sendMessage(ControllerInterface *ci, const QJsonObject &msg, bool notification)
{
    if(m_socket)
    {
        int id = m_socket->sendRequest(msg, notification);
        if(id != 0)
        {
            m_mapMsg.insert(id, ci);
        }
        return id;
    }
    return -1;
}

void JsonRpcHandler::onResponse(const int &id, const QJsonValue &v)
{
    if(m_mapMsg.contains(id))
    {
        ControllerInterface *ci = m_mapMsg.take(id);
        ci->processJsonResponse(id, v);
    }
}

void JsonRpcHandler::onSocketDisconnected()
{
    m_mapMsg.clear();
}
