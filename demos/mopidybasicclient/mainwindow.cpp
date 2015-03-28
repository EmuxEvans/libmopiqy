#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "corewidget.h"
#include "mixerwidget.h"

#include "libmopiqy/corecontroller.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_client = new MopidyClient(this);
    connect(m_client, &MopidyClient::clientConnected, this, &MainWindow::onClientConnected);
    connect(m_client, &MopidyClient::clientDisconnected, this, &MainWindow::onClientDisconnected);
    connect(m_client, &MopidyClient::protocolError, this, &MainWindow::onClientError);
    connect(m_client, &MopidyClient::connectionError, this, &MainWindow::onClientError);

    //
    CoreWidget *coreWidget = new CoreWidget(this);
    coreWidget->setCoreController(m_client->coreController());
    m_ui->tabWidget->addTab(coreWidget, "Core");
    MixerWidget *mixerWidget = new MixerWidget(this);
    mixerWidget->setMixerController(m_client->mixerController());
    m_ui->tabWidget->addTab(mixerWidget, "Mixer");
}

MainWindow::~MainWindow()
{
    m_client->disconnectFromServer();
    delete m_ui;
}

void MainWindow::onClientConnected()
{
    onClientError(0, QString("Connected with libmopidy %1").arg(m_client->clientVersion()));
}

void MainWindow::onClientDisconnected()
{
    onClientError(0, "Disconnected");
}

void MainWindow::onClientError(int code, QString message)
{
    m_ui->lwError->addItem(QString("[%1] %2: %3")
                           .arg(QDateTime::currentDateTime().toString())
                           .arg(code)
                           .arg(message));
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
