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
