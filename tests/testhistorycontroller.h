#ifndef TESTHISTORYCONTROLLER_H
#define TESTHISTORYCONTROLLER_H

#include <QObject>
#include <QtTest/QtTest>
#include "libmopiqy/mopidyclient.h"

class TestHistoryController : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void tstGetHistory();
    void tstGetLength();
    void cleanupTestCase();

private:
    MopidyClient client;
};

#endif // TESTHISTORYCONTROLLER_H
