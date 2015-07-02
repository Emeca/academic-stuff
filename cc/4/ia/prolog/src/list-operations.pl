%vim set filetype=prolog

concatena([], L, L).
concatena([H | L1], L2, [H | L3]):-
	concatena(L1, L2, L3).

conta_elementos([], 0).
conta_elementos([_ | C], N):-
	conta_elementos(C, Y),
	N is Y + 1.

soma_elementos([H], H).
soma_elementos([H | C], X):-
	soma_elementos(C, Y),
	X is Y + H.

nesimo_elemento([H | _], 0, H).
nesimo_elemento([_ | C], N, E):-
	A is N-1,
	nesimo_elemento(C, A, E).

menor(UM, DOIS, UM):-
	UM < DOIS, !.
menor(_, DOIS, DOIS).

get_menor([H], H).
get_menor([H | C], R):-
	get_menor(C, X),
	menor(H, X, R).

maior(UM, DOIS, UM):-
	UM > DOIS, !.
maior(_, DOIS, DOIS).

get_maior([H], H).
get_maior([H | C], R):-
	get_maior(C, A),
	maior(H, A, R).

inserir_elemento_fim([], X, [X]).
inserir_elemento_fim([H | C], X, [H | L]):-
	inserir_elemento(C, X, L).

inverte([],[]).
inverte([H | C], L):-
	inverte(C, A),
	concatena(A, [H], L).
%	concatena([H], A, L).
