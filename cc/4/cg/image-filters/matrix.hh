#ifndef _MATRIX_HH
#define _MATRIX_HH

class Matrix
{
	private:
	int **m;
	int linhas;
	int colunas;
	int toCinza(int red, int green, int blue);

	public:
	Matrix();
	Matrix(int linhas, int colunas);
	int get(int i, int j);
	void set(int i, int j, int cor);
	void set(int i, int j, int red, int green, int blue);
	Matrix *cpy();
	int getLinhas();
	int getColunas();
	void print();
	~Matrix();
};

class fMatrix
{
	private:
	float **m;
	int linhas;
	int colunas;
	float toCinza(float red, float green, float blue);

	public:
	fMatrix();
	fMatrix(int linhas, int colunas);
	float get(int i, int j);
	void set(int i, int j, float cor);
	void set(int i, int j, float red, float green, float blue);
	fMatrix *cpy();
	int getLinhas();
	int getColunas();
	void print();
	~fMatrix();
};

class Vector
{
	private:
	int *v;
	int tam;
	void alocar(int tam);
	int get_pos_menor(int ini);

	public:
	Vector(int tam);
	void matrix2vector(int i, int j, int n, Matrix * m);
	void selection();
	int get(int i);
	int getMeio();
	void print();
	~Vector();
};

#endif
