#include "conf.hh"

void
Superficie::init()
{
}

void
Camera::init()
{
}

void
Iluminacao::init()
{
}

void
Reflexao::init()
{
}

void
Superficie::print()
{
	cout << " __________________________" << endl;
	cout << " |::Superficie::" << endl;
	cout << " |>> superficie.a = " << vet[A] << endl;
	cout << " |>> superficie.b = " << vet[B] << endl;
	cout << " |>> superficie.c = " << vet[C] << endl;
	cout << " |>> superficie.d = " << vet[D] << endl;
	cout << " |>> superficie.e = " << vet[E] << endl;
	cout << " |>> superficie.f = " << vet[F] << endl;
	cout << " |>> superficie.g = " << vet[G] << endl;
	cout << " |>> superficie.h = " << vet[H] << endl;
	cout << " |>> superficie.j = " << vet[J] << endl;
	cout << " |>> superficie.k = " << vet[K] << endl;
	cout << " |_________________________" << endl;
}

void
Camera::print()
{
	cout << " __________________________" << endl;
	cout << " |::Camera::" << endl;
	cout << " |>> exterior.cx = " << exterior[CX] << endl;
	cout << " |>> exterior.cy = " << exterior[CY] << endl;
	cout << " |>> exterior.cz = " << exterior[CZ] << endl;
	cout << " |>> exterior.rx = " << exterior[RX] << endl;
	cout << " |>> exterior.ry = " << exterior[RY] << endl;
	cout << " |>> exterior.rz = " << exterior[RZ] << endl;
	cout << " |>> interior.largura = " << interior[LARGURA] << endl;
	cout << " |>> interior.altura = " << interior[ALTURA] << endl;
	cout << " |>> interior.px = " << interior[PX] << endl;
	cout << " |>> interior.py = " << interior[PY] << endl;
	cout << " |>> interior.distancia_focal = " << interior[DISTANCIA_FOCAL] <<
		endl;
	cout << " |_________________________" << endl;
}

void
Iluminacao::print()
{
	cout << " __________________________" << endl;
	cout << " |::Iluminacao::" << endl;
	cout << " |>> posicao.x = " << posicao[X] << endl;
	cout << " |>> posicao.y = " << posicao[Y] << endl;
	cout << " |>> posicao.z = " << posicao[Z] << endl;
	cout << " |>> ambiente.r = " << ambiente[CR] << endl;
	cout << " |>> ambiente.g = " << ambiente[CG] << endl;
	cout << " |>> ambiente.b = " << ambiente[CB] << endl;
	cout << " |>> indice.r = " << indice[CR] << endl;
	cout << " |>> indice.g = " << indice[CG] << endl;
	cout << " |>> indice.b = " << indice[CB] << endl;
	cout << " |_________________________" << endl;
}

void
Reflexao::print()
{
	cout << " __________________________" << endl;
	cout << " |::Reflexao::" << endl;
	cout << " |>> difuso.r = " << difuso[CR] << endl;
	cout << " |>> difuso.g = " << difuso[CG] << endl;
	cout << " |>> difuso.b = " << difuso[CB] << endl;
	cout << " |>> espectral.r = " << espectral[CR] << endl;
	cout << " |>> espectral.g = " << espectral[CG] << endl;
	cout << " |>> espectral.b = " << espectral[CB] << endl;
	cout << " |>> ambiente.r = " << ambiente[CR] << endl;
	cout << " |>> ambiente.g = " << ambiente[CG] << endl;
	cout << " |>> ambiente.b = " << ambiente[CB] << endl;
	cout << " |>> n = " << n << endl;
	cout << " |_________________________" << endl;
}

void
Conf::init()
{
	superficie = new Superficie();
	camera = new Camera();
	iluminacao = new Iluminacao();
	reflexao = new Reflexao();
}

void
Conf::print()
{
	cout << ":::[IMPRIMINDO CONFIGURACOES]:::" << endl;
	superficie->print();
	camera->print();
	iluminacao->print();
	reflexao->print();
	cout << ":::[FIM]:::" << endl;
}

void
Conf::init6()
{
	delete(superficie);
	delete(camera);
	delete(iluminacao);
	delete(reflexao);
}
