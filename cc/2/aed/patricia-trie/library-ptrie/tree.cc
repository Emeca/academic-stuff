#include "tree.hh"

Tree::Tree()
{
	tamanho = 0;
	root = NULL;
}

Tree::~Tree()
{
	deltree();
};

unsigned
Tree::getTamanho()
{
	return tamanho;
}

No *
Tree::getRoot()
{
	return root;
}

void
Tree::add(string value)
{
	string sa1, sa2, radical;
	No *novo = NULL;
	if (root == NULL)
		root = new No(value);
	else {
		if (root->isRadicalEmpty())
			insere(value, root->getSubarvore());
		else {
			sa1 = value;
			sa2 = root->getRadical();
			radical = analise(sa1, sa2);

			/* radical existente nao sera utilizada */
			if (radical.empty()) {
				novo = root;
				root = new No();
				insere(sa1, root->getSubarvore());
				root->addSubarvore(novo);
			} else {

				/* radical fica igual consome radical da palavra, insere sufixo no sublista */
				if (radical.length() == root->getRadical().length()) {
					if (root->isListaEmpty())
						insere(sa2, root->getSubarvore());
					insere(sa1, root->getSubarvore());

				/* radical diminui, insere sufixo do radical */
				} else if (radical.length() < root->getRadical().length()) {
					/*
					 * anterior na sublista,
					 * consome o radical da palavra e insere na sublista
					 */
					novo = root;
					novo->setRadical(sa2);
					root = new No(radical);
					root->addSubarvore(novo);
					novo = new No(sa1);
					root->addSubarvore(novo);
				}
			}
		}
	}
	tamanho++;
}

void
Tree::insere(string value, Tlista *lista)
{
	string sa1 = value;
	string sa2, radical;
	No *no_aux = NULL;
	No *novo = NULL;
	Tlista::iterator it = lista->begin();

	if (lista->empty()) {
		novo = new No(value);
		lista->push_back(novo);
	} else {
		while (it != lista->end()) {
			no_aux = *it;
			sa2 = no_aux->getRadical();
			radical = analise(sa1, sa2);
			if (!radical.empty())
				break;
			it++;
		}

		/* insere no fim da lista atual */
		if (radical.empty()) {
			novo = new No(value);
			lista->push_back(novo);
		} else {
			if (radical.length() == value.length()) {
				if (sa1.empty()) {
					novo = new No(radical);
					no_aux->setRadical(sa2);
					novo->addSubarvore(no_aux);
					no_aux = new No(sa1);
					novo->addSubarvore(no_aux);
					*it = novo;
				} else
					insere(sa1, no_aux->getSubarvore());
			} else {
				if (radical.length() < value.length()) {
					if (sa2.empty()) {
						if (no_aux->isListaEmpty())
							insere(sa2, no_aux->getSubarvore());
						insere(sa1, no_aux->getSubarvore());
					} else {
						novo = new No(radical);
						no_aux->setRadical(sa2);
						novo->addSubarvore(no_aux);
						no_aux = new No(sa1);
						novo->addSubarvore(no_aux);
						*it = novo;
					}
				}
			}
		}
	}
}

bool
Tree::consulta(string value, No *no)
{

	string sa1 = value;
	string sa2 = no->getRadical();
	string radical = analise(sa1, sa2);

	if (!radical.empty()) {
		if (sa1.empty() && sa2.empty()) {
			if (no->isListaEmpty() || no->isFilhoVaziu())
				return true;

		} else {

			if (sa2.empty()) {

				Tlista *lista = no->getSubarvore();
				Tlista::iterator it = lista->begin();	//isso soh pode ser magica
				bool bool_aux;
				No *no_aux;

				while (it != lista->end()) {

					no_aux = *it;
					bool_aux = consulta(sa1, no_aux);
					if (bool_aux)
						return true;
					it++;
				}
			}
		}
	}
	return false;
}

