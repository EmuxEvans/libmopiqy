#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H

#include <QObject>
#include <libmopiqy/libmopiqy_export.h>

class LIBMOPIQY_EXPORT CoreController : public QObject
{
    Q_OBJECT

public slots:
    virtual void describe() = 0;
    virtual void getUriSchemes() = 0;
    virtual void getVersion() = 0;

signals:
    void describeReceived(const QJsonObject &desc);
    void uriSchemesReceived(const QStringList &uris);
    void versionReceived(const QString &version);
};

#endif //CORECONTROLLER_H
