#include "historywidget.h"
#include "ui_historywidget.h"

HistoryWidget::HistoryWidget(QWidget *parent)
    : QWidget(parent), m_ui(new Ui::HistoryWidget)
{
    m_ui->setupUi(this);
}

HistoryWidget::~HistoryWidget()
{
    delete m_ui;
}

void HistoryWidget::setHistoryController(QSharedPointer<HistoryController> historyController)
{
    m_historyController = historyController;

    if(m_historyController)
    {
        connect(m_ui->btGetHistory, &QPushButton::clicked, m_historyController.data(), &HistoryController::getHistory);
        connect(m_ui->btGetLength, &QPushButton::clicked, m_historyController.data(), &HistoryController::getLength);
    }
}

void HistoryWidget::onHistoryReceived(const QMap<unsigned long, Mopidy::Ref> &history)
{
    QString historyStr;
    for(auto it = history.cbegin(); it != history.cend(); ++it)
        historyStr += QString("%1 - %2\n").arg(it.key()).arg(it.value().name);
    m_ui->pteHistory->setPlainText(historyStr);
}

void HistoryWidget::onLengthReceived(const int &length)
{
    m_ui->sbLength->setValue(length);
}
