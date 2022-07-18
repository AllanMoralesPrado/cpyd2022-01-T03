# Variables
CC=gcc
CFLAGS=-Wall -g3
LDFLAGS=-lm
MKDIR=mkdir -p
DEL=rm -fr

carpetas:
	$(MKDIR) build dist

clean:
	$(DEL) build dist *.o

funciones.o: carpetas funciones.c
	$(CC) $(CFLAGS) -c funciones.c -o build/funciones.o

main.o: carpetas main.c
	$(CC) $(CFLAGS) -c main.c -o build/main.o

all: carpetas funciones.o main.o
	$(CC) $(CFLAGS) -o dist/app build/funciones.o build/main.o $(LDFLAGS)
	$(DEL) build

.PHONY: all
.DEFAULT_GOAL := all
