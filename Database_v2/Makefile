CC=clang

CPPFLAGS=
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= database.c
OBJ= ${SRC:.c=.o}

all: main

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f database
