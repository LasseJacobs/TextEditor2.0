#C++ Makefile
CC=g++

CFLAGS=-g -c -Wall -O0
LDFLAGS=
PNAME=hello
OBJECTS=main.o mainwindow.o commandhandler.o fileio.o closabletab.o scrollabletext.o memorynotebook.o

CFLAGS += `pkg-config --cflags gtkmm-3.0 gtksourceviewmm-3.0`
LDFLAGS += `pkg-config --libs gtkmm-3.0 gtksourceviewmm-3.0`

SRC=src
BIN=bin
SRC_CMD=$(SRC)/commands
SRC_WDGT=$(SRC)/widgets
SRC_UTIL=$(SRC)/utility

all: clean build

smart: build

build: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)/$(PNAME) $(LDFLAGS)

main.o: $(SRC)/main.cc
	$(CC) $(CFLAGS) $(SRC)/main.cc

mainwindow.o: $(SRC)/mainwindow.cc
	$(CC) $(CFLAGS) $(SRC)/mainwindow.cc

commandhandler.o: $(SRC_UTIL)/commandhandler.cc
	$(CC) $(CFLAGS) $(SRC_UTIL)/commandhandler.cc

fileio.o: $(SRC_UTIL)/fileio.cc
	$(CC) $(CFLAGS) $(SRC_UTIL)/fileio.cc

closabletab.o: $(SRC_WDGT)/closabletab.cc
	$(CC) $(CFLAGS) $(SRC_WDGT)/closabletab.cc

scrollabletext.o: $(SRC_WDGT)/scrollabletext.cc
	$(CC) $(CFLAGS) $(SRC_WDGT)/scrollabletext.cc

memorynotebook.o: $(SRC_WDGT)/memorynotebook.cc
	$(CC) $(CFLAGS) $(SRC_WDGT)/memorynotebook.cc

clean:
	rm -rf *o $(PNAME)
	echo 'clean done..'