bool
Tree::consulta(string value)
{
	if (root->getRadical().empty()) {

		Tlista *lista = root->getSubarvore();
		Tlista::iterator it = lista->begin();
		bool bool_aux;
		No *no_aux;

		while (it != lista->end()) {
			no_aux = *it;
			bool_aux = consulta(value, no_aux);
			if (bool_aux)
				return true;
			it++;
		}
	}
	return consulta(value, root);
}

bool
Tree::consome(stack<No *> *pilha, string value, No *no)
{
	string sa1 = value;
	string sa2 = no->getRadical();
	string radical = analise(sa1, sa2);

	if (!radical.empty() && sa2.empty()) {

		pilha->push(no);

		Tlista *lista = no->getSubarvore();
		Tlista::iterator it = lista->begin();
		No *no_aux = NULL;
		bool bool_aux;

		while (it != lista->end()) {

			no_aux = *it;
			bool_aux = consome(pilha, sa1, no_aux);
			if (bool_aux)
				return bool_aux;
			it++;
		}
	}
	return false;
}

stack<No *> *
Tree::empilha(string value)
{
	stack<No *> *pilha = new stack<No *>;

	if (root->getRadical().empty()) {

		Tlista *lista = root->getSubarvore();
		Tlista::iterator it = lista->begin();
		No *no_aux = NULL;
		bool bool_aux;

		while (it != lista->end()) {

			no_aux = *it;
			bool_aux = consome(pilha, value, no_aux);
			if (bool_aux)
				break;
			it++;
		}
	} else
		consome(pilha, value, root);

	return pilha;
}

string
Tree::pilha_to_string(stack < No *>*pilha)
{
	string s;
	stack < No *>p_aux(*pilha);
	while (!p_aux.empty()) {
		s = p_aux.top()->getRadical() + s;
		p_aux.pop();
	}
	return s;
}

void
Tree::chuta(No *no_inicial, stack <No *> pilha, vector < string > *vet,
			unsigned nivel)
{
	if (!no_inicial->getRadical().empty()) {

		pilha.push(no_inicial);

		Tlista *lista = no_inicial->getSubarvore();
		Tlista::iterator it;
		No *no_aux;

		while (it != lista->end()) {

			no_aux = *it;
			chuta(no_aux, pilha, vet, nivel - 1);
			it++;
		}
	} else
		vet->push_back(pilha_to_string(&pilha));
}

vector<string> *
Tree::sugestao(string value, unsigned nivel)
{
	vector<string> *vet = new vector < string >;
	stack<No *> pilha = *(empilha(value));
	chuta(pilha.top(), pilha, vet, nivel);

	return vet;
}

void
Tree::deltree()
{
	deltree(root);
}

void
Tree::deltree(No *no)
{
	if (no->isListaEmpty()) {

		no->delRadical();
		no->delSublista();

	} else {

		Tlista *lista = no->getSubarvore();
		Tlista::iterator it = lista->begin();
		No *no_aux = NULL;

		while (it != lista->end()) {

			no_aux = *it++;
			deltree(no_aux);
		}
	}
}

void
Tree::printArvore()
{
	if (root) {
		No *aux = root;
		printArvore(aux, 1);
	}
}

void
Tree::printArvore(No *root, unsigned nivel)
{
	Tlista *aux = root->getSubarvore();
	Tlista::iterator it;
	No *noaux;

	cout << nivel << " " << root->getRadical() << endl;

	for (it = aux->begin(); it != aux->end(); it++) {

		noaux = *it;
		printArvore(noaux, nivel + 1);
	}
}

string
Tree::analise(string & s1, string & s2)
{
	unsigned i = 0;
	unsigned j = 0;

	while (i < s1.length() && j < s2.length()) {

		if (s1[i] != s2[j])
			break;
		else {
			i++;
			j++;
		}
	}

	string r = s1.substr(0, i);
	s1 = s1.substr(i);
	s2 = s2.substr(j);

	return r;
}
