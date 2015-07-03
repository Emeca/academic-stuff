CC=g++
CPPFLAGS=-Wall -ggdb -lm -static
HOME=./


INPUT=main.cc bmp.cc matrix.cc filtro.cc
OUTPUT=a.out

EB_PATH=./lib


OBJ=$(patsubst %.cc,%.o,$(INPUT))

all: EasyBMP.o $(OBJ) 
	$(CC) -o $(OUTPUT) $(OBJ) $(EB_PATH)/*.o

EasyBMP.o:
	cd $(EB_PATH) && make all

clean:
	cd $(EB_PATH) && make clean
	$(RM) $(OUTPUT) $(OBJ) *.*~

