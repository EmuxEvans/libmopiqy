#ifndef TESTPLAYLISTSCONTROLLER_H
#define TESTPLAYLISTSCONTROLLER_H

#include <QObject>
#include <QtTest/QtTest>
#include "libmopiqy/mopidyclient.h"

class TestPlaylistsController : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void tstAsListResponse();
    void tstCreateResponse();
    void tstGetItemsResponse();
    void tstLookupResponse();
    void tstSaveResponse();
    void cleanupTestCase();

private:
    MopidyClient client;
};

#endif // TESTPLAYLISTSCONTROLLER_H
