CC=g++
CPPFLAGS=-Wall -ggdb -lm
HOME=./


INPUT=main.cc conf.cc bmp.cc parser.cc render.cc
OUTPUT=a.out

EB_PATH=./lib


OBJ=$(patsubst %.cc,%.o,$(INPUT))

all: easybmp $(OBJ)
	$(CC) -o $(OUTPUT) $(OBJ) $(EB_PATH)/*.o

easybmp:
	make -C $(EB_PATH)

clean:
	make -C $(EB_PATH) clean
	$(RM) $(OUTPUT) $(OBJ) *.bmp *.*~

