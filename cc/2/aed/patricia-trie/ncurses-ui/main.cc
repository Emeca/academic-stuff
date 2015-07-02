#include "main.h"

Program::Program(string fn)
{
	tree = new Tree ();
	ifstream *arq = new ifstream(fn.c_str(), ios::in);

	if (!arq) {
		cout << "Não foi possível abrir arquivo de dicionário " << fn << endl;
		exit(1);
	}

	char buffer[50];
	string s;

	cout << "Carregando a árvore, por favor aguarde..." << endl;
	while (arq->peek() != EOF) {
		arq->getline(buffer, 50);
		s.assign(buffer, arq->gcount());
		tree->add(s.c_str());
	}

	arq->close();

	interface = new Interface("log.txt");
}

Program::~Program () {
	delete interface;
	delete tree;
}

void
Program::run()
{
	vector<string> input;
	vector<string> select;

	interface->lerEntrada(input);
	select = input;

	for (unsigned i = 0; i < input.size(); i++)
		if (tree->consulta(input.at(i).c_str()))
			interface->palavraCerta(input.at(i));
		else
			interface->palavraErrada(input.at(i), select);

	string s;
	int i;
	do {
		i = interface->lerEscolha(s);
		if (i == 1) tree->add(s.c_str());
	} while (i != 3);
}

int
main(int argc, char *argv[])
{
	if (argc == 2) {
		Program * p = new Program(argv[1]);
		p->run();
		delete p;
	} else {
		cout << "Uso: " << argv[0] << " <arquivo de dicionario>" << endl;
	}

	return 0;
}
