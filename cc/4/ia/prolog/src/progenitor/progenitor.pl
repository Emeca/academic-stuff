% vim: filetype=prolog

progenitor(tataravo, bisavo).
progenitor(bisavo, vo).
progenitor(vo, pai).
progenitor(pai, eder).
progenitor(eder, filho).

descendentes(P1, P2, [P1]):-
	 progenitor(P1, P2).

descendentes(P1, P2, [P1 | Cauda]):-
	progenitor(P1, X),
	descendentes(X, P2, Cauda).

conta_descendentes(P1, P2, 1):-
	progenitor(P1, P2).

conta_descendentes(P1, P2, Cont):-
	progenitor(P1, X),
	conta_descendentes(X, P2, TC),
	Cont is TC + 1.

lista_descendentes(0).
lista_descendentes(X):-
	descendentes(_, _, L),
	conta_lista(L, X),

conta_lista([], 0).
conta_lista([_ | Cauda], Cont):-
	conta_lista(Cauda, N),
	Cont is N + 1.

imprime([]):-
	nl,
	print('Fim da Lista'),
	nl.

imprime([Cab | Cauda]):-
	print(Cab),
	nl,
	imprime(Cauda).
