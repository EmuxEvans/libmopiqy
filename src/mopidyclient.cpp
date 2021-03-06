#include "libmopiqy/mopidyclient.h"
#include "mopidyclient_p.h"
#include "jsonrpcmessage.h"
#include "modeltranslator.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>


MopidyClientPrivate::MopidyClientPrivate(MopidyClient *parent)
    : QObject(parent), q_ptr(parent),
      coreController(new CoreControllerImpl(this)),
      historyController(new HistoryControllerImpl(this)),
      libraryController(new LibraryControllerImpl(this)),
      mixerController(new MixerControllerImpl(this)),
      playbackController(new PlaybackControllerImpl(this)),
      playlistsController(new PlaylistsControllerImpl(this)),
      tracklistController(new TracklistControllerImpl(this))
{
    m_lastRequestID = 0;
    webSocket = new QWebSocket(QString("libmopiqy-%1").arg(GIT_VERSION));
    connect(webSocket, &QWebSocket::textMessageReceived, this, &MopidyClientPrivate::onTextMessageReceived);
    connect(webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

MopidyClientPrivate::~MopidyClientPrivate()
{
    delete webSocket;
}

void MopidyClientPrivate::registerMopidyTypes()
{
    qRegisterMetaType<Mopidy::PlaybackState>("Mopidy::PlaybackState");
    qRegisterMetaType<Mopidy::RefType>("Mopidy::RefType");
    qRegisterMetaType<Mopidy::Album>("Mopidy::Album");
    qRegisterMetaType<Mopidy::Albums>("Mopidy::Albums");
    qRegisterMetaType<Mopidy::Artist>("Mopidy::Artist");
    qRegisterMetaType<Mopidy::Artists>("Mopidy::Artists");
    qRegisterMetaType<Mopidy::History>("Mopidy::History");
    qRegisterMetaType<Mopidy::Image>("Mopidy::Image");
    qRegisterMetaType<Mopidy::Images>("Mopidy::Images");
    qRegisterMetaType<Mopidy::Playlist>("Mopidy::Playlist");
    qRegisterMetaType<Mopidy::Playlists>("Mopidy::Playlists");
    qRegisterMetaType<Mopidy::Ref>("Mopidy::Ref");
    qRegisterMetaType<Mopidy::Refs>("Mopidy::Refs");
    qRegisterMetaType<Mopidy::SearchResult>("Mopidy::SearchResult");
    qRegisterMetaType<Mopidy::TlTrack>("Mopidy::TlTrack");
    qRegisterMetaType<Mopidy::TlTracks>("Mopidy::TlTracks");
    qRegisterMetaType<Mopidy::Track>("Mopidy::Track");
    qRegisterMetaType<Mopidy::Tracks>("Mopidy::Tracks");
}

void MopidyClientPrivate::sendRequest(std::function<void(QJsonValue)> processFx, const QString &method, const QJsonObject &params)
{
    Q_Q(MopidyClient);
    if(webSocket->state() != QAbstractSocket::ConnectedState)
    {
        emit q->connectionError(-1, "Client is not connected to Mopidy");
        return;
    }

    JsonRpcMessage message = JsonRpcMessage::build_request(method, ++m_lastRequestID, params);
    requestsPool.insert(m_lastRequestID, processFx);
    QByteArray data = message.toJson();
    webSocket->sendTextMessage(data);
}

void MopidyClientPrivate::sendNotification(const QString &method, const QJsonObject &params)
{
    JsonRpcMessage message = JsonRpcMessage::build_notification(method, params);
    QByteArray data = message.toJson();
    webSocket->sendTextMessage(data);
}

void MopidyClientPrivate::processEvent(const QJsonObject &eventObj)
{
    Q_Q(MopidyClient);

    QString evtName = eventObj.value("event").toString();

    if(evtName == "options_changed")
    {
        emit q->optionsChanged();
    }
    else if(evtName == "playback_state_changed")
    {
        QString os = eventObj.value("old_state").toString();
        QString ns = eventObj.value("new_state").toString();
        emit q->playbackStateChanged(
                    ModelTranslator::getState(os),
                    ModelTranslator::getState(ns));
    }
    else if(evtName == "playlist_changed")
    {
        Mopidy::Playlist pl;
        ModelTranslator::fromJson(eventObj.value("playlist").toObject(), pl);
        emit q->playlistChanged(pl);
    }
    else if(evtName == "playlists_loaded")
    {
        emit q->playlistsLoaded();
    }
    else if(evtName == "seeked")
    {
        int tp = eventObj.value("time_position").toDouble();
        emit q->seeked(tp);
    }
    else if(evtName == "track_playback_ended")
    {
        Mopidy::TlTrack tlt;
        ModelTranslator::fromJson(eventObj.value("tl_track").toObject(), tlt);
        int tp = eventObj.value("time_position").toDouble();
        emit q->trackPlaybackEnded(tlt, tp);
    }
    else if(evtName == "track_playback_paused")
    {
        Mopidy::TlTrack tlt;
        ModelTranslator::fromJson(eventObj.value("tl_track").toObject(), tlt);
        int tp = eventObj.value("time_position").toDouble();
        emit q->trackPlaybackPaused(tlt, tp);
    }
    else if(evtName == "track_playback_resumed")
    {
        Mopidy::TlTrack tlt;
        ModelTranslator::fromJson(eventObj.value("tl_track").toObject(), tlt);
        int tp = eventObj.value("time_position").toDouble();
        emit q->trackPlaybackResumed(tlt, tp);
    }
    else if(evtName == "track_playback_started")
    {
        Mopidy::TlTrack tlt;
        ModelTranslator::fromJson(eventObj.value("tl_track").toObject(), tlt);
        emit q->trackPlaybackStarted(tlt);
    }
    else if(evtName == "tracklist_changed")
    {
        emit q->tracklistChanged();
    }
    else if(evtName == "volume_changed")
    {
        emit q->volumeChanged();
    }
    else if(evtName == "mute_changed")
    {
        emit q->muteChanged(eventObj.value("mute").toBool());
    }
    else
    {
        qCritical() << __FUNCTION__ << QObject::tr("Unknown event:") << evtName;
    }
}

void MopidyClientPrivate::onTextMessageReceived(const QString &message)
{
    Q_Q(MopidyClient);

    // try to read json document
    QJsonParseError jpError;
    QJsonDocument jdoc = QJsonDocument::fromJson(message.toLatin1(), &jpError);
    if(jpError.error != QJsonParseError::NoError)
    {
        qCritical() << __FUNCTION__ << QObject::tr("Not a valid Json Document:") << jpError.error << jpError.errorString();
        return;
    }

    const QJsonObject &rootObject = jdoc.object();

    // event or answer to request ?
    if(rootObject.contains("event"))
    {
        processEvent(rootObject);
    }
    else
    {
        // get json-rpc message
        JsonRpcMessage jrm = JsonRpcMessage::fromJson(rootObject);
        if(!jrm.isValid())
        {
            qCritical() << __FUNCTION__ << QObject::tr("Invalid message");
            return;
        }
        if(jrm.type() == JsonRpcMessage::MessageType::Error)
        {
            QString errorMessage = jrm.errorMessage();
            const QJsonValue &errorData = jrm.errrorData();
            if(!errorData.isNull())
            {
                switch(errorData.type())
                {
                case QJsonValue::Bool:
                case QJsonValue::Double:
                    errorMessage += ": " + QString::number(errorData.toInt());
                    break;
                case QJsonValue::String:
                    errorMessage += ": " + errorData.toString();
                    break;
                case QJsonValue::Object:
                {
                    QJsonDocument jDocErr(errorData.toObject());
                    errorMessage += ": " + jDocErr.toJson(QJsonDocument::Compact);
                }
                    break;

                default:break;
                }
            }
            emit q->protocolError(static_cast<int>(jrm.errorCode()), errorMessage);
            return;
        }

        // Process response
        int rid = jrm.id();
        if(requestsPool.contains(rid))
                requestsPool.take(rid)(jrm.result());
    }
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

    d_ptr->registerMopidyTypes();
}

MopidyClient::~MopidyClient()
{
}

void MopidyClient::connectToServer(const QString &host, const quint16 &port, const QString &path)
{
    Q_D(MopidyClient);

    // create connection URL
    QUrl url = QUrl::fromUserInput(host);
    url.setScheme("ws");
    url.setPort(port);
    url.setPath(path);

    // Try to open websocket connection
    d->webSocket->open(url);
}

void MopidyClient::disconnectFromServer()
{
    Q_D(MopidyClient);

    if(d->webSocket->state() == QAbstractSocket::ConnectedState)
        d->webSocket->close();
}

QString MopidyClient::clientVersion() const
{
    return QString(GIT_VERSION);
}

QSharedPointer<CoreController> MopidyClient::coreController()
{
    Q_D(MopidyClient);
    return d->coreController;
}

QSharedPointer<HistoryController> MopidyClient::historyController()
{
    Q_D(MopidyClient);
    return d->historyController;
}

QSharedPointer<LibraryController> MopidyClient::libraryController()
{
    Q_D(MopidyClient);
    return d->libraryController;
}

QSharedPointer<MixerController> MopidyClient::mixerController()
{
    Q_D(MopidyClient);
    return d->mixerController;
}

QSharedPointer<PlaybackController> MopidyClient::playbackController()
{
    Q_D(MopidyClient);
    return d->playbackController;
}

QSharedPointer<PlaylistsController> MopidyClient::playlistsController()
{
    Q_D(MopidyClient);
    return d->playlistsController;
}

QSharedPointer<TracklistController> MopidyClient::tracklistController()
{
    Q_D(MopidyClient);
    return d->tracklistController;
}
