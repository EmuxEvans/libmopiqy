#ifndef HISTORYCONTROLLER_H
#define HISTORYCONTROLLER_H

#include <QObject>
#include <libmopiqy/mopidymodels.h>

class LIBMOPIQY_EXPORT HistoryController : public QObject
{
    Q_OBJECT

public slots:
    virtual void getHistory() = 0;
    virtual void getLength() = 0;

signals:
    void historyReceived(const QMap<unsigned long, Mopidy::Ref> &);
    void lengthReceived(const int &);
};

#endif //HISTORYCONTROLLER_H
