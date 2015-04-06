TEMPLATE = lib
QT       = core websockets
TARGET   = $$qtLibraryTarget(mopiqy)
DEFINES += LIBMOPIQY_SHARED
CONFIG  += c++11

include(../version.pri)

#
# Test coverage
#
unix: CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
    LIBS += -lgcov
}

#
# Public headers
#
LIBMOPIQY_INCDIR  = ../include
LIBMOPIQY_HEADERS = \
    $${LIBMOPIQY_INCDIR}/libmopiqy/libmopiqy_export.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/mopidymodels.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/mopidyclient.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/corecontroller.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/historycontroller.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/librarycontroller.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/mixercontroller.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/playbackcontroller.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/playlistscontroller.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/tracklistcontroller.h

INCLUDEPATH += $${LIBMOPIQY_INCDIR}

#
# Sources
#
SOURCES = \
    mopidyclient.cpp \
    jsonrpcmessage.cpp \
    modeltranslator.cpp \
    basecontrollerimpl.cpp \
    corecontrollerimpl.cpp \
    historycontrollerimpl.cpp \
    librarycontrollerimpl.cpp \
    mixercontrollerimpl.cpp \
    playbackcontrollerimpl.cpp \
    playlistscontrollerimpl.cpp \
    tracklistcontrollerimpl.cpp

HEADERS = \
    $${LIBMOPIQY_HEADERS} \
    mopidyclient_p.h \
    jsonrpcmessage.h \
    modeltranslator.h \
    basecontrollerimpl.h \
    corecontrollerimpl.h \
    historycontrollerimpl.h \
    librarycontrollerimpl.h \
    mixercontrollerimpl.h \
    playbackcontrollerimpl.h \
    playlistscontrollerimpl.h \
    tracklistcontrollerimpl.h

#
# Install
#
target.path    = $${INSTALL_ROOT}/lib
pub_hdrs.files = $$LIBMOPIQY_HEADERS
pub_hdrs.path  = $${INSTALL_ROOT}/include/libmopiqy
INSTALLS += target pub_hdrs
