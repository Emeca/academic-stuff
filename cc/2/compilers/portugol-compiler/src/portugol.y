%{
	#include "aux.hh"

	#define YYERROR_VERBOSE


	int yyparse();
	int yylex();
	
	extern int yychar;
	extern char * yytext;
	extern int nlines;

	int yyerror (const char * s) {
		cerr 	<< "Erro na linha " 
				<< nlines 
				<< " no token \'" 
				<< yytext
				<< "\' => " 
				<< "\"" 
				<< s 
				<< "\"" 
				<< endl;
		return 0;
	}

	TSimbolo* table = NULL;
	Processador* proc = NULL;
	Codigo* gerador = NULL;
%}


%union {
	char STR[30];
	int INT;
	class Variaveis* var;
	class Tipo*	tip;
	class Declaracao* dec;
	class Expressao* exp;
}

%token FUNCAO PROCEDIMENTO
%token ALGORITMO DECLARE MATRIZ DE
%token T_INTEIRO T_REAL T_BOOLEANO T_CARACTERE
%token REFERENCIA INICIO FIM
%token SE ENTAO SENAO
%token MOD DIV NOT OP_LOGICO OP_RELACIONAL
%token REPITA ATE ENQUANTO FACA PARA

%token <STR> IDENTIFICADOR
%token <STR> INTEIRO
%token <STR> ATTRIB
%token <STR> NUMERO
%token <STR> VERDADEIRO FALSO

%token <INT> MAIS MENOS VEZES DIVID MAIOR

%token LITERAL
%token PONTO PONTOPONTO DOISPONTO PONTOVIRG VIRGULA
%token ABRECOLCH FECHACOLCH ABREPAR FECHAPAR 

%type <var> lista_de_identificadores
%type <tip> tipo
%type <tip> tipo_padrao
%type <exp> expressao
%type <exp> expressao_relacional
%type <exp> termo
%type <exp> fator
%type <exp> comando

%expect 6

%%

programa: 
	ALGORITMO IDENTIFICADOR PONTOVIRG comando_composto PONTO
	| ALGORITMO IDENTIFICADOR PONTOVIRG declaracoes comando_composto PONTO {
		gerador->declara(table);
	}
	| ALGORITMO IDENTIFICADOR PONTOVIRG subprogramas comando_composto PONTO
	| ALGORITMO IDENTIFICADOR PONTOVIRG declaracoes subprogramas comando_composto PONTO {

		gerador->declara(table);
	}
	;

declaracoes:
	| DECLARE variaveis  
	;

variaveis:
	lista_de_identificadores DOISPONTO tipo PONTOVIRG {
		
		Simbolo* sim;
		string str;
		list<string>::iterator it = $1->begin();

		for (; it != $1->end() ; it++){
				
				str = *it;
				if (!table->existe(str)){
//					cout << "inserindo: " << str << " na tabela"  << endl;
					sim = new Simbolo(str,*$3->get(),false);
					table->push_back(sim);
				} else {
					cout << "Segunda declaracao da variavel " << str << " na linha: " << nlines << endl;
					YYABORT;
				}
		}
		delete($1);
		delete($3);
	}
	| variaveis lista_de_identificadores DOISPONTO tipo PONTOVIRG {
	
		Simbolo* sim;
		string str;
		list<string>::iterator it = $2->begin();

		for (; it != $2->end() ; it++){

			str = *it;
			if (!table->existe(str)){
				sim = new Simbolo(str,*$4->get(),false);
				table->push_back(sim);
			} else {
				cout << "Segunda declaracao da variavel " << str << " na linha: " << nlines << endl;
				YYABORT;
			}
		}
		delete($2);
		delete($4);
	}
	;

lista_de_identificadores:

	IDENTIFICADOR {
		$$ = new Variaveis();
		$$->push_back($1);
	}
	
	| IDENTIFICADOR VIRGULA lista_de_identificadores {
		$3->push_front($1);
		$$ = $3;
	}
	;

tipo:
	tipo_padrao	{ 
		$$ = $1;
	}

	| MATRIZ ABRECOLCH INTEIRO PONTOPONTO INTEIRO FECHACOLCH DE tipo_padrao {
		
		//isso ainda eh uma gambi
		$$ = new Tipo(_INT);
	}
	;

