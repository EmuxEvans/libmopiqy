#include "jsonwebsocket.h"

#include <QDebug>
#include <QStringList>
#include <QtConcurrent/QtConcurrentRun>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QThread>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/NetException.h>

#include <limits>

using namespace Mopidy::Internal;

class Sleeper : public QThread
{
public:
    static void msleep(unsigned long t)
    {
        QThread::msleep(t);
    }
};

JsonWebSocket::JsonWebSocket(QObject *parent) : QObject(parent)
{
    m_lastId = 0;
    m_ws = 0;
}

bool JsonWebSocket::isConnected() const
{
    return m_http_session.connected();
}

int JsonWebSocket::sendRequest(QJsonObject request, bool notification)
{
    // update to JsonRpc
    request.insert("jsonrpc", QString("2.0"));

    int id = 0;
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
    QByteArray ba2Send = jsDoc.toJson();
    m_ws->sendFrame(ba2Send.data(), ba2Send.size() * sizeof(char));

    // ...
    return id;
}

bool JsonWebSocket::openSocket(const QString &host, const qint16 &port, const QString &path)
{
    // just in case...
    if(isConnected()) closeSocket();

    // set session params
    m_http_session.setHost(host.toStdString());
    m_http_session.setPort(port);
    m_http_session.setTimeout(Poco::Timespan(10, 0));

    try
    {
        // request new session
        Poco::Net::HTTPRequest request("GET", path.toStdString());
        request.add("Upgrade", "websocket");
        Poco::Net::HTTPResponse resp;

        // let's go
        m_ws = new Poco::Net::WebSocket(m_http_session, request, resp);

        // we have websocket !
        if(resp.getStatus() == Poco::Net::HTTPResponse::HTTP_SWITCHING_PROTOCOLS)
        {
            m_stopRequest = false;
            m_futureSocketWatcher = QtConcurrent::run(this, &JsonWebSocket::socketDataWatcher);
            return true;
        }
        else
        {
            emit socketError(resp.getStatus(), QString(resp.getReason().c_str()));
            return false;
        }
    }
    catch(Poco::Exception &ex)
    {
        emit socketError(ex.code(), QString(ex.displayText().c_str()));
        return false;
    }

    // should never arrive here...
    return false;
}

void JsonWebSocket::closeSocket()
{
    m_stopRequest = true;
    m_futureSocketWatcher.waitForFinished();

    if(m_ws)
    {
        m_ws->shutdown();
        delete m_ws;
        m_ws = 0;
    }

    emit socketDisconnected();
}

void JsonWebSocket::socketDataWatcher()
{
    QByteArray baBuf;
    int flags = 0;
    int recvSize = 0;
    const int READ_BUFFER_SIZE = m_ws->getReceiveBufferSize() * sizeof(wchar_t);

    while(!m_stopRequest)
    {
        try
        {
            char res[READ_BUFFER_SIZE];
            while(m_ws->available())
            {
                recvSize = m_ws->receiveFrame(res, READ_BUFFER_SIZE, flags);
                baBuf += QByteArray::fromRawData(res, recvSize);
            }

            if(baBuf.size() > 0)
            {
                parseRawDdata(baBuf);
                baBuf.clear();
            }

            // take a break
            Sleeper::msleep(250);
        }
        catch(Poco::TimeoutException &tex)
        {
            // just a timeout, continue
            // ...
        }
        catch(Poco::Exception &ex)
        {
            // something else..., continue anyway, but log it
            // TODO: log it
            // ...
        }
    }
}

void JsonWebSocket::parseRawDdata(const QByteArray &rawData)
{
    // try to read json document
    QJsonParseError jpError;
    QJsonDocument jdoc = QJsonDocument::fromJson(rawData, &jpError);
    if(jpError.error != QJsonParseError::NoError)
    {
        emit responseError(jpError.error, jpError.errorString());
        return;
    }

    QJsonObject rootObject = jdoc.object();

    // event or answer to request ?
    if(rootObject.contains("event"))
    {
        emit eventReceived(rawData);
    }
    else
    {
        if(rootObject.contains("id") && rootObject.contains("jsonrpc"))
        {
            // we only use int id
            if(rootObject.value("id").type() == QJsonValue::String) return;

            int id = rootObject.value("id").toVariant().toInt();

            // error ?
            if(rootObject.contains("error"))
            {
                QJsonObject errObj = rootObject.value("error").toObject();

                QString errStr;
                if(errObj.contains("data"))
                    errStr = errObj.value("data").toString();

                if(errObj.contains("message"))
                    errStr += ", message: " + errObj.value("message").toString();

                emit responseError(errObj.value("code").toVariant().toInt(), errStr);
                return;
            }
            else
            {
                emit responseReceived(id, rootObject.value("result"));
            }
        }
        else
        {
            emit responseError(-1, QObject::tr("Neither a JsonRpc answer not an event..."));
            return;
        }
    }
}
