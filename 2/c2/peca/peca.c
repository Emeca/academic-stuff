#include <stdio.h>
#include <dir.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

#define pgdown  81
#define pgup    73
#define left    75
#define up      72
#define down    80
#define enter   13
#define esc     27
#define t_um    49
#define t_c     99
#define t_dois  50
#define t_i    105
#define t_tres  51
#define t_s    115

typedef unsigned char uchar;

//===========================================================================
//DECLARACAO DE TIPOS PARA COMPOR A LISTA DUPLA
//===========================================================================
typedef char STRING[50];

typedef struct
{
	uchar d:5; // 5 bits
	uchar m:4; // 4
	uchar a:7; // 7
} TDATA;

typedef union
{
	int ff_fdate; // 16 bits na memoria
	TDATA data;   // os mesmos 16 bits
} UDATA;

/*
 *se eu acessar: data.ff_fdate estarei acessando 16 bits atravez de um int
 *               data.data.d estarei acessando os 5 bits de mais alta ordem
 */
typedef struct
{
	uchar s:5;
	uchar m:6;
	uchar h:5;
} THORA;

typedef union
{
	int ff_ftime;
	THORA hora;
} UHORA;

typedef struct
{
	char nome[13];
	UDATA data;
	UHORA hora;
	int tamanho;
	uchar atributo;
} TBOX;

typedef struct TNO
{
	struct TNO *ant;
	TBOX box;
	struct TNO *prox;
} TNO;

typedef struct TNO *PNO;

//==========================================================================
//Struct e Union para armazenar configuracoes e acessar Memoria de Video
//==========================================================================
typedef struct
{
	uchar letra:4;
	uchar fundo:3;
	uchar blink:1;
} S_COR;

typedef union
{
	uchar full;
	S_COR half;
} U_ATTR;

typedef struct
{
	U_ATTR ativo;
	U_ATTR inativo;
	U_ATTR menu_ativo;
	U_ATTR menu_inativo;
	uchar drive;
} CONFIG;

typedef struct
{
	char letra;
	U_ATTR atributo;
} S_TELA;

typedef S_TELA MTELA[25][80];
typedef MTELA far *PTELA;

//===========================================================================
CONFIG config;
char cfg_file[50];

PTELA
salva_tela()
{
	int i, j;
	PTELA tela_origem = (PTELA) MK_FP(0xB800, 0x0000);
	PTELA tela = (PTELA) malloc(sizeof(MTELA));
	for (i = 0; i < 25; i++)
		for (j = 0; j < 80; j++)
			(*tela)[i][j] = (*tela_origem)[i][j];
	return tela;
}

void
restaura_tela(PTELA tela)
{
	int i, j;
	PTELA tela_destino = (PTELA) MK_FP(0xB800, 0x0000);
	for (i = 0; i < 25; i++)
		for (j = 0; j < 80; j++)
			(*tela_destino)[i][j] = (*tela)[i][j];
	free(tela);
}

//================================================================interrupcoes

// obtem espaco total (Mega bytes) do disco usando interrupcao
float
irq_tam_drive(char drive)
{
	union REGS reg;
	reg.h.ah = 0x36;         // nro da rotina (servico) da interrupcao
	drive = drive - 'A' + 1; // drive fica com o nro equivalente do drive
	reg.h.dl = drive;        // numero que representa o drive 0=default, 1=A. 2=B, 3=C, etc
	int86(0x21, &reg, &reg); // gera interrupcao numero 0x21 (disk space)
	return ((reg.x.cx) * (reg.x.ax / 1024.0) * (reg.x.dx / 1024.0));
}

// obtem espaco livre no disco (Mega bytes) usando interrupcao
float
irq_espaco_livre(char drive)
{
	union REGS reg;
	reg.h.ah = 0x36;         // nro da rotina (servico) da interrupcao
	drive = drive - 'A' + 1; // drive fica com o nro equivalente do drive
	reg.h.dl = drive;        // numero que representa o drive 0=default, 1=A. 2=B, 3=C, etc
	int86(0x21, &reg, &reg); // gera interrupcao numero 0x21 (disk space)
	return ((reg.x.cx) * (reg.x.ax / 1024.0) * (reg.x.bx / 1024.0));
}

// obtem memoria total (Kilo bytes) do personal computer. OBS: memoria "vista" pelo DOS (convencional == 640K)
float
irq_mem_total()
{
	union REGS reg;
	int86(0x12, &reg, &reg); // gera interrupcao numero 0x12 (memory size)
	return (reg.x.ax);       // 'reg.x.ax' fica com memoria em Kbytes
}

