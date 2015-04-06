#ifndef TESTLIBRARYCONTROLLER_H
#define TESTLIBRARYCONTROLLER_H

#include <QObject>
#include <QtTest/QtTest>
#include "libmopiqy/mopidyclient.h"

class TestLibraryController : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void tstBrowse();
    void tstLookup();
    void tstRefresh();
    void tstSearch();
    void tstGetImages();
    void cleanupTestCase();

private:
    MopidyClient client;
};

#endif //TESTLIBRARYCONTROLLER_H
