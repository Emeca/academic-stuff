#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define VERMELHO 1
#define AZUL 2
#define VERDE 3
#define ROSA 4
#define CINZA 5

#define MEXICANO 1
#define PERUANO 2
#define ARGENTINO 3
#define CHILENO 4
#define BRASILEIRO 5

#define CACHORRO 1
#define GATO 2
#define COELHO 3
#define VACA 4
#define CAVALO 5

#define MERCEDES 1
#define VOLKSWAGEM 2
#define CHEVROLET 3
#define FORD 4
#define FIAT 5

#define COCA_COLA 1
#define CAFE 2
#define WHISKY 3
#define CERVEJA	4
#define PEPSI 5

#define N801 0
#define N803 1
#define N805 2
#define N807 3
#define N809 4

#define COR 0
#define NACIONALIDADE 1
#define ANIMAL 2
#define VEICULO 3
#define BEBIDA 4

#define TAM 5
#define TRUE 1
#define FALSE 0

#define FIXO 1
#define N_FIXO 0

int **
matriz_aloca()
{
	int **m = (int **) malloc(sizeof(int *) * TAM);
	int i, j;
	for (i = 0; i < TAM; i++) {
		m[i] = (int *)malloc(sizeof(int) * TAM);
		for (j = 0; j < TAM; j++) {
			m[i][j] = -1;
		}
	}
	return m;
}

void
matriz_desaloca(int **m)
{
	 int i;
	for (i = 0; i < TAM; i++) {
		free(m[i]);
	}

	free(m);
	m = NULL;
}

int
myrandom()
{
	 int nrand = (int)(5.0 * rand() / (RAND_MAX + 1.0));

	return nrand;
}

void
print_vetor(int *v, int tam)
{
	int i;
	for (i = 0; i < tam; i++) {
		 printf("%i ", v[i]);
	}
	printf("\n");
}

void
print_coluna_um(int col)
{
	 switch (col) {
	 case COR:
		printf("COR \r\t\t");
		break;
	case NACIONALIDADE:
		printf("NACIONALIDADE \r\t\t");
		break;
	case ANIMAL:
		printf("ANIMAL \r\t\t");
		break;
	case VEICULO:
		printf("VEICULO \r\t\t");
		break;
	case BEBIDA:
		printf("BEBIDA \r\t\t");
		break;
	}
}

void
print_titulo_linha(int lin)
{
	switch (lin) {
	case N801:
		printf("\n\r\t\t801  ");
		break;
	case N803:
		printf("  803  ");
		break;
	case N805:
		printf("  805  ");
		break;
	case N807:
		printf("  807  ");
		break;
	case N809:
		printf("  809  ");
		break;
	 }
}

char
get_attr(int **m, int i, int j)
{
	switch (i) {
	case COR: {
		if (m[i][j] == VERMELHO)
			return 'V';
		else if (m[i][j] == AZUL)
			return 'A';
		else if (m[i][j] == VERDE)
			return 'E';
		else if (m[i][j] == ROSA)
			return 'R';
		else if (m[i][j] == CINZA)
			return 'C';
	}

	case NACIONALIDADE: {
		if (m[i][j] == MEXICANO)
			return 'M';
		else if (m[i][j] == PERUANO)
			return 'P';
		else if (m[i][j] == ARGENTINO)
			return 'A';
		else if (m[i][j] == CHILENO)
			return 'C';
		else if (m[i][j] == BRASILEIRO)
			return 'B';
	}

	case ANIMAL: {
		if (m[i][j] == CACHORRO)
			return 'D';
		else if (m[i][j] == GATO)
			return 'G';
		else if (m[i][j] == COELHO)
			return 'R';
		else if (m[i][j] == VACA)
			return 'V';
		else if (m[i][j] == CAVALO)
			return 'H';
	}

	case VEICULO: {
		if (m[i][j] == MERCEDES)
			return 'M';
		else if (m[i][j] == VOLKSWAGEM)
			return 'V';
		else if (m[i][j] == CHEVROLET)
			return 'C';
		else if (m[i][j] == FORD)
			return 'F';
		else if (m[i][j] == FIAT)
			return 'I';
	}

	case BEBIDA: {
		if (m[i][j] == COCA_COLA)
			return 'O';
		else if (m[i][j] == CAFE)
			return 'C';
		else if (m[i][j] == WHISKY)
			return 'W';
		else if (m[i][j] == CERVEJA)
			return 'B';
		else if (m[i][j] == PEPSI)
			return 'P';
	}
	}

	return '.';
}

