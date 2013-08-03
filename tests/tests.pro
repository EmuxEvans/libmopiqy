TEMPLATE = app
QT = core testlib
TARGET = tests
INCLUDEPATH += .

SOURCES += main.cpp

# Tests cases
HEADERS += \
    testmopidyparser.h \
    testjsonrpchandler.h

SOURCES += \
    testmopidyparser.cpp \
    testjsonrpchandler.cpp

# Lib
INCLUDEPATH += ../src ../include/libmopiqy
LIBS += -L../src -lmopiqy

# websocketpp
INCLUDEPATH += ../src/3rdparty/websocketpp
LIBS += -lboost_system -lboost_random -lboost_thread
