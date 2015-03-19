#include "jsonrpcmessage.h"

#include <QDebug>
#include <QJsonDocument>

// Keys used by Json-RPC protocol 2.0
const QLatin1String CSK_JSONRPC("jsonrpc");
const QLatin1String CSV_JSONRPC("2.0");
const QLatin1String CSK_METHOD("method");
const QLatin1String CSK_ID("id");
const QLatin1String CSK_PARAMS("params");
const QLatin1String CSK_RESULT("result");
const QLatin1String CSK_ERROR("error");
// error object
const QLatin1String CSE_CODE("code");
const QLatin1String CSE_MESSAGE("message");
const QLatin1String CSE_DATA("data");


JsonRpcMessage::JsonRpcMessage()
{
    m_msgType = MessageType::Invalid;
}

JsonRpcMessage::JsonRpcMessage(const JsonRpcMessage &other)
    : m_msgType(other.m_msgType), m_jsObject(other.m_jsObject)
{ }

JsonRpcMessage &JsonRpcMessage::operator=(const JsonRpcMessage &other)
{
    m_msgType = other.m_msgType;
    m_jsObject = other.m_jsObject;
    return *this;
}

JsonRpcMessage::~JsonRpcMessage()
{ }

JsonRpcMessage JsonRpcMessage::build_request(const QString &method, const int &id, const QJsonObject &params)
{
    JsonRpcMessage request;

    // sanity checks
    if(method.isEmpty())
        return request;

    // create object
    request.m_msgType = MessageType::Request;
    request.m_jsObject.insert(CSK_JSONRPC, CSV_JSONRPC);
    request.m_jsObject.insert(CSK_ID, id);
    request.m_jsObject.insert(CSK_METHOD, method);
    if(!params.isEmpty())
        request.m_jsObject.insert(CSK_PARAMS, params);
    return request;
}

JsonRpcMessage JsonRpcMessage::build_notification(const QString &method, const QJsonObject &params)
{
    JsonRpcMessage request;

    // sanity checks
    if(method.isEmpty())
        return request;

    // create object
    request.m_msgType = MessageType::Notification;
    request.m_jsObject.insert(CSK_JSONRPC, CSV_JSONRPC);
    request.m_jsObject.insert(CSK_METHOD, method);
    if(!params.isEmpty())
        request.m_jsObject.insert(CSK_PARAMS, params);
    return request;
}

JsonRpcMessage::MessageType JsonRpcMessage::type() const
{
    return m_msgType;
}

bool JsonRpcMessage::isValid() const
{
    return (m_msgType != MessageType::Invalid);
}

int JsonRpcMessage::id() const
{
    if(m_msgType == MessageType::Notification)
        return -1;

    const QJsonValue &jvId = m_jsObject.value(CSK_ID);
    if(jvId.isDouble())
        return jvId.toDouble();
    return jvId.toString().toInt();
}

QString JsonRpcMessage::method() const
{
    if(m_msgType == MessageType::Error || m_msgType == MessageType::Response)
        return QString();

    return m_jsObject.value(CSK_METHOD).toString();
}

QJsonValue JsonRpcMessage::params() const
{
    if(m_msgType == MessageType::Error || m_msgType == MessageType::Response)
        return QJsonValue(QJsonValue::Undefined);

    return m_jsObject.value(CSK_PARAMS);
}

QJsonValue JsonRpcMessage::result() const
{
    if(m_msgType != MessageType::Response)
        return QJsonValue(QJsonValue::Undefined);

    return m_jsObject.value(CSK_RESULT);

}

JsonRpcMessage::ErrorCode JsonRpcMessage::errorCode() const
{
    if(m_msgType != MessageType::Error)
        return ErrorCode::NoError;

    const QJsonObject &error = m_jsObject.value(CSK_ERROR).toObject();
    return static_cast<ErrorCode>(error.value(CSE_CODE).toInt());
}

QString JsonRpcMessage::errorMessage() const
{
    if(m_msgType != MessageType::Error)
        return QString();

    const QJsonObject &error = m_jsObject.value(CSK_ERROR).toObject();
    return error.value(CSE_MESSAGE).toString();
}

QJsonValue JsonRpcMessage::errrorData() const
{
    if(m_msgType != MessageType::Error)
        return QString();

    const QJsonObject &error = m_jsObject.value(CSK_ERROR).toObject();
    return error.value(CSE_DATA);
}

QByteArray JsonRpcMessage::toJson() const
{
    QJsonDocument jdoc(m_jsObject);
    return jdoc.toJson(QJsonDocument::Compact);
}

JsonRpcMessage JsonRpcMessage::fromJson(const QJsonObject &jsonObj)
{
    JsonRpcMessage message;

    // sanity checks
    if(!jsonObj.contains(CSK_JSONRPC)
            || jsonObj.value(CSK_JSONRPC).toString() != CSV_JSONRPC)
    {
        qCritical() << Q_FUNC_INFO << "Invalid message";
        return message;
    }

    // extract message type
    if(jsonObj.contains(CSK_ID))
    {
        if(jsonObj.contains(CSK_ERROR))
        {
            message.m_msgType = MessageType::Error;
        }
        else if(jsonObj.contains(CSK_RESULT))
        {
            message.m_msgType = MessageType::Response;
        }
        else if(jsonObj.contains(CSK_METHOD))
        {
            message.m_msgType = MessageType::Request;
        }
    }
    else
    {
        if(jsonObj.contains(CSK_METHOD))
        {
            message.m_msgType = MessageType::Notification;
        }
    }

    // save object
    message.m_jsObject = jsonObj;

    //
    return message;
}
