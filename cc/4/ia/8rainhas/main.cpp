#include <iostream>
#include <vector>

#include "tabuleiro.hpp"

using namespace std;

class Estados : public vector<Matriz *>
{
	private:
	public:
		int ultimo_h[4];
		int numero_de_passos;
		int numero_de_reinicios;

		Estados();
		void reseta();
		void gera_estados(Matriz * m);
		void print();
		void calc_h();
		int get_menor_h();
		Matriz *get_matriz_menor_h();
		void print_hs();
};

Estados::Estados()
{
	vector < Matriz * >();
	this->reseta();
	numero_de_passos = 0;
	numero_de_reinicios = 0;
}

void
Estados::reseta()
{
	ultimo_h[0] = -1;
	ultimo_h[1] = -1;
	ultimo_h[2] = -1;
	ultimo_h[3] = -1;
}

void
Estados::calc_h()
{
	Matriz *m;
	for (unsigned i = 0; i < this->size(); i++) {

		m = (*this)[i];
		m->calc_h();
	}
}

void
Estados::gera_estados(Matriz * m)
{
	this->clear();
	numero_de_passos++;
	for (int i = 0; i < LINHAS; i++) {
		int pos = m->get_pos_rainha(i);
		for (int j = pos - 1; j >= 0; j--) {

			Matriz *n = new Matriz(m);
			n->set(i, pos, 0);
			n->set(i, j, 1);
			this->push_back(n);
		}
		for (int j = pos + 1; j < COLUNAS; j++) {

			Matriz *n = new Matriz(m);
			n->set(i, pos, 0);
			n->set(i, j, 1);
			this->push_back(n);
		}
	}
}

void
Estados::print()
{
	Matriz *m;
	for (unsigned i = 0; i < this->size(); i++) {

		m = (*this)[i];
		cout << endl;
		m->imprime_matriz();
		cout << endl;
	}
}

void
Estados::print_hs()
{
	cout << MAGENTA;
	for (unsigned i = 0; i < this->size(); i++) {

		cout << "[" << (*this)[i]->get_h() << "] ";
	}
	cout << NEUTRO << endl;
}

Matriz *
Estados::get_matriz_menor_h()
{
	Matriz *m = (*this)[0];
	int menor = (*this)[0]->get_h();

	for (unsigned i = 1; i < this->size(); i++) {

		if (menor >= (*this)[i]->get_h()) {

			menor = (*this)[i]->get_h();
			m = (*this)[i];
		}
	}
	return m;
}

int
Estados::get_menor_h()
{
	Matriz *m;
	int menor = (*this)[0]->get_h();

	for (unsigned i = 1; i < this->size(); i++) {

		m = (*this)[i];
		if (menor > m->get_h())
			menor = m->get_h();
	}
	return menor;
}

int
main()
{
	Estados *e = new Estados();
	Matriz *m = new Matriz(RANDOM);

	while (m->get_h() != 0) {
		e->gera_estados(m);
		e->calc_h();
		m = e->get_matriz_menor_h();

		e->ultimo_h[3] = e->ultimo_h[2];
		e->ultimo_h[2] = e->ultimo_h[1];
		e->ultimo_h[1] = e->ultimo_h[0];
		e->ultimo_h[0] = m->get_h();

		if ((e->ultimo_h[0] == e->ultimo_h[2])
			&& (e->ultimo_h[1] == e->ultimo_h[3])) {

			delete(m);
			m = new Matriz(RANDOM);
			e->reseta();
			e->numero_de_reinicios++;
		}

		m->imprime_matriz();
	}

	cout << MAGENTA << "numero de passos: " << VERDE << e->
		numero_de_passos << endl;
	cout << MAGENTA << "numero de reinicios: " << VERDE << e->
		numero_de_reinicios << endl;
	cout << NEUTRO;
	delete(m);
	delete(e);
	return 0;
}
