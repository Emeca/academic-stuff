CPPFLAGS = -W -Wall -Werror 
BIN = 8rainhas

SRC = tabuleiro.cpp main.cpp 

OBJ = $(patsubst %.cpp,%.o,$(SRC))

all: $(OBJ)
	g++ -o $(BIN) $(CPPFLAGS) $(OBJ)

clean:
	rm -f *~ $(BIN) $(OBJ)
