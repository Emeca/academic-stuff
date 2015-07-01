#include "parser.hh"

void
Parser::init()
{
	numero_linha = 0;
	conf_aux = NULL;
}

Parser::Parser(Conf * conf, string file)
{
	init();
	try {
		ifstream fin(file.c_str());
		if (fin) {
			conf_aux = conf;
			bool fim = false;
			while (!fim) {
				string s;
				getline(fin, s);
				numero_linha++;
				if (fin.eof())
					fim = true;
				else
					analise_lexica(s);
			}
			fin.close();
		} else {
			cerr << ">> problemas em acessar o arquivo: " << file << endl;
			exit(0);
		}
/* teste de impressao
		conf_aux->superficie->print();
		conf_aux->camera->print();
		conf_aux->iluminacao->print();
		conf_aux->reflexao->print();
*/
	}
	catch(int erro)
	{
		cerr << ">> problemas em Parser::Parser(Conf* conf, string file) " <<
			erro << endl;
		exit(0);
	}
}

void
Parser::erro(string linha)
{
	cout << ">> problemas no arquivo de configuracao na linha: " << numero_linha
		<< " -> opcao nao suportada: " << linha << endl;
	exit(0);
}

bool
Parser::superficie(string linha)
{
//  cout << ">> entrou em Parser::superficie com a seguinte linha[" << numero_linha << "]: " << linha << endl;
	int
		pos = linha.find('=');
	if (pos > -1) {
		string
		str_ini(linha, 0, pos);
		string
		str_fim(linha, pos + 1, linha.length());
		if (str_ini == "a")
			conf_aux->superficie->vet[A] = (float)atof(str_fim.c_str());
		else if (str_ini == "b")
			conf_aux->superficie->vet[B] = (float)atof(str_fim.c_str());
		else if (str_ini == "c")
			conf_aux->superficie->vet[C] = (float)atof(str_fim.c_str());
		else if (str_ini == "d")
			conf_aux->superficie->vet[D] = (float)atof(str_fim.c_str());
		else if (str_ini == "e")
			conf_aux->superficie->vet[E] = (float)atof(str_fim.c_str());
		else if (str_ini == "f")
			conf_aux->superficie->vet[F] = (float)atof(str_fim.c_str());
		else if (str_ini == "g")
			conf_aux->superficie->vet[G] = (float)atof(str_fim.c_str());
		else if (str_ini == "h")
			conf_aux->superficie->vet[H] = (float)atof(str_fim.c_str());
		else if (str_ini == "j")
			conf_aux->superficie->vet[J] = (float)atof(str_fim.c_str());
		else if (str_ini == "k")
			conf_aux->superficie->vet[K] = (float)atof(str_fim.c_str());
		else
			erro(linha);
	} else
		erro(linha);
	return true;
}

bool Parser::camera(string linha)
{
//  cout << ">> entrou em Parser::camera com a seguinte linha[" << numero_linha << "]: " << linha << endl;
	int
		pos = linha.find('=');
	if (pos > -1) {
		string
		str_ini(linha, 0, pos);
		string
		str_fim(linha, pos + 1, linha.length());
		if (str_ini == "exterior.cx")
			conf_aux->camera->exterior[CX] = (float)atof(str_fim.c_str());
		else if (str_ini == "exterior.cy")
			conf_aux->camera->exterior[CY] = (float)atof(str_fim.c_str());
		else if (str_ini == "exterior.cz")
			conf_aux->camera->exterior[CZ] = (float)atof(str_fim.c_str());
		else if (str_ini == "exterior.rx")
			conf_aux->camera->exterior[RX] = (float)atof(str_fim.c_str());
		else if (str_ini == "exterior.ry")
			conf_aux->camera->exterior[RY] = (float)atof(str_fim.c_str());
		else if (str_ini == "exterior.rz")
			conf_aux->camera->exterior[RZ] = (float)atof(str_fim.c_str());
		else if (str_ini == "interior.largura")
			conf_aux->camera->interior[LARGURA] = (float)atof(str_fim.c_str());
		else if (str_ini == "interior.altura")
			conf_aux->camera->interior[ALTURA] = (float)atof(str_fim.c_str());
		else if (str_ini == "interior.px")
			conf_aux->camera->interior[PX] = (float)atof(str_fim.c_str());
		else if (str_ini == "interior.py")
			conf_aux->camera->interior[PY] = (float)atof(str_fim.c_str());
		else if (str_ini == "interior.distancia_focal")
			conf_aux->camera->interior[DISTANCIA_FOCAL] =
				(float)atof(str_fim.c_str());
		else
			erro(linha);
	} else
		erro(linha);
	return true;
}

