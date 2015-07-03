#ifndef __FILTRO_HH
#define __FILTRO_HH

#include "matrix.hh"

#define PRETO 0
#define BRANCO 255

class Filtro{

	private:
		Matrix* M;
		fMatrix* calcJanela(int dimensao, float borda, float centro);
		Matrix* calcGambi();
		fMatrix* calcfGambi();
		int calcDistancia(int pa, int pb);
		int calcCor(int i, int j, fMatrix* filtro, float divisor);


	public:
		Filtro();
		Filtro(Matrix* matriz);
		Matrix* threshold(int limite);
		Matrix* threshold();
		Matrix* deteccao_de_borda();
		Matrix* deteccao_de_borda(int distancia);
		Matrix* extracao_de_cor();
		Matrix* extracao_de_cor(int distancia, int cor);
		Matrix* mediana();
		Matrix* mediana(int n);
		Matrix* passa_alta();
		Matrix* passa_alta(int n);
		Matrix* passa_baixa();
		Matrix* passa_baixa(int n);
		Matrix* roberts();
		Matrix* sobel();
		Matrix* hb();
		Matrix* hb(int n, int a);
		~Filtro();



};


#endif
