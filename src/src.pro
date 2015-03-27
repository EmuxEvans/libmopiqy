TEMPLATE = lib
QT       = core websockets
TARGET   = $$qtLibraryTarget(mopiqy)
DEFINES += LIBMOPIQY_SHARED
CONFIG  += C++11

include(../version.pri)

#
# Public headers
#
LIBMOPIQY_INCDIR  = ../include
LIBMOPIQY_HEADERS = \
    $${LIBMOPIQY_INCDIR}/libmopiqy/libmopiqy_export.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/mopidymodels.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/mopidyclient.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/corecontroller.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/librarycontroller.h \
    $${LIBMOPIQY_INCDIR}/libmopiqy/playlistcontroller.h

INCLUDEPATH += $${LIBMOPIQY_INCDIR}

#
# Sources
#
SOURCES = \
    mopidyclient.cpp \
    jsonrpcmessage.cpp \
    modeltranslator.cpp \
    corecontrollerimpl.cpp \
    librarycontrollerimpl.cpp

HEADERS = \
    $${LIBMOPIQY_HEADERS} \
    mopidyclient_p.h \
    jsonrpcmessage.h \
    modeltranslator.h \
    corecontrollerimpl.h \
    librarycontrollerimpl.h

#
# Install
#
target.path    = $${INSTALL_ROOT}/lib
pub_hdrs.files = $$LIBMOPIQY_HEADERS
pub_hdrs.path  = $${INSTALL_ROOT}/include/libmopiqy
INSTALLS += target pub_hdrs
