#ifndef __GRAFO_HPP
#define __GRAFO_HPP

#include <iostream>
#include <vector>

#define NONE 0
#define VISITADO 1
#define VISITANDO 2

using namespace std;

class Vertice;
class Arco;
class Aresta;
class Grafo;
class Agenda;

class Aresta
{
	private:
		int peso;
		int pos_origem;
		int pos_destino;

	public:
		Aresta(int pos_origem, int pos_destino, int peso);
		void set_origem(int origem);
		void set_destino(int destino);
		int get_origem();
		int get_destino();
		int get_peso();
};

class Arco:public vector <Aresta>
{
	public:
		Arco();
};

class Vertice
{
	private:
		string nome;
		int status;
		Arco *arco;

	public:
		Vertice(string nome);
		void set_nome(string nome);
		void set_status(int status);
		string get_nome();
		int get_status();
		void add_aresta(Aresta a);
		void uhet();
		void print_arco(Agenda * a);
		Arco *get_arco();
};

class Agenda:public vector<Vertice>
{
	public:
		Agenda();
};

class Grafo
{
	private:
	Agenda *agenda;
	int pos_raiz;

	public:
		Grafo();
		void add(string origem, string destino, int peso);
		bool add_link(string origem, string destino, int peso);
		bool add_vertice(string nome);
		void print_agenda();
		int get_pos_vertice(string v_nome);
};

#endif