//============================================================fim_interrupcoes
void
loadcfg()
{
	FILE *fp;
	if (!(fp = fopen(cfg_file, "rb"))) {
		config.ativo.full = 0;
		config.ativo.half.letra = BLACK;
		config.ativo.half.fundo = GREEN;
		config.inativo.full = 0;
		config.inativo.half.letra = GREEN;
		config.inativo.half.fundo = BLACK;
		config.menu_ativo.full = 0;
		config.menu_ativo.half.letra = LIGHTGRAY;
		config.menu_ativo.half.fundo = BLACK;
		config.menu_inativo.full = 0;
		config.menu_inativo.half.letra = BLACK;
		config.menu_inativo.half.fundo = LIGHTGRAY;
		config.drive = getdisk();
	}

	else
		fread(&config, sizeof(CONFIG), 1, fp);
	fclose(fp);
}

void
reccfg()
{
	FILE *fp;
	fp = fopen(cfg_file, "wb");
	fwrite(&config, sizeof(CONFIG), 1, fp);
	fclose(fp);
}

void
desaloca(PNO *H)
{
	if (*H) {
		while ((*H)->prox) {
			(*H) = (*H)->prox;
			free((*H)->ant);
		}
		free(*H);
		(*H) = NULL;
	}
}

void
ponha_no(PNO * H, PNO novo)
{
	PNO *aux;
	aux = &(*H);

	// enquanto cabeca da lista diferente de NULL <e> nome do no for menor <e> o prox diferente de NULL
	while ((*aux) && (strcmp((*aux)->box.nome, novo->box.nome) < 0)
		   && ((*aux)->prox))
		aux = &((*aux)->prox);
	if ((*aux) && (strcmp((*aux)->box.nome, novo->box.nome) < 0)) { // insere no final
		novo->prox = NULL;
		novo->ant = *aux;
		(*aux)->prox = novo;
	}

	else {
		if (*aux) {
			novo->ant = (*aux)->ant; //quando insere no meio
			(*aux)->ant = novo;
		}

		else
			novo->ant = NULL; // quando insere no inicio
		novo->prox = *aux; //completa a insersoa no inicio ou no meio
		*aux = novo;
	}
}

void
carrega(char *path, PNO *H)
{
	struct ffblk ffblk;
	findfirst(path, &ffblk, 0xFF);

	do {
		PNO novo = (TNO *) malloc(sizeof(TNO));
		strcpy(novo->box.nome, ffblk.ff_name);
		novo->box.data.ff_fdate = ffblk.ff_fdate;
		novo->box.hora.ff_ftime = ffblk.ff_ftime;
		novo->box.tamanho = ffblk.ff_fsize;
		novo->box.atributo = ffblk.ff_attrib;
		ponha_no(&(*H), novo);
	} while (!findnext(&ffblk));
	while ((*H)->ant)
		(*H) = (*H)->ant;
}

void
print_seila(int l_ini, int l_fim, int c_ini, int c_fim, int attr, int ap)
{
	int i, j;
	PTELA tela = (PTELA) MK_FP(0xB800, 0x0000);
	if (ap)
		for (i = l_ini; i < l_fim; i++)
			for (j = c_ini; j < c_fim; j++) {
				(*tela)[i][j].atributo.full = attr;
				(*tela)[i][j].letra = ' ';
			}
	else
		for (i = l_ini; i < l_fim; i++)
			for (j = c_ini; j < c_fim; j++)
				(*tela)[i][j].atributo.full = attr;
}

void
print_atributo(int l_ini, int l_fim, int c_ini, int c_fim, int attr, int ap)
{
	int i, j;
	PTELA tela = (PTELA) MK_FP(0xB800, 0x0000);
	switch (attr) {
	case 1:
		switch (ap) {
		case 1:{
				attr = config.inativo.full;
				for (i = l_ini; i < l_fim; i++)
					for (j = c_ini; j < c_fim; j++) {
						(*tela)[i][j].atributo.full = attr;
						(*tela)[i][j].letra = ' ';
					}
			};
			break;
		case 0:{
				attr = config.inativo.full;
				for (i = l_ini; i < l_fim; i++)
					for (j = c_ini; j < c_fim; j++)
						(*tela)[i][j].atributo.full = attr;
			};
			break;
		}
		break;
	case 0:
		switch (ap) {
		case 1:{
				attr = config.ativo.full;
				for (i = l_ini; i < l_fim; i++)
					for (j = c_ini; j < c_fim; j++) {
						(*tela)[i][j].atributo.full = attr;
						(*tela)[i][j].letra = ' ';
					}
			};
			break;
		case 0:{
				attr = config.ativo.full;
				for (i = l_ini; i < l_fim; i++)
					for (j = c_ini; j < c_fim; j++)
						(*tela)[i][j].atributo.full = attr;
			};
			break;
		}
		break;
	}
/*
 * attr == 1, atributo = inativo
 * attr == 0, atributo = ativo
 * ap   == 1, apaga
 * ap   == 0, naum apaga
 */
}

