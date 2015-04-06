#ifndef TESTMIXERCONTROLLER_H
#define TESTMIXERCONTROLLER_H

#include <QObject>
#include <QtTest/QtTest>
#include "libmopiqy/mopidyclient.h"

class TestMixerController : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void tstGetMute();
    void tstSetMute();
    void tstGetVolume();
    void tstSetVolume();
    void cleanupTestCase();

private:
    MopidyClient client;
};

#endif // TESTMIXERCONTROLLER_H
