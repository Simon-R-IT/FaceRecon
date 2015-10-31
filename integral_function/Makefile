#Basic Makefile

#Compilers and options
CC=gcc
CPPFLAGS=`pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS=`pkg-config --libs sdl` -lSDL_image

SRC= int_image.c
OBJ= ${SRC:.c=.o}

all: main

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f int_image

#END

