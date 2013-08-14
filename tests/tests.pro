TEMPLATE = app
QT = core testlib
TARGET = tests
INCLUDEPATH += .

SOURCES += main.cpp

# Tests cases
HEADERS += \
    testjsonwebsocket.h \
    testjsonrpchandler.h \
    testmopidyparser.h

SOURCES += \
    testjsonwebsocket.cpp \
    testjsonrpchandler.cpp \
    testmopidyparser.cpp

# Lib
INCLUDEPATH += ../src ../include/libmopiqy
LIBS += -L../src -lmopiqy

# websocketpp
INCLUDEPATH += ../src/3rdparty/websocketpp
LIBS += -lboost_system -lboost_random -lboost_thread
