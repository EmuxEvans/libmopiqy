#
# Common build config
#
TEMPLATE = lib
CONFIG += shared
TARGET = mopiqy_core

QT = core

SOURCES = \
    mopidyclient.cpp \
    jsonwebsocket.cpp \
    jsonrpchandler.cpp \
    mopidyparser.cpp \
    corelistener.cpp \
    controllerinterface.cpp \
    playbackcontroller.cpp \
    playlistscontroller.cpp \
    tracklistcontroller.cpp \
    librarycontroller.cpp

HEADERS += \
    mopidyclient.h \
    jsonwebsocket.h \
    jsonrpchandler.h \
    mopidymodels.h \
    mopidyparser.h \
    mopiqy_export.h \
    corelistener.h \
    controllerinterface.h \
    playbackcontroller.h \
    playlistscontroller.h \
    tracklistcontroller.h \
    librarycontroller.h

#
# Platform dependant config
#
unix {
    LIBS += -lPocoNet -lPocoFoundation
    VERSION = $$system(git describe --tags)
    DEFINES += MOPIQY_CORE_VERSION=\\\"$${VERSION}\\\"
}

win32 {
    DEFINES += MOPIQY_CORE_SHARED

    CONFIG(debug, debug|release) {
        LIBS += -lPocoNetd -lPocoFoundationd
        TARGET = $$join(TARGET,,,d)
    }
    CONFIG(release, debug|release): LIBS += -lPocoNet -lPocoFoundation

    DESTDIR = ../bin
}
