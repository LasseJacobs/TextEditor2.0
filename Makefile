#C++ Makefile
CC=g++

CFLAGS=-g -c -Wall -O0
LDFLAGS=
PNAME=hello
OBJECTS=main.o mainwindow.o commandhandler.o fileio.o

CFLAGS += `pkg-config --cflags gtkmm-3.0`
LDFLAGS += `pkg-config --libs gtkmm-3.0`

all: clean build

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


clean:
	rm -rf *o $(PNAME)
	echo 'clean done..'
