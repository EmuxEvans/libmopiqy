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
    void tstAdd();
    void tstEotTrack();
    void tstFilter();
    void tstConsume();
    void tstLength();
    void tstRandom();
    void tstRepeat();
    void tstSingle();
    void tstTlTracks();
    void tstTracks();
    void tstVersion();
    void tstIndex();
    void tstNextTrack();
    void tstPreviousTrack();
    void tstRemove();
    void tstSlice();
    void cleanupTestCase();

private:
    MopidyClient client;
};

#endif // TESTTRACKLISTCONTROLLER_H
