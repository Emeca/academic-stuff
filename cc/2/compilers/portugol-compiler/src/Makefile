SRC = aux.cc
BIN = portugol

CFLAGS = -W -Wall -Werror
CXX = g++

all: aux.o portugol.bison.o portugol.flex.o
	$(CXX) $(CFLAGS) portugol.bison.o portugol.flex.o aux.o -o $(BIN) $(LDFLAGS)

aux.o: aux.cc aux.hh
	$(CXX) $(CFLAGS) -c aux.cc

portugol.bison.cc: portugol.y portugol.l
	bison -t -v --defines=portugol.bison.h --output-file=portugol.bison.cc portugol.y

portugol.bison.o: portugol.bison.cc
	$(CXX) -c portugol.bison.cc

portugol.flex.cc: portugol.l
	flex -o portugol.flex.cc portugol.l

portugol.flex.o: portugol.flex.cc
	$(CXX) -c portugol.flex.cc


clean:
	rm -f portugol.*.cc portugol.*.h *.output *.o $(BIN)
