TEMPLATE = lib
QT = core websockets

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
    corecontroller.cpp

PUBLIC_HEADERS += \
    mopidyclient.h \
    mopidymodels.h \
    mopiqy_export.h \
    eventlistener.h \
    playbackcontroller.h \
    playlistscontroller.h \
    tracklistcontroller.h \
    librarycontroller.h \
    controllerinterface.h \
    corecontroller.h

PRIVATE_HEADERS += \
    jsonwebsocket.h \
    jsonrpchandler.h \
    mopidyparser.h

HEADERS = $$PUBLIC_HEADERS $$PRIVATE_HEADERS

#
# Platform dependant config
#
LVERSION = $$system(git describe --tags --long)
unix {
    VERSION = $$LVERSION
    macx {
        CONFIG += staticlib
    }
}
win32 {
    VERSION = $$system(git describe --tags --abbrev=0)
}
DEFINES += LIBMOPIQY_VERSION=\\\"$${LVERSION}\\\"
DEFINES += LIBMOPIQY_SHARED

#
# Install
#
target.path = $${INSTALL_ROOT}/lib

pub_hdrs.files = $$PUBLIC_HEADERS
pub_hdrs.path  = $${INSTALL_ROOT}/include/libmopiqy

INSTALLS += target pub_hdrs
