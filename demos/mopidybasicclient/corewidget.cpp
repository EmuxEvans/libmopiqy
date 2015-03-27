#include "corewidget.h"
#include "ui_corewidget.h"


CoreWidget::CoreWidget(QWidget *parent)
    : QWidget(parent), m_ui(new Ui::CoreWidget), m_controller(0)
{
    m_ui->setupUi(this);
}

CoreWidget::~CoreWidget()
{
    delete m_ui;
}

void CoreWidget::setCoreController(QSharedPointer<CoreController> coreController)
{
    m_controller = coreController;
}

void CoreWidget::on_btGetVersion_clicked()
{
    if(m_controller)
        m_controller->getVersion();
}

void CoreWidget::onGetVersionReceived(const QString &version)
{
    m_ui->leGetVersion->setText(version);
}
