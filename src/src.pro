TEMPLATE = lib
QT = core websockets

DESTDIR = $$OUT_PWD
TARGET = $$qtLibraryTarget(mopiqy)
DEFINES += LIBMOPIQY_SHARED

include(../version.pri)

SOURCES = \
    mopidyparser.cpp \
    controllerinterface.cpp \
    playbackcontroller.cpp \
    playlistscontroller.cpp \
    tracklistcontroller.cpp \
    librarycontroller.cpp \
    corecontroller.cpp \
    remoteclient.cpp \
    mopiqyhelper.cpp

PUBLIC_HEADERS += \
    mopiqy.h \
    remoteclient.h \
    mopidymodels.h \
    mopiqy_export.h \
    playbackcontroller.h \
    playlistscontroller.h \
    tracklistcontroller.h \
    librarycontroller.h \
    controllerinterface.h \
    corecontroller.h \
    mopiqyhelper.h

PRIVATE_HEADERS += \
    mopidyparser.h

HEADERS = $$PUBLIC_HEADERS $$PRIVATE_HEADERS

#
# Install
#
target.path = $${INSTALL_ROOT}/lib

pub_hdrs.files = $$PUBLIC_HEADERS
pub_hdrs.path  = $${INSTALL_ROOT}/include/libmopiqy

INSTALLS += target pub_hdrs
