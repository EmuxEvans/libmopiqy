#ifndef MOPIDY_CLIENT_P_H
#define MOPIDY_CLIENT_P_H

#include <QObject>
#include <QJsonObject>
#include <QWebSocket>
#include <functional>

#include "corecontrollerimpl.h"
#include "historycontrollerimpl.h"
#include "librarycontrollerimpl.h"
#include "mixercontrollerimpl.h"
#include "playbackcontrollerimpl.h"
#include "playlistscontrollerimpl.h"
#include "tracklistcontrollerimpl.h"

class MopidyClient;
class MopidyClientPrivate : public QObject
{
    Q_OBJECT

public:
    MopidyClientPrivate(MopidyClient * parent);
    ~MopidyClientPrivate();

    void registerMopidyTypes();

    void sendRequest(std::function<void(QJsonValue)> processFx, const QString &method, const QJsonObject &params = QJsonObject());
    void sendNotification(const QString &method, const QJsonObject &params = QJsonObject());
    void processEvent(const QJsonObject &eventObj);

    QWebSocket *webSocket;

    QSharedPointer<CoreController> coreController;
    QSharedPointer<HistoryController> historyController;
    QSharedPointer<LibraryController> libraryController;
    QSharedPointer<MixerController> mixerController;
    QSharedPointer<PlaybackController> playbackController;
    QSharedPointer<PlaylistsController> playlistsController;
    QSharedPointer<TracklistController> tracklistController;

    //
    int m_lastRequestID;

    // pool of requests binded to process functions
    QHash<int, std::function<void(QJsonValue)>> requestsPool;

public slots:
    void onTextMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError socketError);

private:
    MopidyClient * const q_ptr;
    Q_DECLARE_PUBLIC(MopidyClient)
};

#endif //MOPIDY_CLIENT_P_H
