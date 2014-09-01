#
# Makefile for fixchksum
#

CC=gcc
APP=fixchksum
INCLUDES=-I.
OPTIONS=-O2 -Wall
CFLAGS=$(INCLUDES) $(OPTIONS)
SRCS=fixchksum.c
OBJECTS = fixchksum.o

WINCC=/usr/local/cross-tools/bin/i386-mingw32msvc-gcc
WINCFLAGS=-Wall -O2 -fomit-frame-pointer -s -I/usr/local/cross-tools/include -D_WIN32 -DWIN32
WINLIBS=
WINOBJECTS = fixchksum.obj

all: $(APP)

$(APP): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(APP)
	strip $(APP)

clean:
	rm -f $(APP).o
	rm -f $(APP)

install:
	cp -f $(APP) /usr/local/bin/

win: $(APP).exe

$(APP).exe: $(WINOBJECTS)
	$(WINCC) $(WINCFLAGS) $(WINOBJECTS) -o $(APP).exe $(WINLIBS)

fixchksum.obj: fixchksum.c
	$(WINCC) -o $@ $(WINCFLAGS) -c $<

winclean:
	rm -f $(APP).obj
	rm -f $(APP).exe

