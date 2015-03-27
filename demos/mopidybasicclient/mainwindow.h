#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "libmopiqy/mopidyclient.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onClientConnected();
    void onClientDisconnected();
    void on_btConnect_clicked();
    void on_btDisconnect_clicked();

private:
    Ui::MainWindow *m_ui;
    MopidyClient *m_client;
};

#endif //MAINWINDOW_H
