#ifndef HISTORYCONTROLLERIMPL_H
#define HISTORYCONTROLLERIMPL_H

#include "libmopiqy/historycontroller.h"
#include "basecontrollerimpl.h"

class HistoryControllerImpl : public HistoryController, public BaseControllerImpl
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
};

#endif //HISTORYCONTROLLERIMPL_H
