CC = gcc
CFLAGS = -W -Wall -Werror
BISON = bison
FLEX = flex

calc: uhetcomp.tab.o lex.yy.o 
	$(CC) $(CFLAGS) -o comp uhetcomp.tab.o lex.yy.o -lfl

uhetcomp.tab.o: uhetcomp.tab.c
	$(CC) $(CFLAGS) -c uhetcomp.tab.c

uhetcomp.tab.c: uhetcomp.y
	$(BISON) -d uhetcomp.y

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

lex.yy.c: uhetcomp.l
	$(FLEX) uhetcomp.l lex.yy.c

clean:
	rm -f *.o *.c *.h *~ *.flc comp

