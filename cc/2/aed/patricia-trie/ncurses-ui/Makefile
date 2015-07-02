SRC = main.cc
OUT = ncurses-ui

LIB_PTRIE_DIR := $(shell realpath ../library-ptrie/)

#CXXFLAGS = -W -Wall -Werror -DNCURSES 
CXX = g++
CXXFLAGS = -W -Wall -Werror
LDFLAGS = -lcdk -lncurses

all: lib ui

main.o: main.cc main.h
	$(CXX) $(CXXFLAGS) -I$(LIB_PTRIE_DIR) -c $<

interface.o: interface.cc interface.h
	$(CXX) $(CXXFLAGS) -c $<

ui: main.o interface.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -L$(LIB_PTRIE_DIR) -o $(OUT) $^ -lptrie

lib:
	$(MAKE) -C $(LIB_PTRIE_DIR)

clean:
	$(MAKE) -C $(LIB_PTRIE_DIR) clean
	rm -f *.o $(OUT)
