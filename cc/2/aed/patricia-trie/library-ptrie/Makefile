SRC = tree.cc no.cc main.cc
OUT = ptree

CPPFLAGS = -W -Werror -Wall
CXX = g++

all: bin lib

bin: main.o tree.o no.o
	$(CXX) $(CPPFLAGS) -o $(OUT) $^

tree.o: tree.cc tree.hh include.hh
	$(CXX) $(CPPFLAGS) -c $<

no.o: no.cc no.hh include.hh
	$(CXX) $(CPPFLAGS) -c $<

main.o: main.cc tree.hh
	$(CXX) $(CPPFLAGS) -c $<

lib:
	ar rvs libptrie.a tree.o no.o

clean:
	rm -f $(OUT) *.o *.a
