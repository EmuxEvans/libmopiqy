#include "mopidyclient.h"
#include "mopidyclient_p.h"

#include <QJsonDocument>
#include <QUuid>


MopidyClientPrivate::MopidyClientPrivate(QObject *parent) : QObject(parent)
{
    webSocket = new QWebSocket(QString("libmopiqy-%1").arg(LIBMOPIQY_VERSION));
    connect(webSocket, &QWebSocket::textMessageReceived, this, &MopidyClientPrivate::onTextMessageReceived);
    connect(webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

MopidyClientPrivate::~MopidyClientPrivate()
{
    delete webSocket;
}

void MopidyClientPrivate::onTextMessageReceived(const QString &message)
{

}

void MopidyClientPrivate::onError(QAbstractSocket::SocketError socketError)
{
    Q_Q(MopidyClient);
    emit q->connectionError(socketError, webSocket->errorString());
}


MopidyClient::MopidyClient(QObject *parent)
    : QObject(parent), d_ptr(new MopidyClientPrivate(this))
{
    connect(d_ptr->webSocket, &QWebSocket::connected, this, &MopidyClient::clientConnected);
    connect(d_ptr->webSocket, &QWebSocket::disconnected, this, &MopidyClient::clientDisconnected);
}

MopidyClient::~MopidyClient()
{
}

QString MopidyClient::clientVersion() const
{
    QString clientVersion(LIBMOPIQY_VERSION);
    if(clientVersion.isEmpty()) clientVersion = "Unknow version";
    return clientVersion;
}

void RemoteClient::connectTo(const QString &host, const qint16 &port, const QString &path)
{
    disconnectClient();

    // create connection
    QUrl url = QUrl::fromUserInput(host);
    url.setScheme("ws");
    url.setPort(port);
    url.setPath(path);
    m_webSocket->open(url);
}

void RemoteClient::disconnectClient()
{
    if(m_webSocket->state() == QAbstractSocket::ConnectedState)
        m_webSocket->close();
}

QString RemoteClient::sendRequest(QJsonObject request, const bool &isNotification, Mopiqy::ControllerInterface *ci)
{
    QString id("");

    // controller check
    if(!ci) return id;

    // update to JsonRpc
    request.insert("jsonrpc", QString("2.0"));

    if(!isNotification)
    {
        id = generateRandomString();
        request.insert("id", id);

        // append to queries list
        m_mapMsg.insert(id, ci);
    }

    /*
     * Send to socket
     */
    QJsonDocument jsDoc(request);
    QString st2Send = jsDoc.toJson(QJsonDocument::Compact);

    m_webSocket->sendTextMessage(st2Send);

    // TODO: Check what have been sent

    //
    return id;
}

void RemoteClient::onTextMessageReceived(const QString &rawData)
{
    // try to read json document
    QJsonParseError jpError;
    QJsonDocument jdoc = QJsonDocument::fromJson(rawData.toLatin1(), &jpError);
    if(jpError.error != QJsonParseError::NoError)
    {
        qCritical() << __FUNCTION__ << QObject::tr("Not a valid Json Document:") << jpError.error << jpError.errorString();
        return;
    }

    QJsonObject rootObject = jdoc.object();

    // event or answer to request ?
    if(rootObject.contains("event"))
    {
        parseEvent(rootObject);
    }
    else
    {
        if(rootObject.contains("id") && rootObject.contains("jsonrpc"))
        {
            // we only use string id
            if(rootObject.value("id").type() != QJsonValue::String) return;

            QString id = rootObject.value("id").toString();

            // error ?
            if(rootObject.contains("error"))
            {
                QJsonObject errObj = rootObject.value("error").toObject();

                QString errStr;
                if(errObj.contains("data"))
                    errStr = errObj.value("data").toString();

                if(errObj.contains("message"))
                    errStr += ", message: " + errObj.value("message").toString();

                emit messageError(errObj.value("code").toDouble(), errStr);
            }
            else
            {
                parseResponse(id, rootObject.value("result"));
            }
        }
        else
        {
            qCritical() << __FUNCTION__ << QObject::tr("Neither a JsonRpc answer not an event...");
        }
    }
}

void RemoteClient::onSocketError(QAbstractSocket::SocketError error)
{
    emit connectionError(error, m_webSocket->errorString());
}

void RemoteClient::parseEvent(const QJsonObject &eventObj)
{
    QString evtName = eventObj.value("event").toString();

    if(evtName == "options_changed")
    {
        emit options_changed();
    }
    else if(evtName == "playback_state_changed")
    {
        QString os = eventObj.value("old_state").toString();
        QString ns = eventObj.value("new_state").toString();
        emit playback_state_changed(Mopiqy::Parser::getState(os), Mopiqy::Parser::getState(ns));
    }
    else if(evtName == "playlist_changed")
    {
        Mopiqy::Models::Playlist pl;
        Mopiqy::Parser::parseSingleObject(eventObj.value("playlist").toObject(), pl);
        emit playlist_changed(pl);
    }
    else if(evtName == "playlists_loaded")
    {
        emit playlists_loaded();
    }
    else if(evtName == "seeked")
    {
        int tp = eventObj.value("time_position").toDouble();
        emit seeked(tp);
    }
    else if(evtName == "track_playback_ended")
    {
        Mopiqy::Models::TlTrack tlt;
        Mopiqy::Parser::parseSingleObject(eventObj.value("tl_track").toObject(), tlt);
        int tp = eventObj.value("time_position").toDouble();
        emit track_playback_ended(tlt, tp);
    }
    else if(evtName == "track_playback_paused")
    {
        Mopiqy::Models::TlTrack tlt;
        Mopiqy::Parser::parseSingleObject(eventObj.value("tl_track").toObject(), tlt);
        int tp = eventObj.value("time_position").toDouble();
        emit track_playback_paused(tlt, tp);
    }
    else if(evtName == "track_playback_resumed")
    {
        Mopiqy::Models::TlTrack tlt;
        Mopiqy::Parser::parseSingleObject(eventObj.value("tl_track").toObject(), tlt);
        int tp = eventObj.value("time_position").toDouble();
        emit track_playback_resumed(tlt, tp);
    }
    else if(evtName == "track_playback_started")
    {
        Mopiqy::Models::TlTrack tlt;
        Mopiqy::Parser::parseSingleObject(eventObj.value("tl_track").toObject(), tlt);
        emit track_playback_started(tlt);
    }
    else if(evtName == "tracklist_changed")
    {
        emit tracklist_changed();
    }
    else if(evtName == "volume_changed")
    {
        emit volume_changed();
    }
    else if(evtName == "mute_changed")
    {
        emit mute_changed(eventObj.value("mute").toBool());
    }
    else
    {
        qCritical() << __FUNCTION__ << QObject::tr("Unknown event:") << evtName;
    }
}

void RemoteClient::parseResponse(const QString &id, const QJsonValue &responseValue)
{
    if(m_mapMsg.contains(id))
    {
        ControllerInterface *ci = m_mapMsg.take(id);
        ci->processResponse(id, responseValue);
    }
}

QString RemoteClient::generateRandomString()
{
    QString rstr = QUuid::createUuid().toString();
    rstr.remove("{");
    rstr.remove("}");
    return rstr;
}