tipo_padrao:
	T_INTEIRO		{ $$ = new Tipo(_INT);	}
	| T_REAL		{ $$ = new Tipo(_FLOAT);}
	| T_BOOLEANO 	{ $$ = new Tipo(_BOOL);	}
	| T_CARACTERE	{ $$ = new Tipo(_CHAR);	}
	;

subprogramas:
	subprograma
	| subprograma subprogramas
	;

subprograma:
	cabecalho_de_subprograma declaracoes comando_composto PONTOVIRG
	;

cabecalho_de_subprograma:
	FUNCAO IDENTIFICADOR argumentos DOISPONTO tipo_padrao PONTOVIRG
	| PROCEDIMENTO IDENTIFICADOR argumentos PONTOVIRG
	;

argumentos:
	| ABREPAR lista_de_parametros FECHAPAR
	;

lista_de_parametros:
	lista_de_identificadores DOISPONTO tipo
	| REFERENCIA lista_de_identificadores DOISPONTO tipo
	| lista_de_parametros PONTOVIRG lista_de_identificadores DOISPONTO tipo
	| lista_de_parametros PONTOVIRG REFERENCIA lista_de_identificadores DOISPONTO tipo
	;

comando_composto:
	INICIO lista_de_comandos FIM
	| INICIO FIM
	;

lista_de_comandos:
	comando PONTOVIRG {
		
		
		gerador->expressao($1);
		delete($1);
	}
	| lista_de_comandos comando PONTOVIRG {}
	;

comando:
	IDENTIFICADOR ATTRIB expressao {
		
			Simbolo* sim = table->getSimbolo($1);
			if (sim == NULL) {
				cout << "Variavel " << $1 << " nao declarada na linha: " << nlines << endl;
				YYABORT;
			} else {
				sim->setIni(true);
				table->atualiza(sim);
				
				////geracao de codigo
				//gerador->expressao($3);
				//string s = $1;
				//gerador->atribuicao(s);
			
				Exp e(":=",_ATRIBUICAO_);
				Exp f($1,_VARIAVEL_);
				
				$3->push_back(f);
				$3->push_back(e);
				$$ = $3;
				
				//$$ = new Comando($3,$1);
				//delete($3);
			}
	}
	| IDENTIFICADOR ABRECOLCH expressao FECHACOLCH ATTRIB expressao {}
	| IDENTIFICADOR ABRECOLCH expressao FECHACOLCH ATTRIB LITERAL {}
	| procedimento_ou_funcao {}
	| comando_condicional {}
	| comando_repeticao {}
	| comando_composto {}
	;

expressao:
	termo {
		$$ = $1;	
	}
	| expressao MAIS termo 	{
		$$ = $1;
		$$->splice($$->end(),*$3);
		Exp e("+",_MAIS_);
		$$->push_back(e);
//		$$->print();
	}
	| expressao MENOS termo {
		$$ = $1;
		$$->splice($$->end(),*$3);
		Exp e("-",_MENOS_);
		$$->push_back(e);
//		$$->print();
	}
	;

termo:
	fator {
		$$ = $1;
	}
	| termo DIVID fator	{
		$$ = $1;
		$$->splice($$->end(),*$3);
		Exp e("/",_DIVIDIR_);
		$$->push_back(e);
	}
	| termo VEZES fator	{ 
		$$ = $1;
		$$->splice($$->end(),*$3);
		Exp e("*",_VEZES_);
		$$->push_back(e);
	}
	| termo MOD fator {
		cout << "Operacao nao implementada: MOD, na linha: " << nlines << endl; YYABORT;
		$$ = $1;
		$$->splice($$->end(),*$3);
		Exp e("mod",_MOD_);
		$$->push_back(e);
	}
	| termo DIV fator {
		cout << "Operacao nao implementada: MOD, na linha: " << nlines << endl; YYABORT;
		$$ = $1;
		$$->splice($$->end(),*$3);
		Exp e("div",_DIV_);
		$$->push_back(e);
	}
	;

