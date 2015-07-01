#include "matrix.hh"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Vector::Vector(int tam)
{
	this->v = (int *)malloc(sizeof(int) * tam);
	this->tam = tam;
}

int
Vector::get(int i)
{
	if (this->v)
		return this->v[i];
	return 0;
}

int
Vector::getMeio()
{
	if (this->v) {
		int pos = (int)floor(tam / 2);
		return this->v[pos];
	}
	return 0;
}

void
Vector::matrix2vector(int i, int j, int n, Matrix * m)
{
	if (this->v) {
		int k = 0;
		int ifim = i + n;
		int jfim = j + n;
		for (; i < ifim; i++) {
			for (; j < jfim; j++) {
				this->v[k] = m->get(i, j);
				k++;
			}
		}
	}
}

void
Vector::print()
{
	if (this->v) {
		for (int i = 0; i < this->tam; i++) {
			printf("%i ", this->v[i]);
		}
		printf("\n");
	}
}

int
Vector::get_pos_menor(int ini)
{
	if (this->v) {
		int pos = ini;
		int menor = v[ini];

		for (int i = ini + 1; i < this->tam; i++) {

			if (this->v[i] < (int)menor) {
				menor = this->v[i];
				pos = i;
			}
		}
		return pos;
	}
	return 0;
}

void
Vector::selection()
{
	if (this->v) {
		int pos, temp;
		for (int i = 0; i < this->tam - 1; i++) {

			pos = this->get_pos_menor(i);
			//troca
			temp = this->v[i];
			this->v[i] = this->v[pos];
			this->v[pos] = temp;
		}
	}
}

Vector::~Vector()
{

	if (this->v)
		free(this->v);
	this->v = NULL;
}

Matrix::Matrix()
{
	printf("Matrix: constructor vaziu\n");
}

Matrix::Matrix(int linhas, int colunas)
{
	printf("Matrix: constructor\n");
	//alocando vetor de ponteiros pra vetor de int
	this->m = (int **)malloc(sizeof(int *) * linhas);
	for (int i = 0; i < linhas; i++) {
		//alocando vetor de int
		this->m[i] = (int *)malloc(sizeof(int) * colunas);
		for (int j = 0; j < colunas; j++) {

			this->m[i][j] = 0;

		}
	}
	this->linhas = linhas;
	this->colunas = colunas;
}

Matrix *
Matrix::cpy()
{
	Matrix *copia = new Matrix(this->linhas, this->colunas);
	for (int i = 0; i < this->linhas; i++) {
		for (int j = 0; j < this->colunas; j++) {

			copia->set(i, j, this->m[i][j]);
		}
	}
	return copia;
}

int
Matrix::getLinhas()
{

	return this->linhas;
}

int
Matrix::getColunas()
{

	return this->colunas;
}

void
Matrix::set(int i, int j, int cor)
{
	if ((i < linhas) && (j < colunas)) {
		this->m[i][j] = cor;
	} else {
		printf("\ntentativa de estrapolar as dimencoes da matrix: %i,%i\n\n", i,
			   j);
		this->print();
		exit(1);
	}
}

int
Matrix::toCinza(int red, int green, int blue)
{
	int i = (int)(floor(0.299 * red + 0.587 * green + 0.114 * blue));
	return (int)(i & 0xFF);
}

void
Matrix::set(int i, int j, int red, int green, int blue)
{
	this->m[i][j] = this->toCinza(red, green, blue);
}

void
Matrix::print()
{
	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {

			printf("%i ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int
Matrix::get(int i, int j)
{

	if ((i >= 0) && (j >= 0) && (i < linhas) && (j < colunas)) {
		return this->m[i][j];
	} else {
		printf("\ntentativa de estrapolar as dimencoes da matrix: %i,%i\n\n", i,
			   j);
//      this->print();
		exit(1);
	}
}

Matrix::~Matrix()
{
	printf("Matrix: destructor");
	for (int i = 0; i < this->linhas; i++) {
		if (this->m[i])
			free(this->m[i]);
	}
	if (this->m)
		free(this->m);
}

//==========[matriz de float]===============
fMatrix::fMatrix()
{
	printf("fMatrix: constructor vaziu\n");
}

fMatrix::fMatrix(int linhas, int colunas)
{
	printf("fMatrix: constructor\n");
	//alocando vetor de ponteiros pra vetor de int
	this->m = (float **)malloc(sizeof(float *) * linhas);
	for (int i = 0; i < linhas; i++) {
		//alocando vetor de int
		this->m[i] = (float *)malloc(sizeof(float) * colunas);
		for (int j = 0; j < colunas; j++) {

			this->m[i][j] = 0;

		}
	}
	this->linhas = linhas;
	this->colunas = colunas;
}

fMatrix *
fMatrix::cpy()
{
	fMatrix *copia = new fMatrix(this->linhas, this->colunas);
	for (int i = 0; i < this->linhas; i++) {
		for (int j = 0; j < this->colunas; j++) {

			copia->set(i, j, this->m[i][j]);
		}
	}
	return copia;
}

int
fMatrix::getLinhas()
{

	return this->linhas;
}

int
fMatrix::getColunas()
{

	return this->colunas;
}

void
fMatrix::set(int i, int j, float cor)
{
	if ((i < linhas) && (j < colunas)) {
		this->m[i][j] = cor;
	} else {
		printf("\ntentativa de estrapolar as dimencoes da matrix: %i,%i\n\n", i,
			   j);
		this->print();
		exit(1);
	}
}

float
fMatrix::toCinza(float red, float green, float blue)
{
	return 0.299 * red + 0.587 * green + 0.114 * blue;
}

void
fMatrix::set(int i, int j, float red, float green, float blue)
{
	this->m[i][j] = this->toCinza(red, green, blue);
}

void
fMatrix::print()
{
	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {

			printf("%f ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

float
fMatrix::get(int i, int j)
{
	if ((i < linhas) && (j < colunas)) {
		return this->m[i][j];
	} else {
		printf("\ntentativa de estrapolar as dimencoes da matrix: %i,%i\n\n", i,
			   j);
		this->print();
		exit(1);
	}
}

fMatrix::~fMatrix()
{
	printf("fMatrix: destructor");
	for (int i = 0; i < this->linhas; i++) {
		if (this->m[i])
			free(this->m[i]);
	}
	if (this->m)
		free(this->m);
}
