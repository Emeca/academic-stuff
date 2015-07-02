#include "interface.h"

Interface::Interface(string logfile)
{
	char titulo1[] = "<C></B/U>Corretor ortografico Uhet - Algoritmos e Estrutura de Dados<!B!U>";
	char label[] = "Entrada: ";
	
	char titulo2[] = "</B>Palavras nao reconhecidas: <!B>\n";
	char titulo3[] = "</B>Possiveis correcoes: <!B>\n";
	
	f = new ofstream(logfile.c_str(), ios::out | ios::trunc);
	
	curses_tela = initscr();
	cdk_tela = initCDKScreen(curses_tela);	
	initCDKColor();

	cdk_entrada = newCDKMentry(cdk_tela, LEFT, TOP, titulo1, label, A_BOLD,
							   '.', vCHAR, 0, 3, 2, 1, TRUE, FALSE);

	if (cdk_entrada == (CDKMENTRY *) NULL) {		
		destroyCDKScreen (cdk_tela);
		endCDK();

		cout << "Nao foi possivel criar o objeto CDKMENTRY!" << endl;
		exit(1);
	}
	
	cdk_palavras = newCDKScroll(cdk_tela, LEFT, TOP+10, RIGHT, -10, COLS/2-4,
								titulo2, (char **) NULL, 0, TRUE, A_REVERSE, TRUE,
								TRUE);
	npalavras = 0;

	if (cdk_palavras == (CDKSCROLL *) NULL) {
		destroyCDKScreen (cdk_tela);
		endCDK();
		
		cout << "Nao foi possivel criar o objeto CDKSCROLL(cdk_palavras) !!!" << endl;
		exit(2);
	}
	
	cdk_escolhas.push_back(newCDKScroll(cdk_tela, RIGHT, TOP+10, RIGHT, -10,
						   COLS/2-4, titulo3, (char **) NULL, 0, TRUE,
						   A_REVERSE, TRUE, TRUE) );

	if (cdk_escolhas.at(0) == (CDKSCROLL *) NULL) {
		destroyCDKScreen (cdk_tela);
		endCDK();
		
		cout << "Nao foi possivel criar o objeto CDKSCROLL(cdk_escolhas) !!!" << endl;
		exit(3);
	}
	
	refreshCDKScreen(cdk_tela);
}

Interface::~Interface() {
	
	delwin(curses_tela);
	endCDK ();

	f->close();
}

