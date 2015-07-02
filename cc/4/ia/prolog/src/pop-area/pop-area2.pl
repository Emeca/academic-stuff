%vim: filetype=prolog

%pop_area(Estado, Populacao, Area).

pop_area(sp, 90, 9).
pop_area(pr, 80, 8).
pop_area(na, 1000, 1).
pop_area(rs, 70, 7).
pop_area(ac, 10, 1).

menor_elemento([X], X).

menor_elemento([H|C], X):-
	menor_elemento(C, Y),
	H >= Y, X is Y, !;
	X is H.

menor_estado(X):-
	findall(A, pop_area(_,_,A), L),
	menor_elemento(L, N),
	pop_area(X, _, N).

densidade(E, X):-
	pop_area(E, P, A),
	X is P / A.

get_maior([M], M).

get_maior([H | C], M):-
	get_maior(C, N),
	H =< N, M is N, !;
	M is H.

mais_densamente_povoado(X):-
	findall(D, densidade(_, D), Lista),
	get_maior(Lista, Y),
	densidade(X, Y).


