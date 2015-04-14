#ifndef TESTTRACKLISTCONTROLLER_H
#define TESTTRACKLISTCONTROLLER_H

#include <QObject>
#include <QtTest/QtTest>
#include "libmopiqy/mopidyclient.h"

class TestTracklistController : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

private:
    MopidyClient client;
};

#endif // TESTTRACKLISTCONTROLLER_H
