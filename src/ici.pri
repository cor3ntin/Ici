HEADERS += \
    $$PWD/iciparser.h \
    $$PWD/icigrammar_p.h \
    $$PWD/iciast.h \
    $$PWD/iciast_fwd.h \
    $$PWD/ici.h\
    $$PWD/ici_p.h\
    $$PWD/icifunctions.h

SOURCES += \
    $$PWD/iciparser.cpp \
    $$PWD/icigrammar.cpp \
    $$PWD/ici.cpp \
    $$PWD/icifunctions.cpp

OTHER_FILES += $$PWD/ici.l $$PWD/ici.g
INCLUDEPATH += $$PWD $$PWD/../../includes
