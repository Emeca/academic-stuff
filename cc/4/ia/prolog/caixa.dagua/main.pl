% vim: filetype=prolog

caixa(a, [1, 2, 3]).
caixa(b, [4, 5, 6]).
caixa(c, [7, 8, 9]).
caixa(d, [11, 11, 11]).

volume(Modelo, Volume):-
	caixa(Modelo, [A, L, P]),
	Volume is A * L * P.

medida(Modelo, a, Medida):-
	caixa(Modelo, [Medida, _, _]).

medida(Modelo, l, Medida):-
	caixa(Modelo, [_, Medida, _]).

medida(Modelo, p, Medida):-
	caixa(Modelo, [_, _, Medida]).

letraA(X, N):-
	volume(X, V),
	V >= N.

letraB(X):-
	caixa(X, [A, L, _]),
	A == L.

conta_lista([], 0).

conta_lista([_ | Calda], X):-
	conta_lista(Calda, Y),
	X is Y + 1.

auxC(Modelo):-
	caixa(Modelo, [_, _, P]),
	P >= 9.

letraC(R):-
	findall(Modelo, auxc(Modelo), L),
	conta_lista(L, R).

auxD(Modelo):-
	volume(Modelo, Volume),
	Volume > 100,
	Volume < 1000.

letraD(R):-
	findall(Modelo, auxD(Modelo), L),
	conta_lista(L, R).
