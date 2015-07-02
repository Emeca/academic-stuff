CPPFLAGS = -Wall -ggdb
BIN = a.out
SRC= graph.cpp main.cpp 

OBJ = $(patsubst %.cpp,%.o,$(SRC))

all: $(OBJ)
	g++ -o $(BIN) $(CPPFLAGS) $(OBJ)

clean:
	rm -f *~ $(BIN) $(OBJ)
