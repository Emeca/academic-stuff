/* vim: set ts=4 sw=4: */

#include "fat.hh"

Fat::Fat()
{
	clear();
}

Fat::Fat(string vfs)
{
	loadFat(vfs);
}

void
Fat::toFile(string vfs)
{
	ofstream fout(vfs.c_str(), ios::out | ios::in | ios::binary);
	if (fout.good()) {
		fout.seekp(NDIRETORIO * sizeof(EntradaDiretorio));

		fout.write(reinterpret_cast < char *>(tabela), sizeof(tabela));
		fout.close();
	}
}

bool
Fat::loadFat(string vfs)
{
	ifstream fin(vfs.c_str(), ios::in | ios::binary);

	if (fin.good()) {
		fin.seekg(NDIRETORIO * sizeof(EntradaDiretorio));

		for (int i = 0; i < TAM_TABELA; i++)
			fin.read((char *)&(tabela[i]), sizeof(int));

		fin.close();
		return true;
	}
	return false;
}

void
Fat::clear()
{
	for (int i = 0; i < TAM_TABELA; i++)
		tabela[i] = -1;
}

int
Fat::livre()
{
	int i = 0;

	while ((i < TAM_TABELA) && (tabela[i] != -1))
		i++;

	return i;
}

void
Fat::setPos(int pos, int info)
{
	tabela[pos] = info;
}

int
Fat::getProx(int atual)
{
	return tabela[atual];
}

bool
Fat::eof(int atual)
{
	return (atual == tabela[atual]);
}

Bloco::Bloco()
{
	for (int i = 0; i < TAM_BLOCO; i++)
		bloco.byte[i] = 0;
}

AreaDados::AreaDados(string vfs)
{
	AreaDados::vfs = vfs;
	base = NDIRETORIO * sizeof(EntradaDiretorio) + sizeof(Fat);
}

void
AreaDados::gravarBloco(Bloco b, unsigned pos)
{
	fout.open(vfs.c_str(), ios::out | ios::in | ios::binary);
	fout.seekp(base + pos);
	fout.write(reinterpret_cast < char *>(&b), sizeof(b));
	fout.close();
}

void
AreaDados::lerBloco(Bloco & b, unsigned pos)
{
	fout.open(vfs.c_str(), ios::out | ios::in | ios::binary);
	fout.seekp(base + pos);
	fout.read(reinterpret_cast < char *>(&b), sizeof(Bloco));
	fout.close();
}

void
AreaDados::clear()
{
	fout.open(vfs.c_str(), ios::out | ios::binary);
	fout.seekp(base);

	Bloco b;
	for (int i = 0; i < TAM_TABELA; i++)
		fout.write(reinterpret_cast < char *>(&b), sizeof(Bloco));

	fout.close();
}
