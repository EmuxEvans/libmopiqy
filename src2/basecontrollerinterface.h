#ifndef BASECONTROLLERINTERFACE_H
#define BASECONTROLLERINTERFACE_H

#include <QtCore/QJsonValue>
#include <QtCore/QMap>
#include <QtCore/QObject>

namespace Mopiqy {

class MopidyClient;

/*
 * Abstract class for each Controller class
 * - process json response
 * - keep map with message sended waiting for response
 */
class BaseControllerInterface : public QObject
{
    Q_OBJECT

public:
    BaseControllerInterface(QSharedPointer<MopidyClient> mopidyClient);

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

#endif //BASECONTROLLERINTERFACE_H
