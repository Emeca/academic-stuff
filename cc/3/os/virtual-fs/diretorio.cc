/* vim: set ts=4 sw=4: */

#include <string.h>

#include "fat.hh"

void
Data::setDia(short dia)
{
	Data::data.dia = dia;
}

short
Data::getDia()
{
	return Data::data.dia;
}

void
Data::setMes(short mes)
{
	Data::data.mes = mes;
}

short
Data::getMes()
{
	return Data::data.mes;
}

void
Data::setAno(short ano)
{
	Data::data.ano = ano;
}

short
Data::getAno()
{
	return Data::data.ano;
}

void
Data::setData(short fulldata)
{
	data.fulldata = fulldata;
}

short
Data::getData()
{
	return data.fulldata;
}

void
Hora::setHora(short hora)
{
	Hora::tempo.hora = hora;
}

short
Hora::getHora()
{
	return Hora::tempo.hora;
}

void
Hora::setMinuto(short minuto)
{
	Hora::tempo.minuto = minuto;
}

short
Hora::getMinuto()
{
	return Hora::tempo.minuto;
}

void
Hora::setSegundo(short segundo)
{
	Hora::tempo.segundo = segundo;
}

short
Hora::getSegundo()
{
	return Hora::tempo.segundo;
}

void
Hora::setTempo(short fulltempo)
{
	tempo.fulltempo = fulltempo;
}

short
Hora::getTempo()
{
	return tempo.fulltempo;
}

string
Hora::getTempoStr()
{

	char aux[15];
	for (int i = 0; i < 15; i++)
		aux[i] = '\0';

	sprintf(aux, "%i:%i:%i", getHora(), getMinuto(), getSegundo());

	return string(aux, 15);
}

EntradaDiretorio::EntradaDiretorio()
{
	setNome("        ");
	setExtensao("   ");
	setAtributo(false);
	setData(0, 0, 0);
	setHora(0, 0, 0);
	setTamanho(0);
	setInicio(-1);
}

void
EntradaDiretorio::setNome(string nome)
{
	strncpy(dir.nome, nome.c_str(), 8);
}

string
EntradaDiretorio::getNome()
{
	return string(dir.nome);
}

void
EntradaDiretorio::setExtensao(string extensao)
{
	strncpy(dir.extensao, extensao.c_str(), 3);
}

string
EntradaDiretorio::getExtensao()
{
	return string(dir.extensao);
}

void
EntradaDiretorio::setAtributo(bool atributo)
{
	dir.atributo = atributo;
}

bool
EntradaDiretorio::getAtributo()
{
	return dir.atributo;
}

void
EntradaDiretorio::setData(short dia, short mes, short ano)
{
	dir.data.setDia(dia);
	dir.data.setMes(mes);
	dir.data.setAno(ano);
}

short
EntradaDiretorio::getData()
{
	return dir.data.getData();
}

void
EntradaDiretorio::setHora(short hora, short minuto, short segundo)
{
	dir.hora.setHora(hora);
	dir.hora.setMinuto(minuto);
	dir.hora.setSegundo(segundo);
}

short
EntradaDiretorio::getHora()
{
	return dir.hora.getTempo();
}

string
EntradaDiretorio::getHoraStr()
{
	return dir.hora.getTempoStr();
}

void
EntradaDiretorio::setTamanho(int tamanho)
{
	dir.tamanho = tamanho;
}

int
EntradaDiretorio::getTamanho()
{
	return dir.tamanho;
}

void
EntradaDiretorio::setInicio(int inicio)
{
	dir.inicio = inicio;
}

int
EntradaDiretorio::getInicio()
{
	return dir.inicio;
}

string
EntradaDiretorio::getNomeString()
{
	return getNome() + "." + getExtensao() + " " + getHoraStr();
}

void
EntradaDiretorio::print()
{
	cout << getNome() + "." + getExtensao() + "\r\t\t" + getsAtrib() << endl;
}

Diretorio::Diretorio()
{
}

Diretorio::Diretorio(string vfs)
{
	loadRaiz(vfs);
}

void
Diretorio::add(EntradaDiretorio d)
{
	dir.push_back(d);
}

void
Diretorio::clear()
{
	dir.clear();
}

bool
Diretorio::loadRaiz(string nome)
{
	ifstream fin(nome.c_str(), ios::in | ios::binary);
	if (fin.good()) {
		EntradaDiretorio ed;
		for (int i = 0; i < NDIRETORIO; i++) {
			fin.read(reinterpret_cast <char *>(&ed), sizeof(EntradaDiretorio));

			if (ed.getInicio() != -1)
				dir.push_back(ed);
			else
				break;
		}
		fin.close();
		return true;
	}
	return false;
}

bool
Diretorio::raiztoFile(string nome)
{
	if (path.empty()) {
		ofstream fout(nome.c_str(), ios::out | ios::in | ios::binary);
		if (fout.good()) {

			list < EntradaDiretorio >::iterator It = dir.begin();
			EntradaDiretorio ed;

			for (unsigned i = 0; i < dir.size(); i++) {

				ed = *It++;
				fout.write(reinterpret_cast < char *>(&ed),
						   sizeof(EntradaDiretorio));
			}
			fout.close();
			return true;

		}
	}
	return false;
}

bool
Diretorio::clearRaiz(string nome)
{
	/* isso apaga o conteudo do arquivo e recria ele */
	ofstream fout(nome.c_str(), ios::out | ios::binary);

	EntradaDiretorio ed;
	if (fout.good()) {

		for (unsigned i = 0; i < NDIRETORIO; i++) {

			fout.write(reinterpret_cast < char *>(&ed),
					   sizeof(EntradaDiretorio));

		}
		fout.close();
		return true;
	}
	return false;
}

list<EntradaDiretorio> *
Diretorio::getListDir()
{
	list<EntradaDiretorio> *aux = new list<EntradaDiretorio>;

	*aux = dir;
	return aux;
}

void
Diretorio::printDir()
{
	EntradaDiretorio ed;
	string s;

	for (unsigned i = 0; i < dir.size(); i++) {

		ed = *dir.begin();
		s = ed.getNomeString();
		cout << s << endl;
	}
}
