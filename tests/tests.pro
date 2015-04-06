TEMPLATE = app
QT       = core testlib
CONFIG  += c++11

# libmopiqy
INCLUDEPATH += ../include/
LIBS += -L$$OUT_PWD/../src -l$$qtLibraryTarget(mopiqy)

# tests
SOURCES += \
    main.cpp \
    testmopidyclient.cpp \
    testcorecontroller.cpp

HEADERS += \
    testmopidyclient.h \
    testcorecontroller.h
