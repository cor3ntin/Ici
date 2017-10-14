DIR := $(dir $(firstword $(MAKEFILE_LIST)))
TARGET  = ici.so
OFILES  = sipicicmodule.o sipiciICISettings.o sipiciICISettingsContext.o
CPPFILES  = sipicicmodule.cpp sipiciICISettings.cpp sipiciICISettingsContext.cpp
HFILES    = sipAPIici.h
SIPFILE = $(DIR)/ici.sip
QT_INCLUDE_DIR = `pkg-config --variable=includedir Qt5Core`
CC = gcc
CXX = g++
LINK = g++
CPPFLAGS = -DNDEBUG -I.\
	-I$(PYROOT)/includes\
	-I$(DIR)/../src\
	-I/usr/include/python2.7\
	-I$(QT_INCLUDE_DIR)\
	-I$(QT_INCLUDE_DIR)/QtCore\

CFLAGS = -pipe -fPIC -Wall -W
CXXFLAGS = -pipe -fPIC -Wall -W
LFLAGS = -L.. -Wl,-rpath,. -Wl,-rpath,.. -shared -Wl,--version-script=ici.exp
SIP=$(PYROOT)/bin/sip
SIP_FLAGS = -e -w -r -k -I$(QT_INCLUDE_DIR) -x VendorID -t WS_X11 -t Qt_5_4_0 -x Py_v3 -I$(PYROOT)/sip
LIBS = -lici
.SUFFIXES: .c .o .cpp .cc .cxx .C .sip


%.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.cc.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.C.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.c.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<


all: $(TARGET)


$(CPPFILES): $(SIPFILE)
	$(SIP) $(SIP_FLAGS) -c . $<

$(OFILES): $(CPPFILES)

$(TARGET): $(OFILES)
	@echo '{ global: initici; local: *; };' > ici.exp
	$(LINK) $(LFLAGS) -o $(TARGET) $(OFILES) $(LIBS)

install: $(TARGET)
	@test -d $(DESTDIR)/usr/lib/python2.7/dist-packages || mkdir -p $(DESTDIR)/usr/lib/python2.7/dist-packages
	cp -f $(TARGET) $(DESTDIR)/usr/lib/python2.7/dist-packages/$(TARGET)
	strip $(DESTDIR)/usr/lib/python2.7/dist-packages/$(TARGET)

clean:
	-rm -f $(TARGET)
	-rm -f sipicicmodule.*
	-rm -f sipiciICISettings.*
	-rm -f sipiciICISettingsContext.*
	-rm -f ici.exp
