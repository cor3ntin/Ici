QT       = core

TARGET = ici

TEMPLATE = lib

OBJECTS_DIR = .obj
DESTDIR = ..


FLEX_FILES = $$PWD/ici.l
flex.name = flex
flex.input = FLEX_FILES
flex.output = ${QMAKE_FILE_BASE}-lex.inc
flex.commands = /usr/bin/flex -o${QMAKE_FILE_BASE}-lex.inc ${QMAKE_FILE_IN}
flex.CONFIG += no_link explicit_dependencies target_predeps
QMAKE_EXTRA_COMPILERS += flex

QLALR_FILES = $$PWD/ici.g
qlalr.name = qlalr
qlalr.input = QLALR_FILES
qlalr.output = ${QMAKE_FILE_BASE}grammar.cpp
qlalr.commands = qlalr ${QMAKE_FILE_IN}
qlalr.depends = ${FLEX_FILES}
qlalr.dependency_type = TYPE_C
qlalr.CONFIG += no_link explicit_dependencies target_predeps
QMAKE_EXTRA_COMPILERS += qlalr

HEADERS += iciparser.h \
    $$PWD/icigrammar_p.h \
    $$PWD/iciast.h \
    $$PWD/iciast_fwd.h \
    $$PWD/ici.h\
    $$PWD/ici_p.h\
    $$PWD/icifunctions.h

SOURCES += iciparser.cpp \
    icigrammar.cpp \
    $$PWD/ici.cpp \
    $$PWD/icifunctions.cpp
OTHER_FILES += $$PWD/ici.l $$PWD/ici.g
