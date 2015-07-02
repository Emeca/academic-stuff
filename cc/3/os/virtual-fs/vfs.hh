/* vim: set ts=4 sw=4 :*/

#ifndef _VFS_HH
#define _VFS_HH 1

#include "fat.hh"

class Vfs
{
	private:
		Diretorio *dir;
		Fat *fat;
		AreaDados *dados;
		string nome;

	public:
		Vfs();

		/*
		 * se flag == true, estancia vfs carregando o diretorio raiz e a fat pra
		 * memoria se flag == false, cria um 
		 */
		Vfs(string nome, bool flag);
		void setNomeVfs(string nome);
		string getNomeVfs();

		/* format completo, cria uma fat, raiz e area de dados nula */
		void format();

		/* format rapido, apaga apenas a fat e o raiz */
		void formatq();
		
		void touch(string nomeArq, string extArq);
		string cd(string nomeDir);
		void mkdir(string nomeDir);
		void ls();

		/* "fecha" sistema de arquivo */
		void close(string nome);

		/* "conecta" ao arquivo binario */
		void connect(string nome);
};

#endif /* _VFS_HH 1 */
