/* vim: set ts=4 sw=4: */

#ifndef _FAT_HH
#define _FAT_HH 1

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>

#define TAM_TABELA 65536
#define TAM_BLOCO  4096
#define NDIRETORIO 255

using namespace std;

class Data
{
	private:
		union
		{
			short dia:5;
			short mes:4;
			short ano:7;
			short fulldata;
		} data;

	public:
		void setDia(short dia);
		short getDia();
		void setMes(short mes);
		short getMes();
		void setAno(short ano);
		short getAno();
		void setData(short fulldata);
		short getData();
};

class Hora
{
	private:
		union
		{
			short hora:5;
			short minuto:6;
			short segundo:5;
			short fulltempo;
		} tempo;

	public:
		void setHora(short hora);
		short getHora();
		void setMinuto(short minuto);
		short getMinuto();
		void setSegundo(short segundo);
		short getSegundo();
		void setTempo(short fulltempo);
		short getTempo();
		string getTempoStr();
};

class Dados
{
	public:
		char nome[8];
		char extensao[3];
		char reservado[8];
		bool atributo;
		Data data;
		Hora hora;
		int tamanho;
		int inicio;
};

class EntradaDiretorio
{
	private:
		Dados dir;

	public:
		EntradaDiretorio();
		void setNome(string nome);
		string getNome();
		void setExtensao(string extensao);
		string getExtensao();
		string getNomeString();
		void setAtributo(bool atributo);
		bool getAtributo();
		string getsAtrib()
		{
			if (getAtributo())
				return "d";
			else
				return "a";
		};
		void print();
		void setData(short dia, short mes, short ano);
		short getData();
		void setHora(short hora, short minuto, short segundo);
		short getHora();
		string getHoraStr();
		void setTamanho(int tamanho);
		int getTamanho();
		void setInicio(int inicio);
		int getInicio();
};

class Fat
{
	private:
		int tabela[TAM_TABELA];

	public:
		/* chama o metodo clear */
		Fat();

		/* chama loadFat */
		Fat(string vfs);

		/* carrega a fat do arquivo para o objeto */
		bool loadFat(string nome);

		/* retorna a primeira posicao livre na fat */
		int livre();

		bool eof(int atual);

		/* preenche pos de fat, com info */
		void setPos(int pos, int info);

		int getProx(int atual);

		/* limpa a fat na memoria */
		void clear();

		/* grava a fat no arquivo */
		void toFile(string vfs);
};

class Bloco
{
	private:
		union
		{
			unsigned char byte[TAM_BLOCO];
			Dados blocoDir[128]; /* TAM_BLOCO / SIZEOF(EntradaDiretorio) */
		} bloco;

	public:
		Bloco();

		/*
		void setType(bool type);
		bool getType();
		void makeBloco(unsigned char *v);
		*/
};

class Diretorio
{
	private:
		/* lista com as entradas de diretorio do diretorio corrente */
		list<EntradaDiretorio> dir;

		/* tabela com os ponteiros para os diretorios anteriores */
		vector<unsigned> path;

		unsigned getDirIni(char *nome);
		void setPath(unsigned fatDirIni);

	public:
		/* chama clearRaiz() */
		Diretorio();

		Diretorio(string vfs);

		void add(EntradaDiretorio d);

		void loadDir();
		void loadDir(list < Bloco > b);

		/* esvazia uma lista de diretorio q esta no objeto */
		void clear();

		/* grava uma raiz vazia no arquivo */
		bool clearRaiz(string nome);

		/* carrega o diretorio raiz para o objeto */
		bool loadRaiz(string nome);

		/* grava a raiz da memoria no disco */
		bool raiztoFile(string nome);

		/* retorn ponteiro para lista de entrada de diretorio */
		list<EntradaDiretorio> *getListDir();

		void printDir();
};

class AreaDados
{
	private:
		fstream fout;
		unsigned base;
		string vfs;

	public:
		AreaDados(string vfs);

		void gravarBloco(Bloco b, unsigned pos);
		void lerBloco(Bloco & b, unsigned pos);
		void clear();
};

class Arquivo
{
	private:
		vector<Bloco> buffer;

	public:
		Arquivo();
		void append(Bloco);
		void clear();
		Bloco removeFirst();
		bool eof();
};

#endif /* _FAT_HH  */
