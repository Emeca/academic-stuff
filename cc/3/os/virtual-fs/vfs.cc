/* vim: set ts=4 sw=4: */

#include "vfs.hh"

Vfs::Vfs(string nome, bool flag)
{
	if (flag) {

		setNomeVfs(nome);
		dir = new Diretorio(nome);
		fat = new Fat(nome);
		dados = new AreaDados(getNomeVfs());
	} else {
		setNomeVfs(nome);
		dir = new Diretorio();
		fat = new Fat();
		dados = new AreaDados(getNomeVfs());
	}
}

void
Vfs::setNomeVfs(string nome)
{
	Vfs::nome = nome;
}

string
Vfs::getNomeVfs()
{
	return nome;
}

void
Vfs::format()
{
	dir->clearRaiz(nome);
	dir->clear();
	fat->clear();
	fat->toFile(nome);
	dados->clear();
}

void
Vfs::formatq()
{
	dir->clearRaiz(nome);
	dir->clear();
	fat->clear();
	fat->toFile(nome);
}

void
Vfs::touch(string nomeArq, string extArq)
{
	EntradaDiretorio *ed = new EntradaDiretorio();

	ed->setNome(nomeArq);
	ed->setExtensao(extArq);
	ed->setData(0, 0, 0);
	ed->setHora(0, 0, 0);
	ed->setTamanho(1);
	ed->setAtributo(0);
	ed->setInicio(fat->livre());

	dir->add(*ed);
	dir->raiztoFile(nome);

	fat->setPos(ed->getInicio(), ed->getInicio());
	fat->toFile(nome);
}

void
Vfs::close(string nome)
{
	fat->toFile(nome);
	fat->clear();

	dir->raiztoFile(nome);
	dir->clear();
}

void
Vfs::connect(string nome)
{
	dir->loadRaiz(nome);
	fat->loadFat(nome);
}

void
Vfs::ls()
{
	list <EntradaDiretorio> *aux = dir->getListDir();
	list <EntradaDiretorio>::iterator i = aux->begin();

	while (i != aux->end()) {

		i->print();
		i++;
	}
}
