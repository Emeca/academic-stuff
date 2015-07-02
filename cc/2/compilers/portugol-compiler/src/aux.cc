#include "aux.hh"

extern Processador *proc;

void
Variaveis::print(void)
{
	iterator it = begin();
	string s;

	for (; it != end(); it++) {

		s = *it;
		cout << s << endl;
	}
}

Exp::Exp()
{
}

Exp::Exp(string _token, int _tipo)
{
	token = _token;
	tipo = _tipo;
}

Exp::Exp(const char _token[], int _tipo)
{
	token = _token;
	tipo = _tipo;
}

string
Exp::getToken()
{
	return token;
}

int
Exp::getTipo()
{
	return tipo;
}

void
Exp::print()
{
	cout << token;
}

Exp *
Exp::getCopy()
{
	return new Exp(token, tipo);
}

Exp::~Exp()
{
}

void
Expressao::print()
{
	iterator it = begin();
	Exp s;

	for (; it != end(); it++) {

		s = *it;
		cout << s.getToken() /*<< "(" << s.getTipo() << ") " */ <<" ";

	}
	cout << endl;
};

Array::Array()
{
	sub_ini = 0;
	sub_fim = 0;
	tam = 0;
}

Array::Array(int ini, int fim, int n)
{
	sub_ini = ini;
	sub_fim = fim;
	tam = n;
}

int
Array::getIni()
{
	return sub_ini;
}

int
Array::getFim()
{
	return sub_fim;
}

int
Array::getTam()
{
	return tam;
}

Array *
Array::get()
{
	return new Array(sub_ini, sub_fim, tam);
}

Array::~Array()
{
}

Tipo::Tipo()
{
	tipo = _VOID;
	matriz = NULL;
}

Tipo::Tipo(int _tipo)
{
	tipo = _tipo;
	matriz = NULL;
}

Tipo::Tipo(int _tipo, Array * _matriz)
{
	tipo = _tipo;
	matriz = _matriz;
}

void
Tipo::setArray(Array * _matriz)
{
	matriz = _matriz;
}

Array *
Tipo::getArray()
{
	if (matriz)
		return matriz->get();

	return NULL;
}

int
Tipo::getTipo()
{
	return tipo;
}

Tipo *
Tipo::get()
{
	return (new Tipo(getTipo(), getArray()));

}

Tipo::~Tipo()
{
}

Simbolo::Simbolo()
{
	nome = NULL;
	tipo = NULL;
	inicializada = false;
}

Simbolo::Simbolo(string _nome, Tipo _tipo, bool ini)
{
	nome = new string(_nome);
	tipo = new Tipo(_tipo);
	inicializada = ini;
}

void
Simbolo::setNome(string _nome)
{
	if (nome)
		delete(nome);
	nome = new string(_nome);
}

void
Simbolo::setTipo(Tipo _tipo)
{
	if (tipo)
		delete(tipo);
	tipo = new Tipo(_tipo);
}

void
Simbolo::setIni(bool flag)
{
	inicializada = flag;
}

bool
Simbolo::getIni()
{
	return inicializada;
}

string *
Simbolo::getNome()
{
	return (new string(*nome));
}

Tipo *
Simbolo::getTipo()
{
	return (new Tipo(*tipo));
}

void
Simbolo::print()
{
	cout << "\r                   ini:" << inicializada
		<< "\r          tipo: " << tipo->getTipo()
		<< "\rnome: " << *nome;
}

Simbolo::~Simbolo()
{
	delete(nome);
	delete(tipo);
}

void
TSimbolo::print()
{
	list<Simbolo *>::iterator it = begin();
	Simbolo *sim;

	cout << "TABELA DE SIMBOLOS:" << endl;
	for (; it != end(); it++) {

		sim = *it;
		sim->print();
		cout << endl;
	}
}

bool
TSimbolo::existe(string _nome)
{
	list<Simbolo *>::iterator it = begin();
	Simbolo *sim = NULL;

	for (; it != end(); it++) {

		sim = *it;
		if (_nome == *sim->getNome()) {

			return true;
		}
	}
	return false;
}

