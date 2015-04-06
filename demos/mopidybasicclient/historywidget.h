#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include "libmopiqy/historycontroller.h"

namespace Ui {
    class HistoryWidget;
}

class HistoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryWidget(QWidget *parent = 0);
    ~HistoryWidget();

    void setHistoryController(QSharedPointer<HistoryController> historyController);

public slots:
    void onHistoryReceived(const QMap<unsigned long, Mopidy::Ref> &history);
    void onLengthReceived(const int &length);

private:
    Ui::HistoryWidget *m_ui;
    QSharedPointer<HistoryController> m_historyController;
};

#endif // HISTORYWIDGET_H
