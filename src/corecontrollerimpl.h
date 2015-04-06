#ifndef CORECONTROLLERIMPL_H
#define CORECONTROLLERIMPL_H

#include "libmopiqy/corecontroller.h"
#include "basecontrollerimpl.h"

class CoreControllerImpl : public CoreController, public BaseControllerImpl
{
    Q_OBJECT

public:
    CoreControllerImpl(MopidyClientPrivate *parent);
    ~CoreControllerImpl();

    // process responses
    void pr_describe(const QJsonValue &response);
    void pr_getUriSchemes(const QJsonValue &response);
    void pr_getVersion(const QJsonValue &response);

public slots:
    void describe();
    void getUriSchemes();
    void getVersion();
};

#endif //CORECONTROLLERIMPL_H
