#include "no.hh"

No::No()
{
	radical = new string();
	subarvore = new Tlista();
	clear();
}

No::~No()
{
	delRadical();
	delSublista();
};

void
No::clear()
{
	radical->erase();
	subarvore->clear();
}

No::No(string value)
{
	radical = new string(value);
	subarvore = new Tlista();
}

void
No::setRadical(string value)
{
	*radical = value;
}

string
No::getRadical()
{
	return *radical;
}

bool
No::isRadicalEmpty()
{
	return radical->empty();
}

bool
No::isListaEmpty()
{
	return subarvore->empty();
}

bool
No::isEmpty()
{
	if ((radical->empty()) && (subarvore->empty()))
		return true;
	return false;
}

No *
No::getNo(const char letra)
{
	Tlista::iterator it;
	No *noaux;

	if (!subarvore->empty())
		for (it = subarvore->begin(); it != subarvore->end(); it++) {
			noaux = *it;
			char caux = *(noaux->getRadical().data());
			if (caux == letra)
				return noaux;
		}
	return NULL;
}

bool
No::isFilhoVaziu()
{
	Tlista::iterator it = subarvore->begin();
	No *no_aux = NULL;

	while (it != subarvore->end()) {

		no_aux = *it;
		if (no_aux->getRadical().empty())
			return true;
		it++;
	}
	return false;
}

void
No::printSubarvore()
{
	Tlista::iterator it = subarvore->begin();
	No noaux;

	while (it != subarvore->end()) {

		noaux = **it;
		cout << noaux.getRadical() << endl;
		it++;
	}
}

void
No::addSubarvore(No * novono)
{
	subarvore->push_back(novono);
}

No *
No::clone()
{
	return this;
}

void
No::delRadical()
{
	delete(radical);
}

void
No::delSublista()
{
	delete(subarvore);
}

Tlista *
No::getSubarvore()
{
	Tlista *aux = subarvore;
	return aux;
}
