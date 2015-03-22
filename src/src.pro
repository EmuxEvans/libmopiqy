TEMPLATE = lib
QT       = core websockets
TARGET   = $$qtLibraryTarget(mopiqy)
DEFINES += LIBMOPIQY_SHARED
CONFIG  += C++11

include(../version.pri)

#
# Sources
#
SOURCES = \
    mopidyclient.cpp \
    jsonrpcmessage.cpp \
    modeltranslator.cpp \
    corecontroller.cpp \
    librarycontroller.cpp

LIBMOPIQY_HEADERS = \
    libmopiqy_export.h \
    mopidymodels.h \
    mopidyclient.h \
    corecontroller.h \
    librarycontroller.h

HEADERS = \
    $$LIBMOPIQY_HEADERS \
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
