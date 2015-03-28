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
    if(m_controller)
    {
        connect(m_controller.data(), &CoreController::versionReceived, this, &CoreWidget::onGetVersionReceived);
        connect(m_controller.data(), &CoreController::uriSchemesReceived, this, &CoreWidget::onGetUriSchemesReceived);
        connect(m_controller.data(), &CoreController::describeReceived, this, &CoreWidget::onDescribeReceived);
    }
}

void CoreWidget::on_btGetVersion_clicked()
{
    if(m_controller)
        m_controller->getVersion();
}

void CoreWidget::on_btGetUriSchemes_clicked()
{
    if(m_controller)
        m_controller->getUriSchemes();
}

void CoreWidget::on_btDescribe_clicked()
{
    if(m_controller)
        m_controller->describe();
}

void CoreWidget::onGetVersionReceived(const QString &version)
{
    m_ui->leGetVersion->setText(version);
}

void CoreWidget::onGetUriSchemesReceived(const QStringList &schemes)
{
    m_ui->leGetUriSchemes->setText(schemes.join(", "));
}

void CoreWidget::onDescribeReceived(const QString &desc)
{
    m_ui->pteDescribe->setPlainText(desc);
}
