TEMPLATE = app
QT = core network testlib
TARGET = tests

SOURCES += main.cpp

# Tests cases
HEADERS += \
    testjsonwebsocket.h \
    testjsonrpchandler.h \
    testqwebsocketclient.h \
    testmopidyparser.h

SOURCES += \
    testjsonwebsocket.cpp \
    testjsonrpchandler.cpp \
    testqwebsocketclient.cpp \
    testmopidyparser.cpp

# Lib
INCLUDEPATH += ../src
LIBS += -L../src

CONFIG(debug, debug|release): LIBS += -lmopiqyd
CONFIG(release, debug|release): LIBS += -lmopiqy

