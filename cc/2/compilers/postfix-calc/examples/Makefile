all: exemplo1 exemplo2 exemplo3 exemplo4 exemplo5

exemplo1: exemplo1.c
	gcc -o exemplo1 exemplo1.c -lfl

exemplo1.c: exemplo1.l
	flex -o exemplo1.c exemplo1.l

exemplo2: exemplo2.c
	gcc -o exemplo2 exemplo2.c -lfl

exemplo2.c: exemplo2.l
	flex -o exemplo2.c exemplo2.l

exemplo3: exemplo3.c
	gcc -o exemplo3 exemplo3.c -lfl

exemplo3.c: exemplo3.l
	flex -o exemplo3.c exemplo3.l

exemplo4: exemplo4.c
	gcc -o exemplo4 exemplo4.c -lfl

exemplo4.c: exemplo4.l
	flex -o exemplo4.c exemplo4.l

exemplo5: exemplo5.c
	gcc -o exemplo5 exemplo5.c -lfl

exemplo5.c: exemplo5.l
	flex -o exemplo5.c exemplo5.l

clean:
	rm -f exemplo1 exemplo1.c
	rm -f exemplo2 exemplo2.c
	rm -f exemplo3 exemplo3.c
	rm -f exemplo4 exemplo4.c
	rm -f exemplo5 exemplo5.c
