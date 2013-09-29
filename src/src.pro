TEMPLATE = lib
QT = core

TARGET = mopiqy
CONFIG(debug, debug|release): TARGET = $$join(TARGET,,,d)

SOURCES = \
    mopidyclient.cpp \
    jsonwebsocket.cpp \
    jsonrpchandler.cpp \
    mopidyparser.cpp \
    eventlistener.cpp \
    controllerinterface.cpp \
    playbackcontroller.cpp \
    playlistscontroller.cpp \
    tracklistcontroller.cpp \
    librarycontroller.cpp \
    qwebsocketclient.cpp \
    qwebsocketclient_p.cpp

PUBLIC_HEADERS += \
    mopidyclient.h \
    mopidymodels.h \
    mopiqy_export.h \
    eventlistener.h \
    playbackcontroller.h \
    playlistscontroller.h \
    tracklistcontroller.h \
    librarycontroller.h \
    controllerinterface.h

PRIVATE_HEADERS += \
    jsonwebsocket.h \
    jsonrpchandler.h \
    mopidyparser.h \
    qwebsocketclient.h \
    qwebsocketclient_p.h

HEADERS = $$PUBLIC_HEADERS $$PRIVATE_HEADERS

#
# WebSocket
#
INCLUDEPATH += 3rdparty/websocketpp

#
# Platform dependant config
#
unix {
    VERSION = $$system(git describe --tags)
    LIBS += -lboost_thread -lboost_system -lboost_random
}

win32 {
    VERSION = 1.0
    DEFINES += MOPIQY_CORE_SHARED
}

DEFINES += LIBMOPIQY_VERSION=\\\"$${VERSION}\\\"

#
# Install
#
target.path = $${INSTALL_ROOT}/lib

pub_hdrs.files = $$PUBLIC_HEADERS
pub_hdrs.path  = $${INSTALL_ROOT}/include/libmopiqy

INSTALLS += target pub_hdrs