fator:
	IDENTIFICADOR {
		$$ = new Expressao();
		Exp e($1,_VARIAVEL_);
		$$->push_back(e);
	}
	| IDENTIFICADOR ABREPAR lista_de_expressoes FECHAPAR 	{ cout << "?" << endl;}
	| INTEIRO {
		$$ = new Expressao();
		Exp e($1,_INTEIRO_);
		$$->push_back(e);
	}
	| NUMERO {
		$$ = new Expressao();
		Exp e($1,NUMERO);
		$$->push_back(e);
	}
	| VERDADEIRO {
		$$ = new Expressao();
		Exp e("verdadeiro",VERDADEIRO);
		$$->push_back(e);
	}
	| FALSO	{
		$$ = new Expressao();
		Exp e("falso",FALSO);
		$$->push_back(e);
	}
	| ABREPAR expressao FECHAPAR {
		$$ = $2;
	}
	;
	
lista_de_expressoes:
	expressao
	| lista_de_expressoes VIRGULA expressao
	;

procedimento_ou_funcao:
	IDENTIFICADOR
	| IDENTIFICADOR ABREPAR lista_de_expressoes FECHAPAR
	;





comando_condicional:
	SE expressao_relacional ENTAO comando {

		//eu acho que nao eh <comando> e sim <lista_de_comandos> mais jah to com sono
		//acho q desse jeito soh pode uma linha dentro do then

//	if ( a > b ) then
//		bla
//		bla
//_______________________
//	@ini:					se
//______________________
//		cmp reg1,reg2		exp_relacional
// 		jmenor @fim 
//______________________
//			bla				comando
//			bla
//_______________________
//	@fim:					fim
		
		//gerador->se(label->getLabel(_IF_));
		gerador->se("if_ini");
		gerador->exp_relacional($2,"fim");

		gerador->expressao($4);
		gerador->fim("fim");

		delete($2);
		delete($4);
		
	}
	| SE expressao_relacional ENTAO comando SENAO comando {

//_______________________
//	@ini:					se
//______________________
//		cmp reg1,reg2		exp_relacional
// 		jmenor @else 
//______________________
//			bla				comando
//			bla
//______________________
//	@else:
//			ble
//			ble
//_______________________
//	@fim:					fim
		
		gerador->se("while");
		gerador->exp_relacional($2,"else");
		gerador->expressao($4);
		gerador->jmp("fim");
		gerador->se("else");
		gerador->expressao($6);
		gerador->fim("fim");

	}
	;

expressao_relacional:
	expressao OP_RELACIONAL expressao {}
	| expressao MAIOR expressao {

		//lembrete: o resultado da expressao tah na pilha
		//$$ = exp1 exp2 OP
		$$ = $1;
		$$->splice($$->end(),*$3);
		Exp e(">",_MAIOR_);
		$$->push_back(e);
//		$$->print();

	}
	| expressao_relacional OP_LOGICO expressao_relacional {}
	| NOT expressao_relacional {}
	;

comando_repeticao:
	REPITA comando ATE expressao_relacional {
	
//	while a > b do begin
//		bla
//		bla
//
//	@while:
//__________________________________	
//		cmp reg1,reg2
//		jmenor @fim
//__________________________________
//		bla
//		bla
//__________________________________
//		j @while
//__________________________________
//	@fim:

		//gerador->enquanto(label->getLabel("_WHILE_"));
		gerador->se("while");
		gerador->expressao($2);
		gerador->exp_relacional($4,"fim");
		gerador->jmp("while");
		gerador->fim("fim");
		table->print();
		delete($2);
		delete($4);
	}
	| ENQUANTO expressao_relacional FACA comando {

//	while a > b do begin
//		bla
//		bla

//	@while:
//__________________________________	
//		cmp reg1,reg2
//		jmenor @fim
//__________________________________
//		bla
//		bla
//__________________________________
//		j @while
//__________________________________
//	@fim:

		//gerador->enquanto(label->getLabel("_WHILE_"));
		gerador->se("while");
		gerador->exp_relacional($2,"fim");
		gerador->expressao($4);
		gerador->jmp("while");
		gerador->fim("fim");
		table->print();
		delete($2);
		delete($4);

	}
	| PARA IDENTIFICADOR ATTRIB expressao ATE expressao FACA comando
	;



%%


int main() {
	
	table = new TSimbolo();
	proc = new Processador();
	gerador = new Codigo();
	
	int ret = yyparse();
	table->print();


	delete(table);
	delete(proc);
	delete(gerador);

	return ret;
}
