#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H

#include <QObject>
#include "libmopiqy_export.h"

class LIBMOPIQY_EXPORT CoreController : public QObject
{
    Q_OBJECT

public:
    ~CoreController();

public slots:
    virtual void describe();
    virtual void getUriSchemes();
    virtual void getVersion();

signals:
    void describeReceived(const QJsonObject &desc);
    void uriSchemesReceived(const QStringList &uris);
    void versionReceived(const QString &version);

protected:
    CoreController(QObject *parent = 0);
};

#endif //CORECONTROLLER_H
