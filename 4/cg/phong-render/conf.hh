#ifndef _CONF_HH
#define _CONF_HH

#include <iostream>
#include <string>

#define CX 0
#define CY 1
#define CZ 2
#define RX 3
#define RY 4
#define RZ 5
#define CAM_EXTERIOR 6
#define LARGURA 0
#define ALTURA 1
#define PX 2
#define PY 3
#define DISTANCIA_FOCAL 4
#define CAM_INTERIOR 5
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define J 8
#define K 9
#define SUPERFICIE 10
#define X 0
#define Y 1
#define Z 2
#define ILU_POSICAO 3
#define CR 0
#define CG 1
#define CB 2
#define ILU_AMBIENTE 3

//R G B
#define ILU_INDICE 3
#define REF_DIFUSO 3
#define REF_ESPECTRAL 3
#define REF_AMBIENTE 3

using namespace std;

class Superficie
{
	public:
	Superficie()
	{
		cout << "constructor de Superficie" << endl;
		init();
	};
	float vet[SUPERFICIE];		// A B C D E F G H J K
	void init();
	void print();
	~Superficie() {
		cout << "destructor de Superficie" << endl;
	};
};

class Camera
{
	public:
	Camera()
	{
		cout << "constructor de Camera" << endl;
		init();
	};
	float exterior[CAM_EXTERIOR];	// CX CY CZ RX RY RZ
	float interior[CAM_INTERIOR];	// LARGURA ALTURA PX PY DISTANCIA_FOCAL
	void init();
	void print();
	~Camera() {
		cout << "destructor de Camera" << endl;
	};
};

class Iluminacao
{
	public:
	Iluminacao()
	{
		cout << "contructor de Iluminacao" << endl;
		init();
	};
	float posicao[ILU_POSICAO];	// X Y Z
	float ambiente[ILU_AMBIENTE];	// CR CG CB
	float indice[ILU_INDICE];	// CR CG CB
	void init();
	void print();
	~Iluminacao() {
		cout << "destructor de Iluminacao" << endl;
	};
};

class Reflexao
{
	public:
	Reflexao()
	{
		cout << "contructor de Reflexao" << endl;
		init();
	};
	float difuso[REF_DIFUSO];	// CR CG CB
	float espectral[REF_ESPECTRAL];	// CR CG CB
	float ambiente[REF_AMBIENTE];	// CR CG CB
	float n;
	void init();
	void print();
	~Reflexao() {
		cout << "destructor de Reflexao" << endl;
	};
};

class Conf
{
	public:
	Superficie *superficie;
	Camera *camera;
	Iluminacao *iluminacao;
	Reflexao *reflexao;
	Conf()
	{
		cout << "constructor de Conf" << endl;
		init();
	};
	void init();
	void print();
	void init6();
	~Conf() {
		init6();
		cout << "destructor de Conf" << endl;
	};
};
#endif