int
is_dir(int atributo)
{
	return ((atributo & 16) == 16);
}

void
print_xy(int x, int y, char *s)
{
	gotoxy(x, y + 1);
	printf("%s", s);
}

void
print_xy_f(int x, int y, char f)
{
	gotoxy(x, y + 1);
	printf("%f", f);
}

void
print_xy_int(int x, int y, int n)
{
	if (n < 10)
		x++;
	gotoxy(x, y + 1);
	printf("%i", n);
}

void
print_linha(PNO H, int linha)
{
	print_xy(1, linha, H->box.nome);
	print_xy(16, linha, "00/00/");
	print_xy_int(16, linha, H->box.data.data.d);
	print_xy_int(19, linha, H->box.data.data.m);
	print_xy_int(22, linha, H->box.data.data.a + 1980);
	print_xy(29, linha, "00:00:00");
	print_xy_int(29, linha, H->box.hora.hora.h);
	print_xy_int(32, linha, H->box.hora.hora.m);
	print_xy_int(35, linha, H->box.hora.hora.s * 2);
	gotoxy(40, linha + 1);
	printf("%u", H->box.tamanho);
	if (is_dir(H->box.atributo))
		print_xy(51, linha, "<dir>");
	print_xy_int(59, linha, H->box.atributo);
}

void
print_lista(PNO H, int ini, int fim)
{
	while ((ini < fim) && (H)) {
		print_linha(H, ini);
		H = H->prox;
		ini++;
	}
}

int
inc_tela(PNO * H, int ini, int fim)
{
	for (; ini < fim; ini++) { // retorna 1 se fungo
		if ((*H)->prox)        // retorna 0 se chego em null
			(*H) = (*H)->prox;

		else
			return 0;
	}
	return 1;
}

int
dec_tela(PNO * H, int ini, int fim)
{
	for (; ini < fim; ini++) {
		if ((*H)->ant)
			(*H) = (*H)->ant;

		else
			return 0;
	}
	return 1;
}

void
funcao_down(PNO *p_ini, // ponteiro p/ inicio da tela
			PNO *p_pos, // ponteiro p/ posicao do cursor
			PNO *p_fim, // ponteiro p/ fim da tela
			int ini,    // inicio da tela
			int *pos,   // posicao do cursor na tela
			int fim)    // fim da tela
{
	if ((*p_pos)->prox != (*p_fim)->prox) {
		print_atributo(*pos, *pos + 1, 0, 80, 1, 0);
		(*pos)++;
		(*p_pos) = (*p_pos)->prox;
		print_atributo((*pos), (*pos) + 1, 0, 80, 0, 0);
	} else if ((*p_fim)->prox) {
		(*p_ini) = (*p_ini)->prox;
		(*p_pos) = (*p_pos)->prox;
		(*p_fim) = (*p_fim)->prox;
		print_atributo(ini, fim, 0, 80, 1, 1);
		print_lista((*p_ini), ini, fim);
		print_atributo((*pos), (*pos) + 1, 0, 80, 0, 0);
	}
}

void
funcao_up(PNO * p_ini, PNO * p_pos, PNO * p_fim, int ini, int *pos, int fim)
{
	if ((*p_pos)->ant != (*p_ini)->ant) {
		print_atributo((*pos), (*pos) + 1, 0, 80, 1, 0);
		(*pos)--;
		(*p_pos) = (*p_pos)->ant;
		print_atributo((*pos), (*pos) + 1, 0, 80, 0, 0);
	} else if ((*p_ini)->ant) {
		(*p_ini) = (*p_ini)->ant;
		(*p_pos) = (*p_pos)->ant;
		(*p_fim) = (*p_fim)->ant;
		print_atributo(ini, fim, 0, 80, 1, 1);
		print_lista((*p_ini), ini, fim);
		print_atributo((*pos), (*pos) + 1, 0, 80, 0, 0);
	}
}

