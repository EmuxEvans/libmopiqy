#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H

#include "controllerinterface.h"
#include "mopiqy_export.h"

namespace Mopiqy {
class LIBMOPIQY_EXPORT CoreController : public ControllerInterface
{
    Q_OBJECT

public:
    CoreController(RemoteClient *remoteClient);
    ~CoreController();

public slots:
    /*
             * functions from Core API
             */
    void describe();
    void get_uri_schemes();
    void get_version();

signals:
    void onDescribe(const QJsonObject &desc);
    void onVersion(const QString &version);
    void onUriSchemes(const QStringList &uris);

protected:
    void processJsonResponse(const int &idt, const QJsonValue &jv);

private:
    enum CCEnum
    {
        CC_DESCRIBE,
        CC_URI_SCHEMES,
        CC_VERSION
    };
};
}

#endif //CORECONTROLLER_H
