QT = core testlib

SOURCES += \
    main.cpp \
    testmopidyclient.cpp

HEADERS += \
    testmopidyclient.h

win32{
    CONFIG(debug, debug|release) {
        LIBS += -L$${OUT_PWD}/../src/debug -lmopiqyd
    }
    CONFIG(release, debug|release) {
        LIBS += -L$${OUT_PWD}/../src/release -lmopiqy
    }
}