void
funcao_pgdown(PNO * p_ini, PNO * p_pos, PNO * p_fim, int ini, int *pos, int fim)
{
	PNO aux = (*p_fim);
	if (inc_tela(&aux, ini, fim - 1)) {
		(*p_ini) = (*p_fim);
		inc_tela(&(*p_pos), ini, fim - 1);
		inc_tela(&(*p_fim), ini, fim - 1);
	} else {
		(*p_ini) = aux;
		dec_tela(&(*p_ini), ini, fim - 1);
		(*p_pos) = (*p_ini);
		inc_tela(&(*p_pos), ini, (*pos));
		(*p_fim) = aux;
	}
	print_atributo(ini, fim, 0, 80, 1, 1);
	print_lista((*p_ini), ini, fim);
	print_atributo(*(pos), (*pos) + 1, 0, 80, 0, 0);
}

void
funcao_pgup(PNO * p_ini, PNO * p_pos, PNO * p_fim, int ini, int *pos, int fim)
{
	PNO aux = (*p_ini);
	if (dec_tela(&aux, ini, fim - 1)) {
		(*p_fim) = (*p_ini);
		dec_tela(&(*p_pos), ini, fim - 1);
		dec_tela(&(*p_ini), ini, fim - 1);
	} else {
		(*p_ini) = aux;
		(*p_fim) = aux;
		inc_tela(&(*p_fim), ini, fim - 1);
		(*p_pos) = (*p_ini);
		inc_tela(&(*p_pos), ini, (*pos));
	}
	print_atributo(ini, fim, 0, 80, 1, 1);
	print_lista((*p_ini), ini, fim);
	print_atributo(*(pos), (*pos) + 1, 0, 80, 0, 0);
}

void
path_apaga(char *path)
{
	int i = 0;
	while (*(path + i))
		i++;
	while (*(path + i) != '\\')
		*(path + i--) = '\x0';
	*(path + i) = '\x0';
}

void
print_path(char *path, int linha)
{
	linha--;
	print_atributo(linha, linha + 1, 0, 80, 0, 1);
	print_xy(1, linha, path);
}

void
print_coluna(int linha)
{
	linha--;
	linha--;
	print_atributo(linha, linha + 1, 0, 80, 1, 1);
	print_xy(1, linha, "::nome::");
	print_xy(16, linha, "::data::");
	print_xy(29, linha, "::hora::");
	print_xy(40, linha, "::tam::");
	print_xy(51, linha, "::atr::");
} void

print_rodape(int fim)
{
	int aux = 0;
	print_seila(fim, fim + 1, 0, 80, config.menu_inativo.full, 1);
	print_xy(1, fim,
			 "  <PageUp>[subir pagina] <PageDown>[descer pagina] <Up|Down>[rolar] <Enter>[chdir]");
	aux = (config.inativo.half.letra | config.menu_inativo.full);
	print_seila(fim, fim + 1, 2, 10, aux, 0);
	print_seila(fim, fim + 1, 25, 35, aux, 0);
	print_seila(fim, fim + 1, 51, 56, aux, 0);
	print_seila(fim, fim + 1, 64, 71, aux, 0);
}

void
print_menu(int ini)
{
	int aux;
	ini--;
	ini--;
	ini--;
	print_seila(ini, ini + 1, 0, 80, config.menu_inativo.full, 1);
	print_xy(1, ini, "[CoNfIgUrAcOeS]  [InFoRmAcOeS]  [SaIr]");
	aux = aux = (config.inativo.half.letra | config.menu_inativo.full);
	print_seila(ini, ini + 1, 1, 2, aux, 0);
	print_seila(ini, ini + 1, 18, 19, aux, 0);
	print_seila(ini, ini + 1, 33, 34, aux, 0);
}

void
print_tudo(char *path, int ini, int fim)
{
	print_coluna(ini);
	print_path(path, ini);
	print_rodape(fim);
	print_menu(ini);
}

void
print_dir(PNO * p_ini, char *path, int ini, int *pos, int fim)
{
	print_tudo(path, ini, fim);
	print_atributo(ini, fim, 0, 80, 1, 1);
	print_lista((*p_ini), ini, fim);
	print_atributo((*pos), (*pos) + 1, 0, 80, 0, 0);
}

