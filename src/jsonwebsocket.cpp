#include "jsonwebsocket.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include <limits>

using namespace Mopidy::Internal;

JsonWebSocket::JsonWebSocket(QObject *parent) : QObject(parent)
{
    m_lastId = 0;

    connect(&m_wsclient, &QWebSocket::connected, this, &JsonWebSocket::socketConnected);
    connect(&m_wsclient, &QWebSocket::disconnected, this, &JsonWebSocket::socketDisconnected);
    connect(&m_wsclient, &QWebSocket::textMessageReceived, this, &JsonWebSocket::parseRawDdata);
    connect(&m_wsclient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}

JsonWebSocket::~JsonWebSocket()
{
    closeSocket();
}

bool JsonWebSocket::isConnected() const
{
    // TODO: check it
    return m_wsclient.isValid();
}

int JsonWebSocket::sendRequest(QJsonObject request, bool notification)
{
    int id = 0;

    // update to JsonRpc
    request.insert("jsonrpc", QString("2.0"));

    if(!notification)
    {
        id = ++m_lastId;
        request.insert("id", id);

        // in case we reach int limit...
        if(m_lastId == std::numeric_limits<int>::max()) m_lastId = 0;
    }

    /*
     * Send to socket
     */
    QJsonDocument jsDoc(request);
    QString st2Send = jsDoc.toJson(QJsonDocument::Compact);

    m_wsclient.write(st2Send);

    // ...
    return id;
}

bool JsonWebSocket::openSocket(const QString &host, const qint16 &port, const QString &path)
{
    // just in case...
    if(isConnected()) closeSocket();

    // create connection
    QUrl url = QUrl::fromUserInput(host);
    url.setPort(port);
    url.setPath(path);
    m_wsclient.open(url);
    return m_wsclient.waitForConnected();
}

void JsonWebSocket::closeSocket()
{
    m_wsclient.close();
}

void JsonWebSocket::onSocketError(QAbstractSocket::SocketError error)
{
    emit socketError(error, m_wsclient.errorString());
}

void JsonWebSocket::parseRawDdata(const QString &rawData)
{
    // try to read json document
    QJsonParseError jpError;
    QJsonDocument jdoc = QJsonDocument::fromJson(rawData.toLatin1(), &jpError);
    if(jpError.error != QJsonParseError::NoError)
    {
        qCritical() << __FUNCTION__ << QObject::tr("Not a JsonDocument:") << jpError.error << jpError.errorString();
        return;
    }

    QJsonObject rootObject = jdoc.object();

    // event or answer to request ?
    if(rootObject.contains("event"))
    {
        emit eventReceived(rawData.toLatin1());
    }
    else
    {
        if(rootObject.contains("id") && rootObject.contains("jsonrpc"))
        {
            // we only use int id
            if(rootObject.value("id").type() == QJsonValue::String) return;

            int id = rootObject.value("id").toDouble();

            // error ?
            if(rootObject.contains("error"))
            {
                QJsonObject errObj = rootObject.value("error").toObject();

                QString errStr;
                if(errObj.contains("data"))
                    errStr = errObj.value("data").toString();

                if(errObj.contains("message"))
                    errStr += ", message: " + errObj.value("message").toString();

                emit responseError(errObj.value("code").toDouble(), errStr);
            }
            else
            {
                emit responseReceived(id, rootObject.value("result"));
            }
        }
        else
        {
            qCritical() << __FUNCTION__ << QObject::tr("Neither a JsonRpc answer not an event...");
        }
    }
}
