#C++ Makefile
CC=g++

CFLAGS=-g -c -Wall -O0
LDFLAGS=
PNAME=hello
OBJECTS=main.o mainwindow.o commandhandler.o fileio.o closabletab.o scrollabletext.o memorynotebook.o

CFLAGS += `pkg-config --cflags gtkmm-3.0 gtksourceviewmm-3.0`
LDFLAGS += `pkg-config --libs gtkmm-3.0 gtksourceviewmm-3.0`

all: clean build

smart: build

build: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PNAME) $(LDFLAGS)

main.o: main.cc
	$(CC) $(CFLAGS) main.cc

mainwindow.o: mainwindow.cc
	$(CC) $(CFLAGS) mainwindow.cc

commandhandler.o: commandhandler.cc
	$(CC) $(CFLAGS) commandhandler.cc

fileio.o: fileio.cc
	$(CC) $(CFLAGS) fileio.cc

closabletab.o: closabletab.cc
	$(CC) $(CFLAGS) closabletab.cc

scrollabletext.o: scrollabletext.cc
	$(CC) $(CFLAGS) scrollabletext.cc

memorynotebook.o: memorynotebook.cc
	$(CC) $(CFLAGS) memorynotebook.cc

clean:
	rm -rf *o $(PNAME)
	echo 'clean done..'
