LIBICI_DIR = `pwd`/..
LIBS = `pkg-config pyside --libs` -L$(LIBICI_DIR) -lici

MKSPECS_PATH = `qmake -query QMAKE_MKSPECS`

CXXFLAGS = -I$(MKSPECS_PATH)/linux-g++ -I. \
   -I$(LIBICI_DIR)/src \
   -I`pwd`/ici \
   -I`pkg-config --variable=includedir pyside`/QtCore/ \
   -I`pkg-config --variable=includedir QtCore` \
   -I`pkg-config --variable=includedir QtCore`/.. \
   -I`pkg-config --variable=includedir QtGui` \
   `pkg-config --cflags python-2.7` \
   `pkg-config pyside --cflags`

QT4TYPESYSTEM_DIR = `pkg-config pyside --variable=typesystemdir`
QT4HEADER_DIRS = `pkg-config --variable=includedir QtCore`:`pkg-config --variable=includedir QtCore`/..
PYSIDE_PYTHONPATH = `pkg-config --variable=pythonpath PySide`
PYTHON_INTERPRETER = `pkg-config --variable=python_interpreter shiboken`
SHIBOKEN = `pkg-config shiboken --variable=generator_location`

all: generate compile link

generate:
	$(SHIBOKEN) --generatorSet=shiboken \
	global.h \
	--include-paths=$(LIBICI_DIR)/src:$(QT4HEADER_DIRS):/usr/include \
	--typesystem-paths=.:$(QT4TYPESYSTEM_DIR) \
	--output-directory=. \
	typesystem_ici.xml

compile:
	g++ ici/ici_module_wrapper.cpp ici/icisettings_wrapper.cpp ici/icisettingscontext_wrapper.cpp -Wall -fPIC $(CXXFLAGS) -c

link:
	g++ icisettings_wrapper.o ici_module_wrapper.o icisettingscontext_wrapper.o $(LIBS) -fPIC -shared  -Wl,-soname,ici.so -o ici.so

test:
	LD_LIBRARY_PATH=$(LIBICI_DIR):$(LD_LIBRARY_PATH) PYTHONPATH=$(PYSIDE_PYTHONPATH):$(PYTHONPATH) $(PYTHON_INTERPRETER) test.py

clean:
	rm -rf *.o *.so *.?pp *.log *.log ici/*
