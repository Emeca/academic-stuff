% vim: filetype=prolog

progenitor(tataravo, bisavo).
progenitor(bisavo, vo).
progenitor(vo, pai).
progenitor(pai, eu).

antepassado(P1, P2, [P1], 1):-
	progenitor(P1, P2).

antepassado(P1, P2, [P1|Caud], C):-
	progenitor(P1, X),
	antepassado(X, P2, Caud, TC), 
	C is TC + 1.

numero_geracoes(X):-
	findall(X, progenitor(X,_), L),
	conta(L,X). 

conta([], 0).
conta([Cab | Cauda], X):-
	conta(Cauda, N),
	X is N + 1.

imprime([]).
imprime([C | Cd]) :-
	print(C),
	print(' '),
	imprime(Cd).

concatena([], L, L).
concatena([X|L1], L2, [X|L3]) :-
	concatena(L1,L2,L3).
