#ifndef _BMP_HH
#define _BMP_HH

#include "lib/easybmp/EasyBMP.h"

using namespace std;

class Bmp:public BMP
{
	public:
	Bmp(int largura, int altura, int resolucao);
	Bmp(int largura, int altura, int resolucao, int r, int g, int b,
		 string arquivo);
	Bmp(string arquivo);
	void pintarPixel(int i, int j, int r, int g, int b);
	void pintarPixel(int i, int j, float *fbmp);
	void teste(int r, int g, int b);

	~Bmp()
	{
		cout << "destructor de Bmp" << endl;
	};
};

#endif