void
Interface::tokenize(const string &str, vector<string> &tokens,
					const string &delimiters = " ")
{
	/* Skip delimiters at beginning */
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	/* Find first "non-delimiter" */
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while ((string::npos != pos) || (string::npos != lastPos)) {
		/* Found a token, add it to the vector */
		tokens.push_back(str.substr(lastPos, pos - lastPos));

		/* Skip delimiters.  Note the "not_of" */
		lastPos = str.find_first_not_of(delimiters, pos);
		
		/* Find next "non-delimiter" */
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void
Interface::lerEntrada (vector<string> &vEntrada)
{
	curs_set(2);
	activateCDKMentry (cdk_entrada, (chtype *) NULL);

	string aux( (const char *) getCDKMentryValue (cdk_entrada) );
	tokenize(aux, vEntrada, " *!?.,-;:/@#$%\"\\/+=_");
}

void
Interface::palavraCerta (string palavra)
{
	string buffer = palavra + " --> OK\n";
	f->write(buffer.c_str(), buffer.size());
}

void
Interface::palavraErrada(string palavra, vector<string> escolhas)
{
	char *itens[200];
	int n = getCDKScrollItems (cdk_palavras, itens);
	npalavras = n+1;

	itens[n] = copyChar((char*) palavra.c_str());
	setCDKScrollItems (cdk_palavras, itens, n+1, false);

	if (n == 0) cdk_escolhas.clear();

	if (escolhas.size() > 0) {
		char **aux = (char **) malloc(sizeof(char *) * escolhas.size());

		for (unsigned i = 0; i < escolhas.size(); i++)
			aux[i] = (char *) escolhas.at(i).c_str();

		char txt[] = "</B>Possiveis correcoes: <!B>\n";
		cdk_escolhas.push_back(newCDKScroll(cdk_tela, RIGHT, TOP+10, RIGHT,
							   -10, COLS/2-4, txt, aux, escolhas.size(), FALSE,
							   A_REVERSE, TRUE, TRUE));
	}
}

int
Interface::lerEscolha (string &add)
{
	const char *buttons[] = {"Substituir", "Adicionar", "Cancelar", "Sair"};
	int i;

	char titulo2[] = "</B>Palavras nao reconhecidas: <!B>\n";
	char titulo3[] = "</B>Possiveis correcoes: <!B>\n";
	CDKSCROLL *nullScroll1 = newCDKScroll(cdk_tela, LEFT, TOP+10, RIGHT, -10,
										  COLS/2-4, titulo2, (char **) NULL, 0,
										  TRUE, A_REVERSE, TRUE, TRUE);
	CDKSCROLL *nullScroll2 = newCDKScroll(cdk_tela, RIGHT, TOP+10, RIGHT, -10,
										  COLS/2-4, titulo3, (char **) NULL, 0,
										  TRUE, A_REVERSE, TRUE, TRUE);

	if (cdk_escolhas.size() > 0)
		drawCDKScroll(cdk_escolhas.front(), true);
	else
		drawCDKScroll(nullScroll2, true);

	if (npalavras > 0)
		i = activateCDKScroll(cdk_palavras, (chtype *)NULL);
	else
		activateCDKScroll(nullScroll1, (chtype *)NULL);
	
	if (npalavras > 0)
		activateCDKScroll(cdk_escolhas.at(i), (chtype *) NULL);
	else
		activateCDKScroll(nullScroll2, (chtype *) NULL);

	char *itens1[256], *itens2[256];
	char temp[256];
	char *mesg[3];

	if (npalavras > 0) {
		getCDKScrollItems (cdk_palavras, itens1);
		getCDKScrollItems (cdk_escolhas.at(i), itens2);
		mesg[0] = copyChar((char*) "<C></B>O que voce deseja fazer?<!B>");
		sprintf(temp, "Substituir <%s> por <%s>", itens1[i], itens2[i]);
		mesg[1] = copyChar(temp);
		sprintf(temp, "Adicionar <%s> no dicionario.", itens1[i]);
		mesg[2] = copyChar(temp);

		cdk_pergunta = newCDKDialog(cdk_tela, CENTER, CENTER, mesg, 3,
									(char **) buttons, 4, A_REVERSE, TRUE,
									TRUE, FALSE);
	} else
		cdk_pergunta = newCDKDialog(cdk_tela, CENTER, CENTER, NULL, 0,
								    (char **) buttons, 4, A_REVERSE, TRUE,
									TRUE, FALSE);

	int res = activateCDKDialog(cdk_pergunta, (chtype *) NULL);
	destroyCDKDialog(cdk_pergunta);

	if (npalavras > 0) {

		if (res == 0) {
			sprintf(temp, "%s --> Substituido por <%s>.\n", itens1[i], itens2[i]);
			string aux (copyChar(temp));
			f->write(aux.c_str(), aux.size());

			vector<CDKSCROLL *>::iterator it = cdk_escolhas.begin() + i;
			deleteCDKScrollItem(cdk_palavras, i);
			cdk_escolhas.erase(it);
			npalavras--;
		}

		if (res == 1) {
			sprintf(temp, "%s --> Adicionado no dicionario.\n", itens1[i]);
			string aux (copyChar(temp));
			f->write(aux.c_str(), aux.size());

			vector<CDKSCROLL *>::iterator it = cdk_escolhas.begin() + i;
			deleteCDKScrollItem(cdk_palavras, i);
			cdk_escolhas.erase(it);
			npalavras--;

			add.assign(itens1[i]);
		}		
	}

	return res;
}
