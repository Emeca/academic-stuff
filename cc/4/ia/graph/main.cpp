#include <fstream>
#include <stdlib.h>

#include "grafo.hpp"

Grafo *
load_grafo(string nome_arquivo)
{
	Grafo *grafo = new Grafo();

	ifstream fin(nome_arquivo.c_str());
	if (fin) {					// arquivo aberto com sucesso!
		string str;
		getline(fin, str);
		while (!fin.eof()) {

			//parser de cada linha
			int pos_espaco = str.find(" ");
			string s1 = str.substr(0, pos_espaco);
			str = str.substr(pos_espaco + 1);
			pos_espaco = str.find(" ");
			string s2 = str.substr(0, pos_espaco);
			int num = atoi(str.substr(pos_espaco + 1).c_str());

			grafo->add_vertice(s1);
			grafo->add_vertice(s2);
			grafo->add_link(s1, s2, num);
			grafo->add_link(s2, s1, num);

			getline(fin, str);
		}
	} else {
		cerr << "erro ao abrir o arquivo" << endl;
		exit(-1);
	}

	return grafo;
}

int
main(int argc, char *argv[])
{
	Grafo *g = load_grafo("file.txt");
	g->print_agenda();

	cout << "maravilha alberto!" << endl;
	return 0;
}
