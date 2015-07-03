#include "bmp.hh"
#include "matrix.hh"
#include "filtro.hh"
#include <math.h>
#include <unistd.h>

#define RESOLUCAO 24

//largura == coluna (width)
//altura == linha

//$uhetfiltro -t uhet.bmp

Matrix* bmp2matrix(Bmp* bmp){

	cout << "transformando bmp em matriz... ";
	Matrix* matriz = new Matrix( (int)bmp->TellWidth(), (int)bmp->TellHeight() );
	int r,g,b;
	int i,j;

	for (i = 0 ; i < (int) bmp->TellWidth() ; i++){
		for (j = 0 ; j < (int) bmp->TellHeight() ; j++){

			r = (int) (*bmp)(i,j)->Red;
			g = (int) (*bmp)(i,j)->Green;
			b = (int) (*bmp)(i,j)->Blue;

			matriz->set(i,j,r,g,b);
		}
	}
	cout << "ok" << endl;
	return matriz;
}

Bmp* matrix2bmp(Matrix* matriz){


	cout << "transformando matriz em bmp... ";
	Bmp* bmp = new Bmp(matriz->getLinhas(), matriz->getColunas(), RESOLUCAO);
	int i,j;

	for (i = 0 ; i < matriz->getLinhas() ; i++){
		for (j = 0 ; j < matriz->getColunas() ; j++){

			(*bmp)(i,j)->Red = matriz->get(i,j);
			(*bmp)(i,j)->Green = matriz->get(i,j);
			(*bmp)(i,j)->Blue = matriz->get(i,j);

		}
	}
	cout << "ok" << endl;
	return bmp;
}



int main(int argc, char* argv[]){

	//if (argc == 3) {
	if (argc == 1) {
		
		cout << "tres parametros... ok" << endl;
		// se a opcao estiver correta e o arquivo existir:		
		DisplayBitmapInfo("gnu.bmp");

		Bmp* bmp = new Bmp("gnu.bmp");
		Matrix* matriz = bmp2matrix(bmp);
		delete(bmp);
		Filtro* filtro = new Filtro(matriz);

		Matrix* mcinza 		= matriz->cpy();
		Matrix* mtshould	= filtro->threshold();
		Matrix* mborda		= filtro->deteccao_de_borda();
		Matrix* mecor		= filtro->extracao_de_cor();
		Matrix* mmediana	= filtro->mediana();
		Matrix* mpalta		= filtro->passa_alta();
		Matrix* mpbaixa		= filtro->passa_baixa();
		Matrix* mroberts	= filtro->roberts();
		Matrix* msobel		= filtro->sobel();
		Matrix* mhb			= filtro->hb();

		Bmp* bmp_mcinza		= matrix2bmp(mcinza);	bmp_mcinza->WriteToFile("gnu_cinza.bmp");
		Bmp* bmp_mtshould	= matrix2bmp(mtshould);	bmp_mtshould->WriteToFile("gnu_tshould.bmp");
		Bmp* bmp_mborda		= matrix2bmp(mborda);	bmp_mborda->WriteToFile("gnu_borda.bmp");
		Bmp* bmp_mecor		= matrix2bmp(mecor);	bmp_mecor->WriteToFile("gnu_ecor.bmp");
		Bmp* bmp_mmediana	= matrix2bmp(mmediana);	bmp_mmediana->WriteToFile("gnu_mediana.bmp");
		Bmp* bmp_mpalta		= matrix2bmp(mpalta);	bmp_mpalta->WriteToFile("gnu_palta.bmp");
		Bmp* bmp_mpbaixa	= matrix2bmp(mpbaixa);	bmp_mpbaixa->WriteToFile("gnu_pbaixa.bmp");
		Bmp* bmp_mroberts	= matrix2bmp(mroberts);	bmp_mroberts->WriteToFile("gnu_roberts.bmp");
		Bmp* bmp_msobel		= matrix2bmp(msobel);	bmp_msobel->WriteToFile("gnu_sobel.bmp");
		Bmp* bmp_mhb		= matrix2bmp(mhb);		bmp_mhb->WriteToFile("gnu_hb.bmp");
		
		delete(bmp_mcinza);
		delete(bmp_mtshould);
		delete(bmp_mborda);
		delete(bmp_mecor);
		delete(bmp_mmediana);
		delete(bmp_mpalta);
		delete(bmp_mpbaixa);
		delete(bmp_mroberts);
		delete(bmp_msobel);
		delete(bmp_mhb);

	} else {
		cout << "oops: digita certo rapaiz!!!" << endl;
		cout << "sintaxe: " << argv[0] << " <opcao> <arquivo_de_entrada>" << endl;
	}

	cout << "maravilha alberto!" << endl;
	return 0;
}
