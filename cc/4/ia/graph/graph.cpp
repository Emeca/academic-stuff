#include "grafo.hpp"

Vertice::Vertice(string nome)
{
	Vertice::nome = nome;
	Vertice::status = NONE;
	arco = new Arco();
}

string
Vertice::get_nome()
{
	return nome;
}

int
Vertice::get_status()
{
	return status;
}

void
Vertice::add_aresta(Aresta a)
{
	arco->push_back(a);
}

void
Vertice::uhet()
{
	cout << "uhet!" << endl;
}

void
Vertice::print_arco(Agenda * a)
{
	for (unsigned i = 0; i < arco->size(); i++) {

		int pos = (*arco)[i].get_destino();
		cout << "(" << (*a)[pos].get_nome() << "," << (*arco)[i].
			get_peso() << ") ";
	}
}

Arco *
Vertice::get_arco()
{
	return arco;
}

Aresta::Aresta(int v1, int v2, int peso)
{
	Aresta::peso = peso;
	Aresta::pos_origem = v1;
	Aresta::pos_destino = v2;
}

int
Aresta::get_peso()
{
	return peso;
}

int
Aresta::get_destino()
{
	return pos_destino;
}

int
Aresta::get_origem()
{
	return pos_origem;
}

Arco::Arco()
{
	vector<Aresta>();
}

Agenda::Agenda()
{
	vector <Vertice>();
}

int
Grafo::get_pos_vertice(string v_name)
{
	for (unsigned i = 0; i < agenda->size(); i++) {

		if ((*agenda)[i].get_nome() == v_name)
			return i;
	}
	return -1;
}

bool
Grafo::add_vertice(string v_nome)
{
	if (get_pos_vertice(v_nome) < 0) {
		Vertice v(v_nome);
		agenda->push_back(v);
		return true;
	}
	return false;
}

bool
Grafo::add_link(string origem, string destino, int peso)
{
	int po = get_pos_vertice(origem);

	if (po > -1) { // o primeiro vertice estiver inserido
		int pd = get_pos_vertice(destino);
		if (pd > -1) { // o segundo vertice tb estiver inserido

			// cout << "/" << v1->get_nome() << "." << v2->get_nome() << "/" << endl;
			(*agenda)[po].add_aresta(Aresta(po, pd, peso));
			return true;
		}
	}
	return false;
}

void
Grafo::print_agenda()
{
	cout << "tamanho da agenda: " << agenda->size() << endl;
	for (unsigned i = 0; i < agenda->size(); i++) {

		Vertice v = (*agenda)[i];

		cout << "[" << v.get_nome() << /*"," << v.get_status() << */ "] -> "; // << endl;
		v.print_arco(agenda);
		cout << endl;
	}
}

Grafo::Grafo()
{
	agenda = new Agenda();
	pos_raiz = -1;
}
