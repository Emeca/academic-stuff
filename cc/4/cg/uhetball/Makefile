CC=gcc
FLAGS=-Wall -ggdb -lm -lglut


INPUT=uhetball.c
OBJ=uhetball.o
OUTPUT=a.out

#all: objetos $(OBJ) 
#	$(CC) -o $(OUTPUT) $(OBJ) $(FLAGS) 
#
#objetos: $(INPUT) 
#	$(CC) -c $(INPUT) $(FLAGS)

all: $(INPUT)
	$(CC) $(INPUT) $(FLAGS)

clean:
	$(RM) $(OUTPUT) $(OBJ) *.*~

