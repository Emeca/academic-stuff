% vim: filetype=prolog

rota(narandiba, pirapo).
rota(pirapo, prudente).
rota(narandiba, tarabai).
rota(tarabai, pirapo).

caminho(Origem, Destino, [Origem]):-
	rota(Origem,Destino).

caminho(Origem, Destino, [Origem|Cauda]):-
	rota(Origem, X),
	caminho(X, Destino, Cauda).