void
print_matriz(int **m, int **mf)
{
	int i, j;
	for (j = 0; j < TAM; j++) {
		print_titulo_linha(j);
	}
	printf("    matriz");
	printf("     acertos\n");
	for (i = 0; i < TAM; i++) {
		print_coluna_um(i);
		for (j = 0; j < TAM; j++) {
			if (mf[i][j] == FIXO) {
				printf(" %c     ", get_attr(m, i, j));
			} else {
				printf(" %c     ", '.');
			}
		}
		for (j = 0; j < TAM; j++) {
			if (m[i][j] == -1) {
				printf("%c ", '.');
			} else {
				printf("%i ", m[i][j]);
			}
		}
		printf("  ");
		for (j = 0; j < TAM; j++) {
			if (mf[i][j] == -1) {
				printf("%c ", '.');
			} else {
				printf("%i ", mf[i][j]);
			}
		}
		printf("\n");
	}
}

int **
matriz_copy(int **m)
{
	 int **n = matriz_aloca();
	int i, j;
	for (i = 0; i < TAM; i++) {
		for (j = 0; j < TAM; j++) {
			n[i][j] = m[i][j];
		}
	}
	return n;
}

/* mexicano mora na casa vermelha */
int
um(int **m, int **mf)
{
	int j;
	for (j = 0; j < TAM; j++) {
		if ((m[NACIONALIDADE][j] == MEXICANO) && (m[COR][j] == VERMELHO)) {
			mf[NACIONALIDADE][j] = FIXO;
			mf[COR][j] = FIXO;
			printf("* mexicano mora na casa vermelha\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* peruano tem um carro mercedez benz */
int
dois(int **m, int **mf)
{
	int j;
	for (j = 0; j < TAM; j++) {
		if ((m[NACIONALIDADE][j] == PERUANO) && (m[VEICULO][j] == MERCEDES)) {
			mf[NACIONALIDADE][j] = FIXO;
			mf[VEICULO][j] = FIXO;
			printf("* peruano tem um carro mercedez benz\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* argentino possui cachorro */
int
tres(int **m, int **mf)
{
	int j;
	for (j = 0; j < TAM; j++) {
		if ((m[NACIONALIDADE][j] == ARGENTINO) && (m[ANIMAL][j] == CACHORRO)) {
			mf[NACIONALIDADE][j] = FIXO;
			mf[ANIMAL][j] = FIXO;
			printf("* argentino possui cachorro\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* chileno bebe coca-cola */
int
quatro(int **m, int **mf)
{
	int j;
	for (j = 0; j < TAM; j++) {
		if ((m[NACIONALIDADE][j] == CHILENO) && (m[BEBIDA][j] == COCA_COLA)) {
			mf[NACIONALIDADE][j] = FIXO;
			mf[BEBIDA][j] = FIXO;
			printf("* chileno bebe coca-cola\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* na casa verde bebe wisky */
int
cinco(int **m, int **mf)
{
	int j;
	for (j = 0; j < TAM; j++) {
		if ((m[COR][j] == VERDE) && (m[BEBIDA][j] == WHISKY)) {
			mf[COR][j] = FIXO;
			mf[BEBIDA][j] = FIXO;
			printf("* na casa verde bebe wisky\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* dono do volkswagen cria coelho */
int
seis(int **m, int **mf)
{
	int j;
	for (j = 0; j < TAM; j++) {
		if ((m[VEICULO][j] == VOLKSWAGEM) && (m[ANIMAL][j] == COELHO)) {
			mf[VEICULO][j] = FIXO;
			mf[ANIMAL][j] = FIXO;
			printf("* dono do volkswagen cria coelho\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* o dono chevrolet mora na casa rosa */
int
sete(int **m, int **mf)
{
	int j;
	for (j = 0; j < TAM; j++) {
		if ((m[VEICULO][j] == CHEVROLET) && (m[COR][j] == ROSA)) {
			mf[VEICULO][j] = FIXO;
			mf[COR][j] = FIXO;
			printf("* o dono chevrolet mora na casa rosa\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* na casa 3 bebe pepsi */
int
oito(int **m, int **mf)
{
	if (m[BEBIDA][N805] == PEPSI) {
		mf[BEBIDA][N805] = FIXO;
		printf("* na casa 3 bebe pepsi\n");
		return TRUE;
	}
	return FALSE;
}

/* o dono do ford bebe cerveja */
int
nove(int **m, int **mf)
{
	int j;
	for (j = 0; j < TAM; j++) {
		if ((m[VEICULO][j] == CHEVROLET) && (m[COR][j] == ROSA)) {
			mf[VEICULO][j] = FIXO;
			mf[COR][j] = FIXO;
			printf("* o dono do ford bebe cerveja\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* o dono do gato bebe cafe, e nao mora na casa azul */
int
dez(int **m, int **mf)
{
	int j;
	for (j = 0; j < TAM; j++) {
		if ((m[ANIMAL][j] == GATO) && (m[BEBIDA][j] == CAFE)) {
			 if (m[COR][j] != AZUL) {
				 mf[ANIMAL][j] = FIXO;
				mf[BEBIDA][j] = FIXO;
				printf
					("* o dono do gato bebe cafe, e nao mora na casa azul\n");
				return TRUE;
			}
		}
	}
	return FALSE;
}

/* casa verde eh vizinha da casa direita cinza */
int
onze(int **m, int **mf)
{
	int j;
	for (j = 0; j < (TAM - 1); j++) {
		 if ((m[COR][j] == VERDE) && (m[COR][j + 1] == CINZA)) {
			mf[COR][j] = TRUE;
			mf[COR][j + 1] = TRUE;
			printf("* casa verde eh vizinha da casa direita cinza\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* a vaca eh vizinha da casa onde se bebe coca-cola? */
int
doze(int **m, int **mf)
{
	int j;
	if ((m[ANIMAL][0] == VACA) && (m[BEBIDA][1] == COCA_COLA)) {
		mf[ANIMAL][0] = FIXO;
		mf[BEBIDA][1] = FIXO;
		printf("* a vaca eh vizinha da casa onde se bebe coca-cola 1\n");
		return TRUE;
	}
	if ((m[ANIMAL][TAM] == VACA) && (m[BEBIDA][TAM - 1] == COCA_COLA)) {
		mf[ANIMAL][TAM] = FIXO;
		mf[BEBIDA][TAM - 1] = FIXO;
		printf("* a vaca eh vizinha da casa onde se bebe coca-cola 2\n");
		return TRUE;
	}
	for (j = 1; j < (TAM - 1); j++) {
		 if ((m[ANIMAL][j] == VACA) && (m[BEBIDA][j - 1] == COCA_COLA)) {
			mf[ANIMAL][j] = FIXO;
			mf[BEBIDA][j - 1] = FIXO;
			printf("* a vaca eh vizinha da casa onde se bebe coca-cola 3\n");
			return TRUE;
		}
		if ((m[ANIMAL][j] == VACA) && (m[BEBIDA][j + 1] == COCA_COLA)) {
			mf[ANIMAL][j] = FIXO;
			mf[BEBIDA][j + 1] = FIXO;
			printf("* a vaca eh vizinha da casa onde se bebe coca-cola 4\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* o peruano e o argentino sao vizinhos */
int
treze(int **m, int **mf)
{
	int j;
	if ((m[NACIONALIDADE][0] == PERUANO) &&
		(m[NACIONALIDADE][1] == ARGENTINO)) {

		mf[NACIONALIDADE][0] = FIXO;
		mf[NACIONALIDADE][1] = FIXO;
		printf("* o peruano e o argentino sao vizinhos\n");
		return TRUE;
	}
	if ((m[NACIONALIDADE][TAM] == PERUANO)
		 && (m[NACIONALIDADE][TAM - 1] == ARGENTINO)) {
		mf[NACIONALIDADE][TAM] = FIXO;
		mf[NACIONALIDADE][TAM - 1] = FIXO;
		printf("* o peruano e o argentino sao vizinhos\n");
		return TRUE;
	}
	for (j = 1; j < (TAM - 1); j++) {
		if (((m[NACIONALIDADE][j] == PERUANO)
				&& (m[NACIONALIDADE][j - 1] == ARGENTINO))) {
			mf[NACIONALIDADE][j] = FIXO;
			mf[NACIONALIDADE][j - 1] = FIXO;
			printf("* o peruano e o argentino sao vizinhos\n");
			return TRUE;
		}
		if (((m[NACIONALIDADE][j] == PERUANO) &&
			(m[NACIONALIDADE][j + 1] == ARGENTINO))) {

			mf[NACIONALIDADE][j] = FIXO;
			mf[NACIONALIDADE][j + 1] = FIXO;
			printf("* o peruano e o argentino sao vizinhos\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* brasileiro eh vizinho da casa azul */
int
quatorze(int **m, int **mf)
{
	int j;
	if ((m[NACIONALIDADE][0] == BRASILEIRO) && (m[COR][1] == AZUL)) {
		mf[NACIONALIDADE][0] = FIXO;
		mf[COR][1] = FIXO;
		printf("* o brasileiro eh vizinho da casa azul\n");
		return TRUE;
	}
	if ((m[NACIONALIDADE][TAM] == BRASILEIRO) && (m[COR][TAM - 1] == AZUL)) {
		mf[NACIONALIDADE][TAM] = FIXO;
		mf[NACIONALIDADE][TAM - 1] = FIXO;
		printf("* o brasileiro eh vizinho da casa azul\n");
		return TRUE;
	}
	for (j = 1; j < (TAM - 1); j++) {
		if ((m[NACIONALIDADE][j] == BRASILEIRO) && (m[COR][j - 1] == AZUL)) {
			mf[NACIONALIDADE][j] = FIXO;
			mf[COR][j - 1] = FIXO;
			printf("* o brasileiro eh vizinho da casa azul\n");
			return TRUE;
		}
		if ((m[NACIONALIDADE][j] == BRASILEIRO) && (m[COR][j + 1] == AZUL)) {
			mf[NACIONALIDADE][j] = FIXO;
			mf[COR][j + 1] = FIXO;
			printf("* o brasileiro eh vizinho da casa azul\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* a vaca eh vizinho do fiat */
int
quinze(int **m, int **mf)
{
	int j;
	if ((m[ANIMAL][0] == VACA) && (m[VEICULO][1] == FIAT)) {
		mf[ANIMAL][0] = TRUE;
		mf[VEICULO][1] = TRUE;
		printf("* a vaca eh vizinho do fiat 1\n");
		return TRUE;
	}
	if ((m[ANIMAL][TAM] == VACA) && (m[VEICULO][TAM - 1] == FIAT)) {
		mf[ANIMAL][TAM] = TRUE;
		mf[VEICULO][TAM - 1] = TRUE;
		printf("* a vaca eh vizinho do fiat 2\n");
		return TRUE;
	}
	for (j = 1; j < (TAM - 1); j++) {
		 if ((m[ANIMAL][j] == VACA) && (m[VEICULO][j - 1] == FIAT)) {
			mf[ANIMAL][j] = FIXO;
			mf[VEICULO][j - 1] = FIXO;
			printf("* a vaca eh vizinho do fiat 3\n");
			return TRUE;
		}
		if ((m[ANIMAL][j] == VACA) && (m[VEICULO][j + 1] == FIAT)) {
			mf[ANIMAL][j] = FIXO;
			mf[VEICULO][j + 1] = FIXO;
			printf("* a vaca eh vizinho do fiat 4\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* chevrolet eh vizinho do cavalo */
int
dezesseis(int **m, int **mf)
{
	int j;
	if ((m[VEICULO][0] == CHEVROLET) && (m[ANIMAL][1] == CAVALO)) {
		mf[VEICULO][0] = TRUE;
		mf[ANIMAL][1] = TRUE;
		printf("* o chevrolet eh vizinho do cavalo\n");
		return TRUE;
	}
	if ((m[VEICULO][TAM] == CHEVROLET) && (m[ANIMAL][TAM - 1] == CAVALO)) {
		mf[VEICULO][TAM] = TRUE;
		mf[ANIMAL][TAM - 1] = TRUE;
		printf("* o chevrolet eh vizinho do cavalo\n");
		return TRUE;
	}
	for (j = 1; j < (TAM - 1); j++) {
		if ((m[VEICULO][j] == CHEVROLET) && (m[ANIMAL][j - 1] == CAVALO)) {
			mf[VEICULO][j] = TRUE;
			mf[ANIMAL][j - 1] = TRUE;
			printf("* o chevrolet eh vizinho do cavalo\n");
			return TRUE;
		}
		if ((m[VEICULO][j] == CHEVROLET) && (m[ANIMAL][j + 1] == CAVALO)) {
			mf[VEICULO][j] = TRUE;
			mf[ANIMAL][j + 1] = TRUE;
			printf("* o chevrolet eh vizinho do cavalo\n");
			return TRUE;
		}
	}
	return FALSE;
}

/* os coelhos estao a mesma distancia do fiat e da cerveja */
int
dezessete(int **m, int **mf)
{
	int j, ja, jb;
	for (j = 0; j < TAM; j++) {
		for (ja = 0; ja < TAM; ja++) {
			if ((m[ANIMAL][j] == COELHO) &&
				((m[VEICULO][ja] == FIAT) && (m[BEBIDA][ja] == CERVEJA))) {

				mf[ANIMAL][j] = FIXO;
				mf[VEICULO][ja] = FIXO;
				mf[BEBIDA][ja] = FIXO;
				printf ("* os coelhos estao a mesma distancia do fiat e da cerveja\n");
				return TRUE;
			}
		}
		ja = jb = 0;
		while (ja >= 0 && jb < TAM) {
			if ((m[ANIMAL][j] == COELHO) && ((m[VEICULO][ja] == FIAT) &&
				(m[BEBIDA][jb] == CERVEJA))) {

				mf[ANIMAL][j] = FIXO;
				mf[VEICULO][ja] = FIXO;
				mf[BEBIDA][jb] = FIXO;
				printf ("* os coelhos estao a mesma distancia do fiat e da cerveja\n");
				return TRUE;
			}
			ja--;
			jb++;
		}
		ja = jb = 0;
		while (jb >= 0 && ja < TAM) {
			if ((m[ANIMAL][j] == COELHO) && ((m[VEICULO][ja] == FIAT) &&
				(m[BEBIDA][jb] == CERVEJA))) {

				mf[ANIMAL][j] = FIXO;
				mf[VEICULO][ja] = FIXO;
				mf[BEBIDA][jb] = FIXO;
				printf ("* os coelhos estao a mesma distancia do fiat e da cerveja\n");
				return TRUE;
			}
			ja++;
			jb--;
		}
	}
	return FALSE;
}

/* verifica tudo */
int
verifica(int **m, int **mf)
{
	int r = 0;

	r += um(m, mf) + dois(m, mf) + tres(m, mf) + quatro(m, mf) + cinco(m, mf);
	r += seis(m, mf) + sete(m, mf) + oito(m, mf) + nove(m, mf)  + dez(m, mf);
	r += onze(m, mf) + doze(m, mf) + treze(m, mf) + quatorze(m, mf);
	r += quinze(m, mf) + dezesseis(m, mf) + dezessete(m, mf);

	return r;
}

void
matriz_clear(int **m)
{
	int i, j;
	for (i = 0; i < TAM; i++) {
		for (j = 0; j < TAM; j++) {
			m[i][j] = -1;
		}
	}
}

int
esta_em_linha(int *v, int n)
{
	int j;
	for (j = 0; j < TAM; j++) {
		 if (v[j] == n)
			return TRUE;
	}
	return FALSE;
}

void
matriz_randomize(int **m)
{
	int i, j;
	int nrand;
	for (i = 0; i < TAM; i++) {
		for (j = 0; j < TAM; j++) {
			 nrand = myrandom();
			while (esta_em_linha(m[i], nrand))
				nrand = myrandom();
			m[i][j] = nrand;
		}
	}
}

void
matriz_chaqualha(int **m, int **mf)
{
	int i, j, nrand;
	for (i = 0; i < TAM; i++) {
		for (j = 0; j < TAM; j++) {
			if (mf[i][j] != FIXO) {
				m[i][j] = -1;
			 }
		}
		for (j = 0; j < TAM; j++) {
			if (mf[i][j] != FIXO) {
				nrand = myrandom();
				while (esta_em_linha(m[i], nrand)) {
					nrand = myrandom();
					
				}
				m[i][j] = nrand;
			 }
		}
	}
}

void
atualiza_bcount(int *b, int acertos)
{
	int i;
	for (i = 1; i < 10; i++) {
		 b[i - 1] = b[i];
	}
	b[i - 1] = acertos;
}

void
inicializa_bcount(int *b)
{
	int i;
	for (i = 0; i < 10; i++) {
		 b[i] = 0;
	}
}

void
print(int **m, int **mf, int acertos)
{
	print_matriz(m, mf);
	printf("[acertos] %i\n\n", acertos);
	printf ("==============================================================\n");
}

void
reset(int **m, int **mf)
{
	int um, dois;
	int i;
	int aux;
	matriz_clear(mf);
	for (i = 0; i < TAM; i++) {
		um = myrandom();
		dois = myrandom();
		aux = m[i][um];
		m[i][um] = m[i][dois];
		m[i][dois] = m[i][aux];
	}
	verifica(m, mf);
	printf("\nRESET\n\n");

	matriz_clear(mf);
	matriz_clear(m);
	matriz_randomize(m);
}

int
main()
{
	int **m = matriz_aloca();
	int **mf = matriz_aloca();
	int count = 0;
	int bcount[10];
	int reinicio = 0;
	int acertos = 0;

	inicializa_bcount(bcount);
	srandom(time(NULL));
	matriz_randomize(m);

	print(m, mf, acertos);
	while ((acertos = verifica(m, mf)) != 17) {
		print(m, mf, acertos);
		matriz_chaqualha(m, mf);
		count++;
		atualiza_bcount(bcount, acertos);
		if (bcount[0] == bcount[9]) {
			reset(m, mf);
			inicializa_bcount(bcount);
			count = 0;
			reinicio++;
		}
	}

	print_matriz(m, mf);
	printf("reinicios: %i", reinicio);
	printf("iteracoes: %i", count);
	matriz_desaloca(m);
	matriz_desaloca(mf);
	return count;
}
