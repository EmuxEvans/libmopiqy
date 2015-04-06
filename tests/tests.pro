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
    testcorecontroller.cpp \
    testhistorycontroller.cpp \
    testmixercontroller.cpp

HEADERS += \
    testmopidyclient.h \
    testcorecontroller.h \
    testhistorycontroller.h \
    testmixercontroller.h
