TEMPLATE = lib
QT = core
CONFIG += exceptions

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
    librarycontroller.cpp

LIBMOPIQY_INC_ROOT = $$PWD/../include/libmopiqy
PUBLIC_HEADERS += \
    $${LIBMOPIQY_INC_ROOT}/mopidyclient.h \
    $${LIBMOPIQY_INC_ROOT}/mopidymodels.h \
    $${LIBMOPIQY_INC_ROOT}/mopiqy_export.h \
    $${LIBMOPIQY_INC_ROOT}/corelistener.h \
    $${LIBMOPIQY_INC_ROOT}/playbackcontroller.h \
    $${LIBMOPIQY_INC_ROOT}/playlistscontroller.h \
    $${LIBMOPIQY_INC_ROOT}/tracklistcontroller.h \
    $${LIBMOPIQY_INC_ROOT}/librarycontroller.h \
    $${LIBMOPIQY_INC_ROOT}/controllerinterface.h

PRIVATE_HEADERS += \
    jsonwebsocket.h \
    jsonrpchandler.h \
    mopidyparser.h

HEADERS = $$PUBLIC_HEADERS $$PRIVATE_HEADERS

#
# websocketpp
#
INCLUDEPATH += $$PWD/3rdparty/websocketpp $${LIBMOPIQY_INC_ROOT}

#
# Platform dependant config
#
unix {
    VERSION = $$system(git describe --tags)
    LIBS += -lboost_system -lboost_random -lboost_thread
}

win32 {
    VERSION = 1.0
    DEFINES += MOPIQY_CORE_SHARED
    include(find_boost.pri)
}
DEFINES += MOPIQY_CORE_VERSION=\\\"$${VERSION}\\\"

#
# Install
#
target.path = $${INSTALL_ROOT}/lib

pub_hdrs.files = $$PUBLIC_HEADERS
pub_hdrs.path  = $${INSTALL_ROOT}/include/libmopiqy

INSTALLS += target pub_hdrs
