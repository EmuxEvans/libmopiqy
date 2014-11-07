#ifndef TESTMOPIDYCLIENT_H
#define TESTMOPIDYCLIENT_H

#include <QObject>
#include <QtTest/QtTest>

class TestMopidyClient : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void tstConnectionOk();
    void tstDeconnection();
    void tstConnectionFail();
    void cleanupTestCase();

private:
    QString m_host;
    qint16 m_port;
    QString m_path;
};

#endif // TESTMOPIDYCLIENT_H
