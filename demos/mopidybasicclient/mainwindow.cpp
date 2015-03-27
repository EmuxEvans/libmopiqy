#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "corewidget.h"

#include "libmopiqy/corecontroller.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_client = new MopidyClient(this);
    connect(m_client, &MopidyClient::clientConnected, this, &MainWindow::onClientConnected);
    connect(m_client, &MopidyClient::clientDisconnected, this, &MainWindow::onClientDisconnected);

    //
    CoreWidget *coreWidget = new CoreWidget(this);
    coreWidget->setCoreController(m_client->coreController());
    m_ui->tabWidget->addTab(coreWidget, "Core");
}

MainWindow::~MainWindow()
{
    m_client->disconnectFromServer();
    delete m_ui;
}

void MainWindow::onClientConnected()
{
    qDebug() << "connected" << m_client->clientVersion();
}

void MainWindow::onClientDisconnected()
{
    qDebug() << "Disconnected";
}

void MainWindow::on_btConnect_clicked()
{
    m_client->connectToServer(
                m_ui->leMopidyHost->text(),
                m_ui->sbMopidyPort->value(),
                m_ui->leMopidyPath->text());
}

void MainWindow::on_btDisconnect_clicked()
{
    m_client->disconnectFromServer();
}
