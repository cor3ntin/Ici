QT       = core

TARGET = ici

TEMPLATE = lib

OBJECTS_DIR = .obj
DESTDIR = ..


FLEX_FILES = ici.l
flex.name = flex
flex.input = FLEX_FILES
flex.output = ${QMAKE_FILE_BASE}-lex.inc
flex.commands = /usr/bin/flex -o${QMAKE_FILE_BASE}-lex.inc ${QMAKE_FILE_IN}
flex.CONFIG += no_link explicit_dependencies target_predeps
QMAKE_EXTRA_COMPILERS += flex

QLALR_FILES = ici.g
qlalr.name = qlalr
qlalr.input = QLALR_FILES
qlalr.output = ${QMAKE_FILE_BASE}grammar.cpp
qlalr.commands = /home/cor3ntin/dev/qlalr/src/qlalr ${QMAKE_FILE_IN}
qlalr.depends = ${QMAKE_FILE_BASE}.l
qlalr.dependency_type = TYPE_C
qlalr.CONFIG += no_link explicit_dependencies target_predeps
QMAKE_EXTRA_COMPILERS += qlalr


HEADERS += iciparser.h \
    icigrammar_p.h \
    iciast.h \
    iciast_fwd.h \
    ici.h\
    ici_p.h\
    icifunctions.h

SOURCES += iciparser.cpp \
    icigrammar.cpp \
    ici.cpp \
    icifunctions.cpp
OTHER_FILES += ici.l ici.g