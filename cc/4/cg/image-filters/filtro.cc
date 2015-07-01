#include "filtro.hh"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Filtro::Filtro()
{
//  this->M = NULL;
	M = '\0';
}

Filtro::Filtro(Matrix * matriz)
{
	this->M = matriz;
}

Filtro::~Filtro()
{
	if (this->M)
		delete(this->M);
	this->M = '\0';
}

Matrix *
Filtro::threshold()
{
	return this->threshold(127);
}

Matrix *
Filtro::threshold(int limite)
{
	Matrix *maux = this->M->cpy();
	for (int i = 0; i < maux->getLinhas(); i++)
		for (int j = 0; j < maux->getColunas(); j++) {
			if (maux->get(i, j) < (int)limite)
				maux->set(i, j, PRETO);
			else
				maux->set(i, j, BRANCO);
		}
	return maux;
}

int
Filtro::calcDistancia(int pa, int pb)
{
	return (int)rint(sqrt(((pa - pb) * (pa - pb)) * 3)) & 0xFF;
}

Matrix *
Filtro::deteccao_de_borda()
{

	return this->deteccao_de_borda(50);
}

Matrix *
Filtro::deteccao_de_borda(int distancia)
{
	Matrix *maux = this->M->cpy();
	int atual, direita, baixo;
	for (int i = 0; i < (maux->getLinhas() - 1); i++) {
		for (int j = 0; j < (maux->getColunas() - 1); j++) {
			atual = maux->get(i, j);
			direita = maux->get(i, j + 1);
			baixo = maux->get(i + 1, j);
			direita = calcDistancia(atual, direita);
			baixo = calcDistancia(atual, baixo);
			if ((direita > (int)distancia) || (baixo > (int)distancia))
				//maux->set(i,j,PRETO);
				maux->set(i, j, BRANCO);
			else
				//maux->set(i,j,BRANCO);
				maux->set(i, j, PRETO);

		}
	}
	return maux;
}

Matrix *
Filtro::extracao_de_cor()
{

	return this->extracao_de_cor(50, BRANCO);
}

Matrix *
Filtro::extracao_de_cor(int distancia, int cor)
{
	Matrix *maux = this->M->cpy();
	int atual, dist;
	for (int i = 0; i < maux->getLinhas(); i++) {
		for (int j = 0; j < maux->getColunas(); j++) {

			atual = maux->get(i, j);
			dist = this->calcDistancia(atual, cor);
			if (dist < (int)distancia)
				maux->set(i, j, BRANCO);
			else
				maux->set(i, j, PRETO);
		}
	}
	return maux;
}

Matrix *
Filtro::mediana()
{
	return this->mediana(3);
}

int
get_pos_menor(int *v, int ini, const int tam)
{
	if (v) {
		int pos = ini;
		int menor = v[ini];
		for (int i = ini + 1; i < tam; i++) {
			if (v[i] < menor) {
				menor = v[i];
				pos = i;
			}
		}
		return pos;
	}
	return 0;
}

void
selection(int *v, const int tam)
{
	if (v) {
		int pos, temp;

		for (int i = 0; i < tam - 1; i++) {
			pos = get_pos_menor(v, i, tam);
			//troca
			temp = v[i];
			v[i] = v[pos];
			v[pos] = temp;
		}
	}
}

Matrix *
Filtro::mediana(int n)
{
	Matrix *maux = new Matrix(M->getLinhas(), M->getColunas());
	int i, j;
	int v[9];
	for (i = 1; i < (M->getLinhas() - 1); i++) {
		for (j = 1; j < (M->getColunas() - 1); j++) {

			v[0] = M->get(i - 1, j - 1);
			v[1] = M->get(i - 1, j);
			v[2] = M->get(i - 1, j + 1);
			v[3] = M->get(i, j - 1);
			v[4] = M->get(i, j);
			v[5] = M->get(i, j + 1);
			v[6] = M->get(i + 1, j - 1);
			v[7] = M->get(i + 1, j);
			v[8] = M->get(i + 1, j + 1);
			selection(v, 9);
			maux->set(i, j, v[4]);
		}
	}
	return maux;
}

fMatrix *
Filtro::calcJanela(int dimensao, float borda, float centro)
{
	fMatrix *mfiltro = new fMatrix(dimensao, dimensao);
	for (int i = 0; i < mfiltro->getLinhas(); i++) {
		for (int j = 0; j < mfiltro->getColunas(); j++) {

			int meio = (int)((dimensao - 1) / 2);
			if ((i == meio) && (j == meio))
				mfiltro->set(i, j, centro);
			else
				mfiltro->set(i, j, borda);
		}
	}
	return mfiltro;
}

Matrix *
Filtro::calcGambi()
{
	Matrix *mfiltro = new Matrix(3, 3);
	mfiltro->set(0, 0, -1);
	mfiltro->set(0, 1, -1);
	mfiltro->set(0, 2, -1);
	mfiltro->set(1, 0, -1);
	mfiltro->set(1, 1, 8);
	mfiltro->set(1, 2, -1);
	mfiltro->set(2, 0, -1);
	mfiltro->set(2, 1, -1);
	mfiltro->set(2, 2, -1);
	return mfiltro;
}

