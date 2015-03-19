#ifndef CORECONTROLLERIMPL_H
#define CORECONTROLLERIMPL_H

#include "corecontroller.h"

class MopidyClientPrivate;

class CoreControllerImpl : public CoreController
{
    Q_OBJECT

public:
    CoreControllerImpl(MopidyClientPrivate *parent = 0);
    ~CoreControllerImpl();

    // process responses
    void pr_describe(const QJsonValue &response);
    void pr_getUriSchemes(const QJsonValue &response);
    void pr_getVersion(const QJsonValue &response);

public slots:
    void describe();
    void getUriSchemes();
    void getVersion();

private:
    MopidyClientPrivate *m_mcp;
};

#endif //CORECONTROLLER_H