Simbolo *
TSimbolo::getSimbolo(string nome)
{
	list<Simbolo *>::iterator it = begin();
	Simbolo *sim;

	for (; it != end(); it++) {

		sim = *it;
		if (*sim->getNome() == nome) {
			return new Simbolo(nome, *sim->getTipo(), sim->getIni());
		}
	}

	return NULL;
}

void
TSimbolo::atualiza(Simbolo * sim)
{
	list < Simbolo * >::iterator it = begin();
	Simbolo *aux;
	bool achou = false;
	for (; it != end(); it++) {

		aux = *it;
		if (*aux->getNome() == *sim->getNome()) {
			*it = sim;
			achou = true;
			break;
		}
	}
	if (!achou)
		push_back(sim);
}

Registrador::Registrador()
{
	h = _LIVRE;
	l = _LIVRE;
}

void
Registrador::setH(unsigned int status)
{
	h = status;
}

void
Registrador::setL(unsigned int status)
{
	l = status;
}

void
Registrador::setF(unsigned int status)
{
	h = l = status;
}

unsigned int
Registrador::getH()
{
	return h;
}

unsigned int
Registrador::getL()
{
	return l;
}

void
Registrador::setNome(string s)
{
	nome = s;
}

string
Registrador::getNome()
{
	return nome;
}

unsigned int
Registrador::getF()
{
	if ((h == _USADO) && (l == _LIVRE))
		return _PARCIAL;
	if ((h == _LIVRE) && (l == _USADO))
		return _PARCIAL;
	if ((h == _USADO) && (l == _USADO))
		return _USADO;
	if ((h == _LIVRE) && (l == _LIVRE))
		return _LIVRE;

	return -1;
}

Processador::Processador()
{
	reg[0].setNome("ax");
	reg[1].setNome("bx");
	reg[2].setNome("cx");
	reg[3].setNome("dx");
	pilha = new Pilha();
}

void
Processador::setStatus(string nome, unsigned int status)
{
	switch (nome[1]) {
	case 'a': {
			if (nome[2] == 'l')
				reg[0].setL(status);
			else if (nome[2] == 'h')
				reg[0].setH(status);
			else
				reg[0].setF(status);
		};
		break;
	case 'b': {
			if (nome[2] == 'l')
				reg[1].setL(status);
			else if (nome[2] == 'h')
				reg[1].setH(status);
			else
				reg[1].setF(status);
		};
		break;
	case 'c': {
			if (nome[2] == 'l')
				reg[2].setL(status);
			else if (nome[2] == 'h')
				reg[2].setH(status);
			else
				reg[2].setF(status);
		};
		break;

	case 'd': {
			if (nome[2] == 'l')
				reg[3].setL(status);
			else if (nome[2] == 'h')
				reg[3].setH(status);
			else
				reg[3].setF(status);
		};
		break;
	}
}

unsigned int
Processador::getStatus(string nome)
{
	switch (nome[1]) {
	case 'a': {
			if (nome[2] == 'l')
				return reg[0].getL();
			if (nome[2] == 'h')
				return reg[0].getH();
			return reg[0].getF();
		};
		break;

	case 'b': {
			if (nome[2] == 'l')
				return reg[1].getL();
			if (nome[2] == 'h')
				return reg[1].getH();
			return reg[1].getF();
		};
		break;
	case 'c': {
			if (nome[2] == 'l')
				return reg[2].getL();
			if (nome[2] == 'h')
				return reg[2].getH();
			return reg[2].getF();
		};
		break;
	case 'd': {
			if (nome[2] == 'l')
				return reg[3].getL();
			if (nome[2] == 'h')
				return reg[3].getH();
			return reg[3].getF();
		};
		break;
	}

	return -1;
}

string
Processador::getLivre()
{
	for (int i = 0; i < 4; i++) {
		if (reg[i].getF() == _LIVRE) {
			reg[i].setF(_USADO);
			return reg[i].getNome();
		}
	}

	return "";
}

Pilha *
Processador::getPilha()
{
	return pilha;
}

Processador::~Processador()
{
	delete(pilha);
}

void
Pilha::print()
{
	iterator it = begin();
	Exp e;

	cout << endl << "pilha:" << endl;
	for (; it != end(); it++) {

		e = *it;
		e.print();
		cout << endl;
	}
	cout << "fim da pilha" << endl << endl;
}

