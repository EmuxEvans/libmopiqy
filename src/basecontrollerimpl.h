#ifndef BASECONTROLLERIMPL_H
#define BASECONTROLLERIMPL_H

#include <functional>

#include <QDebug>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class MopidyClientPrivate;

class BaseControllerImpl
{
public:
    BaseControllerImpl(MopidyClientPrivate *parent);

    void sendRequest(std::function<void(QJsonValue)> processFx, const QString &method, const QJsonObject &params = QJsonObject());
    void sendNotification(const QString &method, const QJsonObject &params = QJsonObject());

protected:
    MopidyClientPrivate *m_mcp;
};

#endif //BASECONTROLLERIMPL_H
