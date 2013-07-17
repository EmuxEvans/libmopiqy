INCLUDEPATH += $$PWD/include

# core itself
unix {
    LIBS += -L../mopiqy_core -lmopiqy_core
}
win32 {
    LIBS += -L../bin
    CONFIG(debug, debug|release): LIBS += -lmopiqy_core1d
    CONFIG(release, debug|release): LIBS += -lmopiqy_core1
    DESTDIR = ../bin
}
