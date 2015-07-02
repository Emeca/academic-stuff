% vim: set filetype=prolog

% Densidade = Pop/Area 

pop_area(parana, 200, 5).
pop_area(rio_grande_do_sul, 300, 200).
pop_area(sao_paulo, 500, 400).
pop_area(rio_de_janeiro, 300, 10).

soma_lista([], 0).
soma_lista([Cab | Cauda], Soma):-
	soma_lista(Cauda, N),
	Soma is N + Cab.

densidade(Estado, D):-
	pop_area(Estado, Pop, Area),
	D is Pop/Area.

densidade_pais(X):-
	findall(Populacao, pop_area(_, Populacao, _), L),
	soma_lista(L, PopTotal),
	findall(Area, pop_area(_, _, Area), L2),
	soma_lista(L2, AreaTotal),
	X is PopTotal/AreaTotal.

menor_estado(X):-
	findall(Area, pop_area(_, _, Area), L),
	menor_elemento_lista(L, Menor),
	pop_area(X, _, Menor).

menor_elemento_lista([X], X):- !.
menor_elemento_lista([X , Y | Cauda], Menor):-
	X < Y,
	menor_elemento_lista([X | Cauda], Menor), !.

menor_elemento_lista([_, Y | Cauda], Menor) :-
	menor_elemento_lista([Y | Cauda], Menor).

menor_elemento(E1, E2, Menor) :- 
	E1 < E2, 
	Menor is E1, !;
	Menor is E2. 

imprime([]):-
	print('Fim'), nl.

imprime([X | Y]):-
	print(X),
	nl,
	imprime(Y).
