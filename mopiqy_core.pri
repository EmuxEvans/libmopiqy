INCLUDEPATH += $$PWD/include

# core itself
unix {
    LIBS += -L../mopiqy_core -lmopiqy_core
}
win32 {
    LIBS += -L../mopiqy_core/bin
    CONFIG(debug, debug|release): LIBS += -lmopiqy_cored
    CONFIG(release, debug|release): LIBS += -lmopiqy_core
    DESTDIR = ../bin
}
