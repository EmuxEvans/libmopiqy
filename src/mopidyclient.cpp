#include "mopidyclient.h"
#include "mopidyparser.h"

#include <QJsonDocument>

using namespace Mopidy;

MopidyClient::MopidyClient(QObject *parent) : QObject(parent)
{
    m_webSocket = new QWebSocket("libmopiqy", QWebSocketProtocol::VersionLatest, this);

    connect(m_webSocket, &QWebSocket::connected, this, &MopidyClient::clientConnected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &MopidyClient::clientDisconnected);
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &MopidyClient::onTextMessageReceived);
    connect(m_webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}

MopidyClient::~MopidyClient()
{
}

QString MopidyClient::clientVersion() const
{
    return LIBMOPIQY_VERSION;
}

void MopidyClient::connectTo(const QString &host, const qint16 &port, const QString &path)
{
    disconnectClient();

    // create connection
    QUrl url = QUrl::fromUserInput(host);
    url.setScheme("ws");
    url.setPort(port);
    url.setPath(path);
    m_webSocket->open(url);
}

void MopidyClient::disconnectClient()
{
    if(m_webSocket->state() == QAbstractSocket::ConnectedState)
        m_webSocket->close();
}

QString MopidyClient::sendRequest(QJsonObject request, const bool &isNotification, Mopidy::Core::ControllerInterface *ci)
{
    QString id("");

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

void MopidyClient::onTextMessageReceived(const QString &rawData)
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

void MopidyClient::onSocketError(QAbstractSocket::SocketError error)
{
    emit connectionError(error, m_webSocket->errorString());
}

void MopidyClient::parseEvent(const QJsonObject &eventObj)
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
        emit playback_state_changed(Mopidy::Parser::getState(os), Mopidy::Parser::getState(ns));
    }
    else if(evtName == "playlist_changed")
    {
        Mopidy::Models::Playlist pl;
        Mopidy::Parser::parseSingleObject(eventObj.value("playlist").toObject(), pl);
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
        Mopidy::Models::TlTrack tlt;
        Mopidy::Parser::parseSingleObject(eventObj.value("tl_track").toObject(), tlt);
        int tp = eventObj.value("time_position").toDouble();
        emit track_playback_ended(tlt, tp);
    }
    else if(evtName == "track_playback_paused")
    {
        Mopidy::Models::TlTrack tlt;
        Mopidy::Parser::parseSingleObject(eventObj.value("tl_track").toObject(), tlt);
        int tp = eventObj.value("time_position").toDouble();
        emit track_playback_paused(tlt, tp);
    }
    else if(evtName == "track_playback_resumed")
    {
        Mopidy::Models::TlTrack tlt;
        Mopidy::Parser::parseSingleObject(eventObj.value("tl_track").toObject(), tlt);
        int tp = eventObj.value("time_position").toDouble();
        emit track_playback_resumed(tlt, tp);
    }
    else if(evtName == "track_playback_started")
    {
        Mopidy::Models::TlTrack tlt;
        Mopidy::Parser::parseSingleObject(eventObj.value("tl_track").toObject(), tlt);
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

void MopidyClient::parseResponse(const QString &id, const QJsonValue &responseValue)
{
    if(m_mapMsg.contains(id))
    {
        Core::ControllerInterface *ci = m_mapMsg.take(id);
        ci->processResponse(id, responseValue);
    }
}

QString MopidyClient::generateRandomString()
{
    return "azerty";
}
