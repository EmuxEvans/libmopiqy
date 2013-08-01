TEMPLATE = lib
CONFIG += shared
TARGET = mopiqy_core

QT = core

SOURCES = \
    src/mopidyclient.cpp \
    src/jsonwebsocket.cpp \
    src/jsonrpchandler.cpp \
    src/mopidyparser.cpp \
    src/corelistener.cpp \
    src/controllerinterface.cpp \
    src/playbackcontroller.cpp \
    src/playlistscontroller.cpp \
    src/tracklistcontroller.cpp \
    src/librarycontroller.cpp

PUBLIC_HEADERS += \
    include/mopiqy_core/mopidyclient.h \
    include/mopiqy_core/mopidymodels.h \
    include/mopiqy_core/mopiqy_export.h \
    include/mopiqy_core/corelistener.h \
    include/mopiqy_core/playbackcontroller.h \
    include/mopiqy_core/playlistscontroller.h \
    include/mopiqy_core/tracklistcontroller.h \
    include/mopiqy_core/librarycontroller.h \
    include/mopiqy_core/controllerinterface.h

HEADERS += \
    src/jsonwebsocket.h \
    src/jsonrpchandler.h \
    src/mopidyparser.h \
    $${PUBLIC_HEADERS}

INCLUDEPATH += include/mopiqy_core

#
# websocketpp
#
INCLUDEPATH += ./websocketpp

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
    CONFIG(debug, debug|release): TARGET = $$join(TARGET,,,d)

    DESTDIR = ../bin

    #
    # Where is boost ??
    # TODO: Use CMake
    #
    BOOST_ROOT_DIR = C:/local/boost_1_54_0
    BOOST_INC_DIR  = $${BOOST_ROOT_DIR}
    BOOST_LIB_DIR  = $${BOOST_ROOT_DIR}/lib32-msvc-10.0

    INCLUDEPATH += $${BOOST_INC_DIR}
    LIBS += -L$${BOOST_LIB_DIR}
}
DEFINES += MOPIQY_CORE_VERSION=\\\"$${VERSION}\\\"
