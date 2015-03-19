#ifndef JSONRPCMESSAGE_H
#define JSONRPCMESSAGE_H

/*
 * Message definition for Json-RPC protocol
 */

#include <QJsonObject>

class JsonRpcMessage
{
public:

    // Some enums
    enum class ErrorCode {
        NoError = 0,
        Parse = -32700,
        InvalidRequest = -32600,
        MethodNotFound = -32601,
        InvalidParams = -32602,
        Internal = -32603,
        Server = -32000
    };

    enum class MessageType {
        Invalid,
        Request,
        Response,
        Notification,
        Error
    };

    // ctor
    JsonRpcMessage();
    // copy constructor
    JsonRpcMessage(const JsonRpcMessage &other);
    JsonRpcMessage& operator=(const JsonRpcMessage &other);
    // dtor
    ~JsonRpcMessage();

    // builders
    static JsonRpcMessage build_request(const QString &method, const int &id, const QJsonObject &params = QJsonObject());
    static JsonRpcMessage build_notification(const QString &method, const QJsonObject &params = QJsonObject());

    // information about this message
    MessageType type() const;
    bool isValid() const;

    // request + response + error
    int id() const;

    // request + notification
    QString method() const;
    QJsonValue params() const;

    // response
    QJsonValue result() const;

    // error
    ErrorCode errorCode() const;
    QString errorMessage() const;
    QJsonValue errrorData() const;

    // parser
    QByteArray toJson() const;
    static JsonRpcMessage fromJson(const QJsonObject &jsonObj);

private:
    QJsonObject m_jsObject;
    MessageType m_msgType;
};

#endif //JSONRPCMESSAGE_H
