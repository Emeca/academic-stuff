CPPFLAGS=-Wall -ggdb -static
CC=g++
SRC=EasyBMP.cpp
OUTPUT=EasyBMP.o

OBJ=$(patsubst %.cpp,%.o,$(SRC))

all: $(OBJ)
	
clean:
	$(RM) $(OUTPUT)
