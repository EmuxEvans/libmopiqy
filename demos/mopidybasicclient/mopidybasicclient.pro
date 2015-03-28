TEMPLATE = app
QT       = core gui widgets
CONFIG  += c++11

#
INCLUDEPATH += $$PWD/../../include/
LIBS += -L$$OUT_PWD/../../src -l$$qtLibraryTarget(mopiqy)


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    corewidget.cpp

HEADERS += \
    mainwindow.h \
    corewidget.h

FORMS += \
    mainwindow.ui \
    corewidget.ui
