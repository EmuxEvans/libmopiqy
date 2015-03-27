#ifndef COREWIDGET_H
#define COREWIDGET_H

#include <QWidget>
#include "libmopiqy/corecontroller.h"

namespace Ui {
    class CoreWidget;
}

class CoreWidget : public QWidget
{
    Q_OBJECT

public:
    CoreWidget(QWidget *parent = 0);
    ~CoreWidget();

    void setCoreController(QSharedPointer<CoreController> coreController);

private slots:
    void on_btGetVersion_clicked();
    void onGetVersionReceived(const QString &version);

private:
    Ui::CoreWidget *m_ui;
    QSharedPointer<CoreController> m_controller;
};

#endif //COREWIDGET_H
