#ifndef HISTORYCONTROLLERIMPL_H
#define HISTORYCONTROLLERIMPL_H

#include "libmopiqy/historycontroller.h"

class MopidyClientPrivate;

class HistoryControllerImpl : public HistoryController
{
    Q_OBJECT

public:
    HistoryControllerImpl(MopidyClientPrivate *parent);
    ~HistoryControllerImpl();

    // process responses
    void pr_getHistory(const QJsonValue &response);
    void pr_getLength(const QJsonValue &response);

public slots:
    void getHistory();
    void getLength();

private:
    MopidyClientPrivate *m_mcp;
};

#endif //HISTORYCONTROLLERIMPL_H