bool
Parser::iluminacao(string linha)
{
//  cout << ">> entrou em Parser::iluminacao com a seguinte linha[" << numero_linha << "]: " << linha << endl;
	int pos = linha.find('=');
	if (pos > -1) {
		string
		str_ini(linha, 0, pos);
		string
		str_fim(linha, pos + 1, linha.length());
		if (str_ini == "posicao.x")
			conf_aux->iluminacao->posicao[X] = (float)atof(str_fim.c_str());
		else if (str_ini == "posicao.y")
			conf_aux->iluminacao->posicao[Y] = (float)atof(str_fim.c_str());
		else if (str_ini == "posicao.z")
			conf_aux->iluminacao->posicao[Z] = (float)atof(str_fim.c_str());
		else if (str_ini == "ambiente.r")
			conf_aux->iluminacao->ambiente[CR] = (float)atof(str_fim.c_str());
		else if (str_ini == "ambiente.g")
			conf_aux->iluminacao->ambiente[CG] = (float)atof(str_fim.c_str());
		else if (str_ini == "ambiente.b")
			conf_aux->iluminacao->ambiente[CB] = (float)atof(str_fim.c_str());
		else if (str_ini == "indice.r")
			conf_aux->iluminacao->indice[CR] = (float)atof(str_fim.c_str());
		else if (str_ini == "indice.g")
			conf_aux->iluminacao->indice[CG] = (float)atof(str_fim.c_str());
		else if (str_ini == "indice.b")
			conf_aux->iluminacao->indice[CB] = (float)atof(str_fim.c_str());
		else
			erro(linha);
	} else
		erro(linha);
	return true;
}

bool
Parser::reflexao(string linha)
{
//  cout << ">> entrou em Parser::reflexao com a seguinte linha[" << numero_linha << "]: " << linha << endl;
	int pos = linha.find('=');

	if (pos > -1) {
		string
		str_ini(linha, 0, pos);
		string
		str_fim(linha, pos + 1, linha.length());
		if (str_ini == "difuso.r")
			conf_aux->reflexao->difuso[CR] = (float)atof(str_fim.c_str());
		else if (str_ini == "difuso.g")
			conf_aux->reflexao->difuso[CG] = (float)atof(str_fim.c_str());
		else if (str_ini == "difuso.b")
			conf_aux->reflexao->difuso[CB] = (float)atof(str_fim.c_str());
		else if (str_ini == "espectral.r")
			conf_aux->reflexao->espectral[CR] = (float)atof(str_fim.c_str());
		else if (str_ini == "espectral.g")
			conf_aux->reflexao->espectral[CG] = (float)atof(str_fim.c_str());
		else if (str_ini == "espectral.b")
			conf_aux->reflexao->espectral[CB] = (float)atof(str_fim.c_str());
		else if (str_ini == "ambiente.r")
			conf_aux->reflexao->ambiente[CR] = (float)atof(str_fim.c_str());
		else if (str_ini == "ambiente.g")
			conf_aux->reflexao->ambiente[CG] = (float)atof(str_fim.c_str());
		else if (str_ini == "ambiente.b")
			conf_aux->reflexao->ambiente[CB] = (float)atof(str_fim.c_str());
		else if (str_ini == "n")
			conf_aux->reflexao->n = (float)atof(str_fim.c_str());
		else
			erro(linha);
	} else
		erro(linha);
	return true;
}

bool
Parser::analise_lexica(string linha)
{
	if ((linha[0] != '#') && (linha.length() > 0)) {
//      cout << ">> entrou em Parser::analise_lexica com a seguinte linha[" << numero_linha << "]: " << linha;
		int
			pos = linha.find('.');
		if (pos > -1) {
			string
			str_ini(linha, 0, pos);
			string
			str_fim(linha, pos + 1, linha.length());
//          cout << " || " << str_ini << " || " << str_fim << endl;
			if (str_ini == "superficie")
				superficie(str_fim);
			else if (str_ini == "camera")
				camera(str_fim);
			else if (str_ini == "iluminacao")
				iluminacao(str_fim);
			else if (str_ini == "reflexao")
				reflexao(str_fim);
			else
				erro(linha);
		} else
			erro(linha);
	}
	return true;
}