fMatrix *
Filtro::calcfGambi()
{
	fMatrix *mfiltro = new fMatrix(3, 3);
	mfiltro->set(0, 0, 1);
	mfiltro->set(0, 1, 1);
	mfiltro->set(0, 2, 1);
	mfiltro->set(1, 0, 1);
	mfiltro->set(1, 1, 1);
	mfiltro->set(1, 2, 1);
	mfiltro->set(2, 0, 1);
	mfiltro->set(2, 1, 1);
	mfiltro->set(2, 2, 1);
	return mfiltro;
}

int
Filtro::calcCor(int i2, int j2, fMatrix * mfiltro, float divisor)
{
	float acm = 0;
	int recuo = (int)floor((mfiltro->getLinhas() - 1) / 2);
	for (int i = 0; i < mfiltro->getLinhas(); i++) {
		for (int j = 0; j < mfiltro->getColunas(); j++) {
			acm +=
				mfiltro->get(i, j) * this->M->get(i + i2 - recuo,
												  j + j2 - recuo);
		}
	}
	return (int)rint(acm / divisor);
}

Matrix *
Filtro::passa_alta()
{
	return this->passa_alta(3);
}

Matrix *
Filtro::passa_alta(int n)
{
	Matrix *maux = this->M->cpy();
	fMatrix *mfiltro = this->calcJanela(n, -1, n * n - 1);
	int recuo = (int)(n - 1) / 2;
	mfiltro->print();
	for (int i = recuo; i < M->getLinhas() - recuo; i++) {
		for (int j = recuo; j < M->getColunas() - recuo; j++) {

			int pixel = this->calcCor(i, j, mfiltro, n * n);
			maux->set(i, j, pixel);
		}
	}
	return maux;
}

Matrix *
Filtro::passa_baixa()
{
	return this->passa_baixa(3);
}

Matrix *
Filtro::passa_baixa(int dimensao)
{
	Matrix *maux = this->M->cpy();
	fMatrix *mfiltro = this->calcJanela(dimensao, 1, 1);
	mfiltro->print();
	int recuo = (int)(dimensao - 1) / 2;
	for (int i = recuo; i < M->getLinhas() - recuo; i++) {
		for (int j = recuo; j < M->getColunas() - recuo; j++) {

			int pixel = this->calcCor(i, j, mfiltro, dimensao * dimensao);
			maux->set(i, j, pixel);
		}
	}
	return maux;
}

Matrix *
Filtro::roberts()
{
	Matrix *maux = this->M->cpy();
	fMatrix *mV = new fMatrix(2, 2);
	fMatrix *mH = new fMatrix(2, 2);
	mV->set(0, 0, 0);
	mV->set(0, 1, 1);			//  0  1
	mV->set(1, 0, -1);
	mV->set(1, 1, 0);			// -1  0
	mH->set(0, 0, 1);
	mH->set(0, 1, 0);			//  1  0
	mH->set(1, 0, 0);
	mH->set(1, 1, -1);			//  0 -1
	for (int i = 0; i < M->getLinhas() - 1; i++) {
		for (int j = 0; j < M->getColunas() - 1; j++) {

			int a = this->calcCor(i, j, mV, 1);
			int b = this->calcCor(i, j, mH, 1);
			//int pixel = (int) rint(sqrt(pow(a,2) + pow(b,2)));
			int pixel = (int)rint(sqrt(a * a + b * b));
			maux->set(i, j, pixel);
		}
	}
	return maux;
}

Matrix *
Filtro::sobel()
{
	Matrix *maux = this->M->cpy();
	fMatrix *mV = new fMatrix(3, 3);
	fMatrix *mH = new fMatrix(3, 3);

	mV->set(0, 0, -1);
	mV->set(0, 1, 0);
	mV->set(0, 2, 1);			// -1  0  1
	mV->set(1, 0, -2);
	mV->set(1, 1, 0);
	mV->set(1, 2, 2);			// -2  0  2
	mV->set(2, 0, -1);
	mV->set(2, 1, 0);
	mV->set(2, 2, 1);			// -1  0  1
	mH->set(0, 0, 1);
	mH->set(0, 1, 2);
	mH->set(0, 2, 1);			//  1  2  1
	mH->set(1, 0, 0);
	mH->set(1, 1, 0);
	mH->set(1, 2, 0);			//  0  0  0 
	mH->set(2, 0, -1);
	mH->set(2, 1, -2);
	mH->set(2, 2, -1);			// -1 -2 -1
	int i, j;
	for (i = 1; i < M->getLinhas() - 1; i++) {
		for (j = 1; j < M->getColunas() - 1; j++) {

			int a = this->calcCor(i, j, mV, 1);
			int b = this->calcCor(i, j, mH, 1);
			//int pixel = (int) rint(sqrt(pow(a,2) + pow(b,2)));
			int pixel = (int)rint(sqrt(a * a + b * b));
			maux->set(i, j, pixel);
		}
	}
	return maux;
}

Matrix *
Filtro::hb()
{
	return this->hb(3, 1);		//idem passa-alta
}

Matrix *
Filtro::hb(int n, int a)
{
	Matrix *maux = this->M->cpy();
	fMatrix *mfiltro = this->calcJanela(n, -1, n * n * a - 1);
	int recuo = (int)(n - 1) / 2;
	mfiltro->print();
	for (int i = recuo; i < M->getLinhas() - recuo; i++) {
		for (int j = recuo; j < M->getColunas() - recuo; j++) {

			int pixel = this->calcCor(i, j, mfiltro, n * n);
			maux->set(i, j, pixel);
		}
	}
	return maux;
}
