#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H

#include <QtCore/QJsonValue>
#include <QtCore/QMap>
#include <QtCore/QObject>

namespace Mopiqy {

class RemoteClient;

/*
         * Abstract class for each Controller class
         * - process json response
         * - keep map with message sended waiting for response
         */
class ControllerInterface : public QObject
{
    Q_OBJECT

public:
    ControllerInterface(RemoteClient *remoteClient);

    void processResponse(const QString &id, const QJsonValue &jv);

protected:
    virtual void processJsonResponse(const int &idt, const QJsonValue &jo) = 0;
    void sendMessage(const QJsonObject &msg, const int &requestType, bool notification = false);

private:
    RemoteClient *m_client;

    // map to store id / request type per controller
    QMap<QString, int> m_idQuery;
};
}

#endif //CONTROLLERINTERFACE_H