void
init_dir(PNO * H, char *path, PNO * p_ini, PNO * p_pos, PNO * p_fim, int ini,
		 int *pos, int fim)
{
	desaloca(&(*H));
	carrega(path, &(*H));
	(*p_ini) = (*p_pos) = (*p_fim) = (*H);
	(*pos) = ini;
	inc_tela(&(*p_fim), ini, fim - 1);
	print_dir(p_ini, path, ini, pos, fim);
}

void
funcao_enter(PNO * H, char *path, PNO * p_ini, PNO * p_pos, PNO * p_fim,
			 int ini, int *pos, int fim)
{
	if (is_dir((*p_pos)->box.atributo)) {
		if (!(strcmp((*p_pos)->box.nome, ".."))) {
			path_apaga(path);
			path_apaga(path);
			strcat(path, "\\*.*");
		} else if ((strcmp((*p_pos)->box.nome, "."))) {
			path_apaga(path);
			strcat(path, "\\");
			strcat(path, (*p_pos)->box.nome);
			strcat(path, "\\*.*");
		}
		init_dir(H, path, p_ini, p_pos, p_fim, ini, pos, fim);
	}
}

void
seleciona_menu(int ini, int c_ini, int c_fim)
{
	ini--;
	ini--;
	print_seila(ini - 1, ini, c_ini, c_fim, config.menu_ativo.full, 0);
}

void
desenha_caixa(STRING * s, int n, int ini, int fim, int c_ini, int c_fim)
{
	int i = 0;
	char aux[50];
	print_seila(ini, fim + 1, c_ini, c_fim, config.menu_inativo.full, 1);
	ini++;
	c_ini++;
	c_ini++;
	for (i = 0; i < n; i++, ini++)
		print_xy(c_ini, ini, s[i]);
}

void
apaga_tela()
{
	int aux;
	aux = (config.inativo.full | BROWN);
	print_seila(0, 25, 0, 80, aux, 0);
}

int
funcao_menu(STRING * s, int n, int ini, int fim, int c_ini, int c_fim)
{
	int c = ' ';
	int pos_atual;
	int pos_ant;
	PTELA tela;
	desenha_caixa(s, n, ini - 2, fim, c_ini, c_fim);
	ini--;
	pos_atual = ini;
	pos_ant = pos_atual + 1;
	while (c != esc) {
		switch (c) {
		case up:{
				if (pos_atual > ini) {
					pos_ant = pos_atual;
					pos_atual--;
				}
			};
			break;
		case down:{
				if (pos_atual < fim - 1) {
					pos_ant = pos_atual;
					pos_atual++;
				}
			};
			break;
		case enter:
			return (pos_atual - ini + 1);
		}
		print_seila(pos_atual, pos_atual + 1, c_ini, c_fim,
					config.menu_ativo.full, 0);
		print_seila(pos_ant, pos_ant + 1, c_ini, c_fim,
					config.menu_inativo.full, 0);
		c = getch();
		if (c == 0)
			c = getch();
	}
	return 0;
}

int
get_cor()
{
	int aux;
	int linha, coluna;
	STRING s[8];
	strcpy(s[0], "preto");
	strcpy(s[1], "azul");
	strcpy(s[2], "verde");
	strcpy(s[3], "cyano");
	strcpy(s[4], "vermelho");
	strcpy(s[5], "magenta");
	strcpy(s[6], "marron");
	strcpy(s[7], "cinza");
	linha = random(7) + 10;
	coluna = random(80) + 11;
	return (funcao_menu(s, 8, linha, linha + 7, coluna, coluna + 11) - 1); // abremenu
}

void
conf(int c)
{
	if ((c >= 1) && (c <= 4)) {
		switch (c) {
		case 1:
			config.inativo.half.letra = get_cor();
			break;
		case 2:
			config.ativo.half.letra = get_cor();
			break;
		case 3:
			config.inativo.half.fundo = get_cor();
			break;
		case 4:
			config.ativo.half.fundo = get_cor();
			break;
		}
	}
}

void
funcao_conf(PNO * p_ini, char *path, int ini, int *pos, int fim)
{
	STRING s[4];
	PTELA tela;
	tela = salva_tela(); // salva janela
	strcpy(s[0], "letra normal");
	strcpy(s[1], "letra ativa");
	strcpy(s[2], "fundo normal");
	strcpy(s[3], "fundo ativo");
	apaga_tela();
	seleciona_menu(ini, 0, 15);
	conf(funcao_menu(s, 4, ini, 6, 0, 15)); // abremenu
	restaura_tela(tela); // restaura tel
	print_dir(p_ini, path, ini, pos, fim);
}

