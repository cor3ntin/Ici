QT       = core

TARGET = ici

TEMPLATE = app

OBJECTS_DIR = .obj
DESTDIR = ..


SOURCES += main.cpp
INCLUDEPATH += "../src"
LIBS += -L$${PWD}/.. -lici
