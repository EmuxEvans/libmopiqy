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
    include/mopidyclient.h \
    include/mopidymodels.h \
    include/mopiqy_export.h \
    include/corelistener.h \
    include/playbackcontroller.h \
    include/playlistscontroller.h \
    include/tracklistcontroller.h \
    include/librarycontroller.h \
    include/controllerinterface.h

HEADERS += \
    src/jsonwebsocket.h \
    src/jsonrpchandler.h \
    src/mopidyparser.h \
    $${PUBLIC_HEADERS}


#
# Platform dependant config
#
unix {
    LIBS += -lPocoFoundation -lPocoNet
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
}
