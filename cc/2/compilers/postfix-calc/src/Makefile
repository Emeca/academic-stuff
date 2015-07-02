all: calc.cc
	g++ -o calc calc.cc -lfl -lm -ggdb -Wall

calc.cc: calc.l
	flex -o calc.cc calc.l

clean:
	rm -f calc.cc calc *~
