#include "bmp.hh"

Bmp::Bmp(int largura, int altura, int resolucao)
{
	cout << "constructor de Bmp" << endl;
	BMP();
	this->SetSize(largura, altura);
	this->SetBitDepth(resolucao);
}

Bmp::Bmp(int largura, int altura, int resolucao, int r, int g, int b,
		 string arquivo)
{
	cout << "constructor de Bmp" << endl;
	BMP();
	this->SetSize(largura, altura);
	this->SetBitDepth(resolucao);
	for (int i = 0; i < this->TellWidth(); i++) {
		for (int j = 0; j < this->TellHeight(); j++) {
			pintarPixel(i, j, r, g, b);
		}
	}
	this->WriteToFile(arquivo.c_str());
}

void
Bmp::teste(int r, int g, int b)
{
	for (int i = 0; i < this->TellWidth(); i++) {
		for (int j = 0; j < this->TellHeight(); j++) {
			pintarPixel(i, j, r, g, b);
		}
	}
}

void
Bmp::pintarPixel(int i, int j, int r, int g, int b)
{
	(*this) (i, j)->Red = r;
	(*this) (i, j)->Green = g;
	(*this) (i, j)->Blue = b;
}

void
Bmp::pintarPixel(int i, int j, float *fbmp)
{
	(*this) (i, j)->Red = (int)rint(fbmp[0]);
	(*this) (i, j)->Green = (int)rint(fbmp[1]);
	(*this) (i, j)->Blue = (int)rint(fbmp[2]);
}
