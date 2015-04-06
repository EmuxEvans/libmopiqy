#ifndef TESTCORECONTROLLER_H
#define TESTCORECONTROLLER_H

#include <QObject>
#include <QtTest/QtTest>
#include "libmopiqy/mopidyclient.h"

class TestCoreController : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void tstDescribe();
    void tstGetUriSchemes();
    void tstGetVersion();
    void cleanupTestCase();

private:
    MopidyClient client;
};

#endif // TESTCORECONTROLLER_H
