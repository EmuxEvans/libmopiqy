#ifndef MOPIDY_CLIENT_P_H
#define MOPIDY_CLIENT_P_H

#include <QObject>
#include <QJsonObject>
#include <QWebSocket>
#include <functional>

#include "corecontrollerimpl.h"
#include "librarycontrollerimpl.h"

class MopidyClient;
class MopidyClientPrivate : public QObject
{
    Q_OBJECT

public:
    MopidyClientPrivate(MopidyClient * parent);
    ~MopidyClientPrivate();

    void sendRequest(std::function<void(QJsonValue)> processFx, const QString &method, const QJsonObject &params = QJsonObject());
    void sendNotification(const QString &method, const QJsonObject &params = QJsonObject());
    void processEvent(const QJsonObject &eventObj);

    QWebSocket *webSocket;
    QSharedPointer<CoreControllerImpl> coreController;
    QSharedPointer<LibraryControllerImpl> libraryController;

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
