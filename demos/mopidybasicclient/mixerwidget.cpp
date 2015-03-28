#include "mixerwidget.h"
#include "ui_mixerwidget.h"

MixerWidget::MixerWidget(QWidget *parent) :
    QWidget(parent), m_ui(new Ui::MixerWidget)
{
    m_ui->setupUi(this);
}

MixerWidget::~MixerWidget()
{
    delete m_ui;
}

void MixerWidget::setMixerController(QSharedPointer<MixerController> mixerController)
{
    m_mixerController = mixerController;
    if(m_mixerController)
    {
        connect(m_mixerController.data(), &MixerController::getMuteReceived, this, &MixerWidget::onGetMuteReceived);
        connect(m_mixerController.data(), &MixerController::setMuteReceived, this, &MixerWidget::onSetMuteReceived);
        connect(m_mixerController.data(), &MixerController::getVolumeReceived, this, &MixerWidget::onGetVolumeReceived);
        connect(m_mixerController.data(), &MixerController::setVolumeReceived, this, &MixerWidget::onSetVolumeReceived);
    }
}

void MixerWidget::on_btGetMute_clicked()
{
    if(m_mixerController)
        m_mixerController->getMute();
}

void MixerWidget::on_btSetMute_clicked()
{
    m_ui->cbSetMuteAck->setChecked(false);
    if(m_mixerController)
        m_mixerController->setMute(m_ui->cbSetMute->isChecked());
}

void MixerWidget::on_btGetVolume_clicked()
{
    if(m_mixerController)
        m_mixerController->getVolume();
}

void MixerWidget::on_btSetVolume_clicked()
{
    m_ui->cbSetVolumeAck->setChecked(false);
    if(m_mixerController)
        m_mixerController->setVolume(m_ui->sbSetVolume->value());
}

void MixerWidget::onGetMuteReceived(const bool &muted)
{
    m_ui->cbGetMute->setChecked(muted);
}

void MixerWidget::onSetMuteReceived(const bool &ack)
{
    m_ui->cbSetMuteAck->setChecked(ack);
}

void MixerWidget::onGetVolumeReceived(const int &volume)
{
    m_ui->sbGetVolume->setValue(volume);
}

void MixerWidget::onSetVolumeReceived(const bool &ack)
{
    m_ui->cbSetVolumeAck->setChecked(ack);
}
