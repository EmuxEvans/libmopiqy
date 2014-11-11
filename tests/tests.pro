QT = core testlib

SOURCES += \
    main.cpp \
    testmopidyclient.cpp

HEADERS += \
    testmopidyclient.h

include(../libmopiqy.pri)
LIBS += -L$${OUT_PWD}/../src
