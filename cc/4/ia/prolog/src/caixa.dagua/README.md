Considere uma base de dados que contém informações sobre diversos modeloos de caixas d'água, na seguinte forma:

```
caixa(Modelo, [Altura, Largura, Profundidade]).
```

Desenvolva os seguintes programas:

- Volume de um determinado Modelo
```
volume(Modelo, Volume)
```

- Medida conforme o tipo
```
medida(Modelo, Tipo, Medida)
```
 - tipo **a** retorna Altura
 - tipo **l** retorna Largura
 - tipo **p** retorna Profundidade

Interrogue Prolog para obter as seguintes informaçôes:

- a) Quais recipientes tem capacidade maior que 50m3?
- b) Quais recipientes possuem a mesma altura e largura?
- c) Quantos recipientes tem profundidade maior que 2m?
- d) Quantos recipientes tem volume entre 50 e 70m3?
