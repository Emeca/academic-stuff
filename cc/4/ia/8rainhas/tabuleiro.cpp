#include "tabuleiro.hpp"

int
Matriz::busca_linha(int lin, int col)
{
	int i, acm = 0;
	for (i = lin + 1; i < LINHAS; i++)
		if (m[i][col] == TEM)
			acm++;

	for (i = lin - 1; i >= 0; i--)
		if (m[i][col] == TEM)
			acm++;

	return acm;
}

int
Matriz::busca_coluna(int lin, int col)
{
	int i, acm = 0;
	for (i = col + 1; i < COLUNAS; i++)
		if (m[lin][i] == TEM)
			acm++;

	for (i = col - 1; i >= 0; i--)
		if (m[lin][i] == TEM)
			acm++;

	return acm;
}

int
Matriz::busca_diagonal(int lin, int col)
{
	int i = lin - 1;
	int j = col - 1;
	int acm = 0;
	while ((i >= 0) && (j >= 0))
		if (m[i--][j--] == TEM)
			acm++;

	i = lin + 1;
	j = col + 1;
	while ((i < LINHAS) && (j < COLUNAS))
		if (m[i++][j++] == TEM)
			acm++;

	i = lin - 1;
	j = col + 1;
	while ((i >= 0) && (j < COLUNAS))
		if (m[i--][j++] == TEM)
			acm++;

	i = lin + 1;
	j = col - 1;
	while ((i < LINHAS) && (j >= 0))
		if (m[i++][j--] == TEM)
			acm++;

	return acm;
}

int
Matriz::come_ou_nao(int lin, int col)
{
	return (busca_linha(lin, col) + busca_coluna(lin, col) +
			busca_diagonal(lin, col));
}

int
Matriz::tromba()
{
	int i, j, acm = 0;
	for (i = 0; i < LINHAS; i++)
		for (j = 0; j < COLUNAS; j++)
			if (this->m[i][j] == TEM)
				acm += come_ou_nao(i, j);
	return acm;
}

void
Matriz::set(int lin, int col, int value)
{
	m[lin][col] = value;
}

int
Matriz::get_h()
{
	return h;
}

void
Matriz::calc_h()
{
	h = tromba();
}

int
Matriz::get_pos_rainha(int lin)
{
	int i;
	for (i = 0; i < COLUNAS - 1; i++) {
		if (m[lin][i] == TEM)
			return i;
	}
	return i;
}

void
Matriz::imprime_matriz()
{
	int i, j;

	for (i = 0; i < LINHAS; i++) {
		printf("---------------------------------\n");
		for (j = 0; j < COLUNAS; j++) {
			if (m[i][j] == 1) {

				printf("| %s%c%s ", VERMELHO, '#', NEUTRO);

			} else {
				printf("|   ");
			}
		}
		printf("|");
		printf(" %s[%i]%s\n", AZUL, h, NEUTRO);

	}
	printf("---------------------------------\n");
}

int **
Matriz::matriz_copy()
{
	int i, j;
	int **n = aloca_matriz();

	for (i = 0; i < LINHAS; i++) {
		for (j = 0; j < COLUNAS; j++) {
			n[i][j] = this->m[i][j];
		}
	}
	return n;
}

int **
Matriz::aloca_matriz(void)
{
	int i, j;
	int **m = (int **)malloc(sizeof(int *) * LINHAS);
	for (i = 0; i < LINHAS; i++) {
		m[i] = (int *)malloc(sizeof(int) * COLUNAS);
		for (j = 0; j < COLUNAS; j++) {
			m[i][j] = 0;
		}
	}
	return m;
}

void
Matriz::desaloca_matriz(int lin)
{
	int i;
	for (i = 0; i < lin; i++) {
		free(m[i]);
	}
	free(m);
}

Matriz::Matriz()
{
	h = -1;
	m = aloca_matriz();
}

Matriz::Matriz(Matriz * m)
{
	h = -1;
	this->m = m->matriz_copy();
}

int *
myrandom(int n)
{
	int *v = (int *) malloc(sizeof(int) * n);

	srandom(time(NULL));
	for (int i = 0; i < n; i++) {
		v[i] = (int) random() / 280000000;
	}
	return v;
}

Matriz::Matriz(int flag)
{
	h = -1;
	m = aloca_matriz();
	if (flag == RANDOM) {

		int *v = myrandom(LINHAS);
		m[0][v[0]] = 1;
		m[1][v[1]] = 1;
		m[2][v[2]] = 1;
		m[3][v[3]] = 1;
		m[4][v[4]] = 1;
		m[5][v[5]] = 1;
		m[6][v[6]] = 1;
		m[7][v[7]] = 1;
	}
}

Matriz::~Matriz()
{
	desaloca_matriz(LINHAS);
}
