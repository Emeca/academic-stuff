Árvore Patricia
===============

Esta e' uma implementacao de uma classe de arvore patricia estao implementados
metodos de insercao e busca de palavras.

Arquivos
--------

- **main.cc**: contem testes da arvore
- **no.hh**: classe que representa um no da arvore
- **no.cc**: implementa o .hh
- **tree.hh**: classe das operacaes na arvore, insercao e busca
- **tree.cc**: implementa o .hh
- **include.hh**: includes nescessarios e criacao de tipos
- **Makefile**: arquivo com regras para compilacao

Compilação
----------

Para compilar basta o comando: make, sera gerado o executavel com o nome
uhetree que executa os testes implementados no main.cc e os arquivos objetos .o
Para limpar, apagar .o e o binario: make clean

TODO
----

Seria interessante implementar um metodo para remocao da palavra da arvore e um
para retornar uma lista de sugestoes para uma palavra nao contida na arvore.

Autor
-----

- Eder Ruiz Maria
- <eder.rm82@gmail.com>