Codigo::Codigo()
{
}

void
Codigo::make_conta(string inst, int op)
{
	proc->getPilha()->pop_back();
	proc->getPilha()->pop_back();
	proc->getPilha()->push_back(Exp("", op));
	cout << "\r\tpop ax" << endl;
	cout << "\r\tpop bx" << endl;
	cout << "\r\t" << inst << " bx" << endl;
	cout << "\r\tpush ax" << endl;
}

void
Codigo::declara(TSimbolo * table)
{
	list < Simbolo * >::iterator it = table->begin();
	Simbolo *sim = NULL;
	int tam;

	for (; it != table->end(); it++) {
		sim = *it;
		cout << "V_" << *sim->getNome() << ":" << endl;
		switch (sim->getTipo()->getTipo()) {
		case _INT:{
				tam = 2;
				break;
			}
		case _FLOAT:{
				tam = 6;
				break;
			}
		case _BOOL:{
				tam = 1;
				break;
			}
		case _CHAR:{
				tam = 1;
				break;
			}
		}
		for (int i = 0; i < tam; i++) {
			cout << "\r\tnop" << endl;
		}
	}
}

void
Codigo::expressao(Expressao * exp)
{
	if (!exp)
		cout << "nao alocado" << endl;
	else {
		list < Exp >::iterator it = exp->begin();
		Exp e;
		int tipo;

		for (; it != exp->end(); it++) {

			e = *it;
			tipo = e.getTipo();
			switch (tipo) {
			case _MAIS_:{
					make_conta("add", _MAIS_);
				}
				break;
			case _MENOS_:{
					make_conta("sub", _MENOS_);
				}
				break;
			case _VEZES_:{
					make_conta("mul", _VEZES_);
				}
				break;
			case _DIVIDIR_:{
					make_conta("div", _DIVIDIR_);
				}
				break;

			case _INTEIRO_:{
					Exp g(e.getToken(), e.getTipo());
					proc->getPilha()->push_back(g);
					cout << "\r\tpush " << e.getToken() << endl;
				}
				break;

			case _ATRIBUICAO_:{

					Exp f = proc->getPilha()->back();
					proc->getPilha()->pop_back();
					proc->getPilha()->pop_back();
					cout << "\r\tpop ax" << endl;
					cout << "\r\tmov @V_" << f.getToken() << " ax" << endl;

				}
				break;

			case _VARIAVEL_:{
					Exp g(e.getToken(), e.getTipo());
					proc->getPilha()->push_back(g);
				}
				break;

			}
		}
	}
}

void
Codigo::se(string label)
{
	cout << "@" << label << ":" << endl;
}

void
Codigo::exp_relacional(Expressao * exp, string label)
{
	if (!exp)
		cout << "nao alocado" << endl;
	else {

		list < Exp >::iterator it = exp->begin();
		Exp e;
		int tipo;

		for (; it != exp->end(); it++) {

			e = *it;
			tipo = e.getTipo();
			switch (tipo) {
			case _MAIOR_: {

					cout << "\r\tpop ax" << endl;
					cout << "\r\tpop bx" << endl;
					cout << "\r\tcmp ax,bx" << endl;
					cout << "\r\tjmenor @" << label << endl;
				}
				break;

			default: {
					Expressao *eaux = new Expressao();
					Exp g(e.getToken(), e.getTipo());
					eaux->push_back(g);
					expressao(eaux);
					delete(eaux);
				}
				break;
			}
		}
	}
}

void
Codigo::jmp(string label)
{
	cout << "\r\tjmp @" << label << endl;
}

void
Codigo::fim(string label)
{
	cout << "@" << label << ":" << endl;
}

void
Codigo::atribuicao(string var)
{
	/*
	 * nesse ponto tudo jah foi calculado,
	 * eh soh mov pra area de memoria da
	 * variavel <var> o q tah no topo da pilha do processador
	 */
	proc->getPilha()->pop_back();
	cout << "\r\tpop ax" << endl;
	cout << "\r\tmov @V_" << var << " ax" << endl;
}

Codigo::~Codigo()
{
}
