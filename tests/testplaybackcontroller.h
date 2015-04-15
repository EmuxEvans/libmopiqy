#ifndef TESTPLAYBACKCONTROLLER_H
#define TESTPLAYBACKCONTROLLER_H

#include <QObject>
#include <QtTest/QtTest>
#include "libmopiqy/mopidyclient.h"

class TestPlaybackController : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void tstCurrentTlTrack();
    void tstCurrentTrack();
    void tstState();
    void tstStreamTitle();
    void tstTimePosition();
    void tstSeek();
    void cleanupTestCase();

private:
    MopidyClient client;
};

#endif // TESTPLAYBACKCONTROLLER_H
