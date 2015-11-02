#Basic Makefile

#Compilers and options
CC=clang -fsanitize=address
CPPFLAGS=`pkg-config --cflags sdl` -MMD -MP 
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O3
LDFLAGS=
LDLIBS=`pkg-config --libs sdl` -lSDL_image

SRC= Preprocessing.c int_image.c
OBJ= ${SRC:.c=.o}

# dependencies files (produced from source files list)
DEP= ${SRC:.c=.d}

# include dependencies files
-include ${DEP}
 
all: int_image

int_image: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f ${DEP}
	rm -f int_image

#END

