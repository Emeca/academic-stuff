#ifndef _PARSER_HH
#define _PARSER_HH

#include <fstream>
#include <string>
#include <stdlib.h>

#include "conf.hh"

class Parser
{
	private:
	int numero_linha;
	Conf *conf_aux;
	bool analise_lexica(string linha);
	void init();
	void erro(string linha);
	bool superficie(string linha);
	bool camera(string linha);
	bool iluminacao(string linha);
	bool reflexao(string linha);

	public:
	Parser(Conf * conf, string file);
};

#endif
