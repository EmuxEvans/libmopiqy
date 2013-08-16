TEMPLATE = lib
QT = core network

TARGET = mopiqy
CONFIG(debug, debug|release): TARGET = $$join(TARGET,,,d)

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
    librarycontroller.cpp \
    qwebsocketclient.cpp \
    websocketutility.cpp \

PUBLIC_HEADERS += \
    mopidyclient.h \
    mopidymodels.h \
    mopiqy_export.h \
    corelistener.h \
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
    websocketutility.h \

HEADERS = $$PUBLIC_HEADERS $$PRIVATE_HEADERS

#
# Platform dependant config
#
unix {
    VERSION = $$system(git describe --tags)
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
