CC = gcc
CPPFLAGS = -Wall -W -Werror

INPUT = main.c

OBJ := $(patsubst %.c, %.o, $(INPUT))

all: $(OBJ)
	$(CC) -o scheduler $(OBJ)

clean:
	$(RM) scheduler $(OBJ)

