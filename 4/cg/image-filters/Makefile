CC=g++
CPPFLAGS=-Wall -ggdb -lm -static
HOME=./


INPUT=main.cc bmp.cc matrix.cc filtro.cc
OUTPUT=a.out

EB_PATH=./lib


OBJ=$(patsubst %.cc,%.o,$(INPUT))

all: easybmp $(OBJ) 
	$(CC) -o $(OUTPUT) $(OBJ) $(EB_PATH)/*.o

easybmp:
	make -C $(EB_PATH)

clean:
	cd $(EB_PATH) && make clean
	$(RM) $(OUTPUT) $(OBJ) *.*~

