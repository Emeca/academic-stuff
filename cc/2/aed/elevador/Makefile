SRC = fila.c main.c interface.c
OUTPUT = elevador
CC     = gcc
CFLAGS = -W -Wall -Werror

all: fila.o main.o interface.o
	$(CC) $(CFLAGS) -o $(OUTPUT) $^

fila.o: fila.c fila.h aux.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c fila.h interface.h mygetch.h
	$(CC) $(CFLAGS) -c $<

interface.o: interface.c interface.h fila.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f $(OUTPUT) *.o
