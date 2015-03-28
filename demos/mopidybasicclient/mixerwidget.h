#ifndef MIXERWIDGET_H
#define MIXERWIDGET_H

#include <QWidget>
#include "libmopiqy/mixercontroller.h"

namespace Ui {
class MixerWidget;
}

class MixerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MixerWidget(QWidget *parent = 0);
    ~MixerWidget();

    void setMixerController(QSharedPointer<MixerController> mixerController);

private slots:
    void on_btGetMute_clicked();
    void on_btSetMute_clicked();
    void on_btGetVolume_clicked();
    void on_btSetVolume_clicked();

    void onGetMuteReceived(const bool &muted);
    void onSetMuteReceived(const bool &ack);
    void onGetVolumeReceived(const int &volume);
    void onSetVolumeReceived(const bool &ack);

private:
    Ui::MixerWidget *m_ui;
    QSharedPointer<MixerController> m_mixerController;
};

#endif // MIXERWIDGET_H
