#ifndef _RENDER_HH
#define _RENDER_HH

#include "conf.hh"
#include "bmp.hh"
#include "math.h"
#include "stdlib.h"

#define PI 3.141592
#define MinGray 0
#define MaxGray 255

class RGB
{
	public:
	float r;
	float g;
	float b;
};

class Render
{
	private:
	Conf * conf;
	Bmp *bmp;
	RGB **matriz;
	//atributos auxiliares para calculo
	float fRPx, fRPy;			// armazena a razão 1 / (tamanho do pixel) para otimização
	float fMeioW, fMeioH;		// metade da largura e da altura para otimização
	float fRotation[3][3];		// matriz de rotação
	float fMenor, fMaior;		// maior e menor das bandas RGB do Phong

	public:
	Render(Conf * conf, Bmp * bmp);
	float power(float base, int exp);
	void calcMatrizRotacao();
	void normalizar();
	float calcProdutoEscalar(float *um, float *dois);
	float calcNumerador(float AA, float BB);
	float calcDenominador(float AA, float BB);
	float calcDistancia(float x, float y, float z);
	float calcAngloCos(float X1, float Y1, float Z1, float X2, float Y2,
					   float Z2);
	float calcAngloCos(float *um, float *dois);
	float calcDelta(float AA, float BB);
	float getMenor(float *fbmp, float menor);
	float getMaior(float *fbmp, float maior);
	void init();
	void print();
	void phonger();
	~Render();
};

#endif
