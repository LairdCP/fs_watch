#if building outside of buildroot, you may need to specify which ccx with
#	make CXX=arm-sdc-linux-gnueabi-g++	
#
# License: ISC
# Copyright 2014 Laird

CFLAGS += -std=c99

LIBS += -linotifytools

all: fs_watch

fs_watch: fs_watch.o common.o
	$(CC) $(CFLAGS) $(LINKOPT) -o $@ fs_watch.o common.o $(LIBS)

clean:
	rm -f fs_watch *.o

