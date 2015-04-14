TEMPLATE = app
QT       = core testlib
CONFIG  += c++11

# libmopiqy
INCLUDEPATH += ../include/
LIBS += -L$$OUT_PWD/../src -l$$qtLibraryTarget(mopiqy)

# tests
SOURCES += \
    main.cpp \
    testmopidyclient.cpp \
    testcorecontroller.cpp \
    testhistorycontroller.cpp \
    testmixercontroller.cpp \
    testlibrarycontroller.cpp \
    testplaybackcontroller.cpp \
    testtracklistcontroller.cpp \
    testplaylistscontroller.cpp

HEADERS += \
    testmopidyclient.h \
    testcorecontroller.h \
    testhistorycontroller.h \
    testmixercontroller.h \
    testlibrarycontroller.h \
    testplaybackcontroller.h \
    testtracklistcontroller.h \
    testplaylistscontroller.h