void
info(int c)
{
	int linha, coluna, comprimento;
	float f;
	char s[20];
	if ((c >= 1) && (c <= 5)) {
		switch (c) {
		case 1:{
				strcpy(s, "[tamanho do disco]");
				f = irq_tam_drive(3);
			};
			break;
		case 2:{
				strcpy(s, "[espaco livre]");
				f = irq_espaco_livre(3);
			}
			break;
		case 3:{
				strcpy(s, "[memoria total]");
				f = irq_mem_total(3);
			};
			break;
		case 4:
			strcpy(s, "[memoria utilizada]");
			break;
		case 5:
			strcpy(s, "[memoria livre]");
			break;
		}
		linha = random(7) + 10;
		comprimento = strlen(s) + 2;
		coluna = random(80) - 2 + comprimento;
		print_seila(linha, linha + 5, coluna, coluna + comprimento,
					config.menu_inativo.full, 1);
		print_xy(coluna + 2, linha + 1, "InFoRmAcAo:");
		print_xy(coluna + 2, linha + 2, s);
		print_xy_f(coluna + 2, linha + 3, f);
		c = getch();
		if (c == 0)
			c = getch();
	}
}

void
funcao_info(int ini)
{
	STRING s[5];
	PTELA tela;
	tela = salva_tela(); // salva janela
	strcpy(s[0], "tamanho do disco");
	strcpy(s[1], "espaco livre");
	strcpy(s[2], "memoria total");
	strcpy(s[3], "memoria utilizada");
	strcpy(s[4], "memoria livre");
	apaga_tela();
	seleciona_menu(ini, 17, 30);
	info(funcao_menu(s, 5, ini, 7, 17, 36)); // abremenu
	restaura_tela(tela); // restaura tel
}

void
funcao_sair(int ini, int *close)
{
	int c;
	STRING s[3];
	PTELA tela;
	tela = salva_tela(); // salva janela
	strcpy(s[0], "sair sem salvar");
	strcpy(s[1], "sair salvando");
	strcpy(s[2], "calcelar");
	apaga_tela();
	seleciona_menu(ini, 32, 38);
	c = funcao_menu(s, 3, ini, 5, 32, 49); //  abremenu
	switch (c) {
	case 2:{
			reccfg();
			(*close) = 1;
		};
		break;
	case 1:
		(*close) = 1;
		break;
	}
	restaura_tela(tela); // restaura tel
	print_xy_int(79, 0, c);
}

void
navega(PNO H)
{
	int ini = 3, fim = 24, pos = 3;
	int c = ' ';
	int close = 0;
	char path[256];
	PNO p_ini, p_pos, p_fim;
	p_pos = NULL;
	strcpy(path, "C:\\*.*");
	init_dir(&H, path, &p_ini, &p_pos, &p_fim, ini, &pos, fim);
	while (!close) {
		if (c != ' ') {
			c = getch();
			if (c == 0)
				c = getch();
		} else
			c = 0;
		switch (c) {
		case esc:
			funcao_sair(ini, &close);
			break;
		case up:
			funcao_up(&p_ini, &p_pos, &p_fim, ini, &pos, fim);
			break;
		case down:
			funcao_down(&p_ini, &p_pos, &p_fim, ini, &pos, fim);
			break;
		case pgup:
			funcao_pgup(&p_ini, &p_pos, &p_fim, ini, &pos, fim);
			break;
		case pgdown:
			funcao_pgdown(&p_ini, &p_pos, &p_fim, ini, &pos, fim);
			break;
		case enter:
			funcao_enter(&H, path, &p_ini, &p_pos, &p_fim, ini, &pos, fim);
			break;
		case t_um:
			funcao_conf(&p_ini, path, ini, &pos, fim);
			break;
		case t_c:
			funcao_conf(&p_ini, path, ini, &pos, fim);
			break;
		case t_dois:
			funcao_info(ini);
			break;
		case t_i:
			funcao_info(ini);
			break;
		case t_tres:
			funcao_sair(ini, &close);
			break;
		case t_s:
			funcao_sair(ini, &close);
			break;
		}
	}
	desaloca(&H);
}

int
main()
{
	PNO H = NULL;
	strcpy(cfg_file, "c:\\prog\\cfg.dat");
	loadcfg();
	system("cls");
	navega(H);
	system("cls");
	return 0;
}
