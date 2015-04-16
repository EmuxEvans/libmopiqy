TEMPLATE = app
QT       = core gui widgets
CONFIG  += c++11
DESTDIR  = $${OUT_PWD}/../../bin
#
INCLUDEPATH += $$PWD/../../include/
LIBS += -L$$OUT_PWD/../../bin -l$$qtLibraryTarget(mopiqy)


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    corewidget.cpp \
    mixerwidget.cpp \
    historywidget.cpp

HEADERS += \
    mainwindow.h \
    corewidget.h \
    mixerwidget.h \
    historywidget.h

FORMS += \
    mainwindow.ui \
    corewidget.ui \
    mixerwidget.ui \
    historywidget.ui
