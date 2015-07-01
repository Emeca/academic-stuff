#include "render.hh"

Render::Render(Conf * conf, Bmp * bmp)
{
	cout << "contructor de Render" << endl;
	Render::conf = conf;
	Render::bmp = bmp;
	fMeioW = conf->camera->interior[LARGURA] / 2;
	fMeioH = conf->camera->interior[ALTURA] / 2;
	fMenor = 1;
	fMaior = 0;
	fRPx = 1 / conf->camera->interior[PX];
	fRPy = 1 / conf->camera->interior[PY];
	conf->camera->exterior[RX] = conf->camera->exterior[RX] * PI / 180;
	conf->camera->exterior[RY] = conf->camera->exterior[RY] * PI / 180;
	conf->camera->exterior[RZ] = conf->camera->exterior[RZ] * PI / 180;
	matriz =
		(RGB **) malloc(sizeof(RGB *) *
						(int)rint(conf->camera->interior[LARGURA]));
	for (int i = 0; i < (int)rint(conf->camera->interior[LARGURA]); i++)
		matriz[i] =
			(RGB *) malloc(sizeof(RGB) *
						   (int)rint(conf->camera->interior[ALTURA]));
	init();
}

Render::~Render()
{
	cout << "destructor de Render" << endl;
	for (int i = 0; i < (int)rint(conf->camera->interior[LARGURA]); i++)
		if (matriz[i])
			free(matriz[i]);
	if (matriz)
		free(matriz);
	conf = NULL;
	bmp = NULL;
}

float
Render::power(float base, int exp)
{
	if (exp == 0)
		return 1;
	else
		return base * power(base, exp - 1);
}

float
Render::calcProdutoEscalar(float *um, float *dois)
{
	return um[X] * dois[X] + um[Y] * dois[Y] + um[Z] * dois[Z];
}

float
Render::calcNumerador(float AA, float BB)
{
	return (-2 * conf->superficie->vet[D] * conf->camera->exterior[CX] * BB -
			2 * conf->superficie->vet[B]
			* conf->camera->exterior[CY] * BB - 2 * conf->superficie->vet[J] +
			2 * conf->superficie->vet[A]
			* AA * AA * conf->camera->exterior[CZ] -
			2 * conf->superficie->vet[A] * conf->camera->exterior[CX]
			* AA - 2 * conf->superficie->vet[H] * BB +
			2 * conf->superficie->vet[F] * AA * conf->camera->exterior[CZ]
			- 2 * conf->superficie->vet[E] * conf->camera->exterior[CY] -
			2 * conf->superficie->vet[G] * AA +
			2 * conf->superficie->vet[E] * BB * conf->camera->exterior[CZ] +
			2 * conf->superficie->vet[B] * BB * BB *
			conf->camera->exterior[CZ] -
			2 * conf->superficie->vet[F] * conf->camera->exterior[CX] -
			2 * conf->superficie->vet[B] * AA * conf->camera->exterior[CY] +
			4 * conf->superficie->vet[D] * AA * BB *
			conf->camera->exterior[CZ]);
}

float
Render::calcDenominador(float AA, float BB)
{
	return (2 * conf->superficie->vet[F] * AA + conf->superficie->vet[B]
			* BB * BB + conf->superficie->vet[C] +
			2 * conf->superficie->vet[E] * BB +
			2 * conf->superficie->vet[D] * AA * BB +
			conf->superficie->vet[A] * AA * AA);
}

float
Render::calcDistancia(float x, float y, float z)
{
	return (sqrtf(power((conf->camera->exterior[CX] - x), 2)
				  + power((conf->camera->exterior[CY] - y), 2)
				  + power((conf->camera->exterior[CZ] - z), 2)));
}

float
Render::calcAngloCos(float *um, float *dois)
{
	float temp, produto;
	temp =
		sqrtf(um[X] * um[X] + um[Y] * um[Y] +
			  um[Z] * um[Z]) * sqrtf(dois[X] * dois[X] + dois[Y] * dois[Y] +
									 dois[Z] * dois[Z]);
	if (temp != 0) {
		produto = calcProdutoEscalar(um, dois) / temp;
		if (produto < 0)
			return 0;
		else
			return produto;
	} else
		return 0;
}

void
Render::calcMatrizRotacao()
{
	float cosRx, senRx;			// cos do angulo de rotação de x
	float cosRy, senRy;			// cos do angulo de rotação de y
	float cosRz, senRz;			// cos do angulo de rotação de z
	cosRx = cos(conf->camera->exterior[RX]);
	senRx = sin(conf->camera->exterior[RX]);
	cosRy = cos(conf->camera->exterior[RY]);
	senRy = sin(conf->camera->exterior[RY]);
	cosRz = cos(conf->camera->exterior[RZ]);
	senRz = sin(conf->camera->exterior[RZ]);
	fRotation[0][0] = cosRx * cosRy;
	fRotation[0][1] = cosRx * senRy * senRz - senRx * cosRz;
	fRotation[0][2] = senRx * senRz + cosRx * senRy * cosRz;
	fRotation[1][0] = senRx * cosRy;
	fRotation[1][1] = cosRx * cosRz + senRx * senRy * senRz;
	fRotation[1][2] = cosRz * senRx * senRy - cosRx * senRz;
	fRotation[2][0] = -senRy;
	fRotation[2][1] = senRz * cosRy;
	fRotation[2][2] = cosRz * cosRy;
}

void
Render::normalizar()
{
	float AA, BB;
	AA = fMaior - fMenor;
//  if (AA <= 0) AA = 1;
	if (AA <= 0)
		AA = 0;
	else
		AA = (MaxGray - MinGray) / AA;
	BB = MinGray - (fMenor * AA);
	for (int i = 0; i < bmp->TellWidth(); i++) {
		for (int j = 0; j < bmp->TellHeight(); j++) {
			(*bmp) (i, j)->Red = (int)(rint((matriz[i][j].r * AA + BB)));
			(*bmp) (i, j)->Green = (int)(rint((matriz[i][j].g * AA + BB)));
			(*bmp) (i, j)->Blue = (int)(rint((matriz[i][j].b * AA + BB)));
		}
	}
}

float
Render::calcDelta(float AA, float BB)
{
//  cout << "AA: " << AA << " | BB: " << BB << endl;
	float resp =
		-2 * conf->superficie->vet[C] * conf->superficie->vet[G] *
		conf->camera->exterior[CX]
		+
		conf->superficie->vet[D] * conf->superficie->vet[D] *
		conf->camera->exterior[CX]
		* conf->camera->exterior[CX] * BB * BB +
		2 * conf->superficie->vet[J] * conf->superficie->vet[H] * BB -
		2 * conf->superficie->vet[E] * BB * conf->superficie->vet[K] +
		conf->superficie->vet[J]
		* conf->superficie->vet[J] -
		conf->superficie->vet[C] * conf->superficie->vet[K] +
		conf->superficie->vet[F]
		* conf->superficie->vet[F] * AA * AA * conf->camera->exterior[CZ]
		* conf->camera->exterior[CZ] +
		conf->superficie->vet[E] * conf->superficie->vet[E]
		* BB * BB * conf->camera->exterior[CZ] * conf->camera->exterior[CZ]
		+ conf->superficie->vet[D] * conf->superficie->vet[D] * AA * AA
		* conf->camera->exterior[CY] * conf->camera->exterior[CY] + 2
		* conf->superficie->vet[J] * conf->superficie->vet[E] *
		conf->camera->exterior[CY]
		+ 2 * conf->superficie->vet[J] * conf->superficie->vet[G] * AA +
		2 * conf->superficie->vet[J] * conf->superficie->vet[F] *
		conf->camera->exterior[CX]
		- 2 * conf->superficie->vet[F] * AA * conf->superficie->vet[K]
		- conf->superficie->vet[B] * BB * BB * conf->superficie->vet[K]
		-
		2 * conf->superficie->vet[C] * conf->superficie->vet[H] *
		conf->camera->exterior[CY]
		-
		conf->superficie->vet[C] * conf->superficie->vet[A] *
		conf->camera->exterior[CX] * conf->camera->exterior[CX]
		-
		conf->superficie->vet[C] * conf->superficie->vet[B] *
		conf->camera->exterior[CY] * conf->camera->exterior[CY]
		- conf->superficie->vet[A] * AA * AA * conf->superficie->vet[K]
		+ 2 * conf->superficie->vet[D] * conf->camera->exterior[CX] * BB
		* BB * conf->superficie->vet[H] - 2 * conf->superficie->vet[D]
		* conf->camera->exterior[CX] * BB * conf->superficie->vet[F] * AA
		* conf->camera->exterior[CZ] -
		2 * conf->superficie->vet[D] * conf->camera->exterior[CX]
		* BB * conf->superficie->vet[E] * conf->camera->exterior[CY] -
		2 * conf->superficie->vet[D] * conf->camera->exterior[CX] * BB *
		conf->superficie->vet[G]
		* AA +
		2 * conf->superficie->vet[D] * conf->camera->exterior[CX] * BB * BB *
		conf->superficie->vet[E] * conf->camera->exterior[CZ] +
		2 * conf->superficie->vet[D] * conf->camera->exterior[CX] *
		conf->camera->exterior[CX] * BB * conf->superficie->vet[F] -
		2 * conf->superficie->vet[D] * conf->superficie->vet[D]
		* conf->camera->exterior[CX] * BB * AA * conf->camera->exterior[CY]
		+
		2 * conf->superficie->vet[B] * conf->camera->exterior[CY] * BB *
		conf->superficie->vet[A]
		* conf->camera->exterior[CX] * AA +
		2 * conf->superficie->vet[B] * conf->camera->exterior[CY]
		* BB * conf->superficie->vet[F] * AA * conf->camera->exterior[CZ] +
		2 * conf->superficie->vet[B] * conf->camera->exterior[CY] * BB *
		conf->superficie->vet[G] * AA +
		2 * conf->superficie->vet[B] * conf->camera->exterior[CY] * BB *
		conf->superficie->vet[F]
		* conf->camera->exterior[CX] +
		conf->superficie->vet[H] * conf->superficie->vet[H] * BB * BB +
		conf->superficie->vet[E] * conf->superficie->vet[E] *
		conf->camera->exterior[CY] * conf->camera->exterior[CY]
		+ conf->superficie->vet[G] * conf->superficie->vet[G] * AA * AA +
		conf->superficie->vet[F]
		* conf->superficie->vet[F] * conf->camera->exterior[CX] *
		conf->camera->exterior[CX] -
		2 * conf->superficie->vet[A] * AA * AA * conf->camera->exterior[CZ] *
		conf->superficie->vet[E]
		* conf->camera->exterior[CY] +
		2 * conf->superficie->vet[A] * conf->camera->exterior[CX] * AA *
		conf->superficie->vet[H] * BB +
		2 * conf->superficie->vet[A] * conf->camera->exterior[CX]
		* AA * conf->superficie->vet[E] * conf->camera->exterior[CY] +
		2 * conf->superficie->vet[A]
		* conf->camera->exterior[CX] * AA * conf->superficie->vet[E] * BB *
		conf->camera->exterior[CZ]
		+
		2 * conf->superficie->vet[H] * BB * conf->superficie->vet[F] * AA *
		conf->camera->exterior[CZ] -
		2 * conf->superficie->vet[H] * BB * conf->superficie->vet[E]
		* conf->camera->exterior[CY] +
		2 * conf->superficie->vet[H] * BB * conf->superficie->vet[G]
		* AA + 2 * conf->superficie->vet[H] * BB * BB * conf->superficie->vet[E]
		* conf->camera->exterior[CZ] +
		2 * conf->superficie->vet[H] * BB * conf->superficie->vet[F]
		* conf->camera->exterior[CX] -
		2 * conf->superficie->vet[H] * BB * conf->superficie->vet[D]
		* AA * conf->camera->exterior[CY] -
		2 * conf->superficie->vet[F] * AA * conf->camera->exterior[CZ] *
		conf->superficie->vet[E] * conf->camera->exterior[CY] +
		2 * conf->superficie->vet[F]
		* AA * AA * conf->camera->exterior[CZ] * conf->superficie->vet[G] +
		2 * conf->superficie->vet[F] * AA * conf->camera->exterior[CZ] *
		conf->camera->exterior[CZ] * conf->superficie->vet[E]
		* BB -
		2 * conf->superficie->vet[F] * conf->superficie->vet[F] * AA *
		conf->camera->exterior[CZ] * conf->camera->exterior[CX] +
		2 * conf->superficie->vet[F] * AA * AA * conf->camera->exterior[CZ] *
		conf->superficie->vet[D] * conf->camera->exterior[CY] +
		2 * conf->superficie->vet[E] * conf->camera->exterior[CY] *
		conf->superficie->vet[G] * AA -
		2 * conf->superficie->vet[E] * conf->superficie->vet[E] *
		conf->camera->exterior[CY] * BB * conf->camera->exterior[CZ]
		+
		2 * conf->superficie->vet[E] * conf->camera->exterior[CY] *
		conf->superficie->vet[F] * conf->camera->exterior[CX]
		+
		2 * conf->superficie->vet[E] * conf->camera->exterior[CY] *
		conf->camera->exterior[CY] * conf->superficie->vet[D]
		* AA -
		2 * conf->superficie->vet[E] * conf->camera->exterior[CY] *
		conf->superficie->vet[D]
		* AA * BB * conf->camera->exterior[CZ] +
		2 * conf->superficie->vet[G] * AA * conf->superficie->vet[E] * BB *
		conf->camera->exterior[CZ] - 2 * conf->superficie->vet[G]
		* AA * conf->superficie->vet[F] * conf->camera->exterior[CX] +
		2 * conf->superficie->vet[G]
		* AA * AA * conf->superficie->vet[D] * conf->camera->exterior[CY] -
		2 * conf->superficie->vet[E] * BB * conf->camera->exterior[CZ] *
		conf->superficie->vet[F] * conf->camera->exterior[CX]
		-
		2 * conf->superficie->vet[B] * BB * BB * conf->camera->exterior[CZ] *
		conf->superficie->vet[F]
		* conf->camera->exterior[CX] -
		2 * conf->superficie->vet[F] * conf->camera->exterior[CX] *
		conf->superficie->vet[D]
		* AA * conf->camera->exterior[CY] +
		2 * conf->superficie->vet[D] * conf->camera->exterior[CX]
		* BB * conf->superficie->vet[J] +
		2 * conf->superficie->vet[B] * conf->camera->exterior[CY] * BB *
		conf->superficie->vet[J] -
		2 * conf->superficie->vet[J] * conf->superficie->vet[A] * AA * AA *
		conf->camera->exterior[CZ] +
		2 * conf->superficie->vet[J] * conf->superficie->vet[A] *
		conf->camera->exterior[CX]
		* AA -
		2 * conf->superficie->vet[J] * conf->superficie->vet[F] * AA *
		conf->camera->exterior[CZ]
		-
		2 * conf->superficie->vet[J] * conf->superficie->vet[E] * BB *
		conf->camera->exterior[CZ] -
		2 * conf->superficie->vet[J] * conf->superficie->vet[B] * BB * BB *
		conf->camera->exterior[CZ] +
		2 * conf->superficie->vet[J] * conf->superficie->vet[D] * AA *
		conf->camera->exterior[CY] - 4 * conf->superficie->vet[J]
		* conf->superficie->vet[D] * AA * BB * conf->camera->exterior[CZ] -
		4 * conf->superficie->vet[F]
		* AA * conf->superficie->vet[H] * conf->camera->exterior[CY] -
		2 * conf->superficie->vet[F] * AA * conf->superficie->vet[B] *
		conf->camera->exterior[CY] * conf->camera->exterior[CY] -
		2 * conf->superficie->vet[B]
		* BB * BB * conf->superficie->vet[G] * conf->camera->exterior[CX] -
		conf->superficie->vet[B] * BB * BB * conf->superficie->vet[A] *
		conf->camera->exterior[CX] * conf->camera->exterior[CX] -
		4 * conf->superficie->vet[E] * BB * conf->superficie->vet[G] *
		conf->camera->exterior[CX] - 2 * conf->superficie->vet[E]
		* BB * conf->superficie->vet[A] * conf->camera->exterior[CX] *
		conf->camera->exterior[CX] -
		2 * conf->superficie->vet[A] * AA * AA * conf->superficie->vet[H] *
		conf->camera->exterior[CY] - conf->superficie->vet[A]
		* AA * AA * conf->superficie->vet[B] * conf->camera->exterior[CY] *
		conf->camera->exterior[CY] -
		2 * conf->superficie->vet[C] * conf->superficie->vet[D] *
		conf->camera->exterior[CX] * conf->camera->exterior[CY] -
		conf->superficie->vet[C]
		* conf->superficie->vet[B] * BB * BB * conf->camera->exterior[CZ] *
		conf->camera->exterior[CZ] - conf->superficie->vet[C]
		* conf->superficie->vet[A] * AA * AA * conf->camera->exterior[CZ] *
		conf->camera->exterior[CZ] +
		2 * conf->superficie->vet[C] * conf->superficie->vet[A] *
		conf->camera->exterior[CX] * AA * conf->camera->exterior[CZ] +
		2 * conf->superficie->vet[C] * conf->superficie->vet[H] * BB *
		conf->camera->exterior[CZ] - 2 * conf->superficie->vet[C]
		* conf->superficie->vet[D] * AA * conf->camera->exterior[CZ] *
		conf->camera->exterior[CZ] * BB +
		2 * conf->superficie->vet[C] * conf->superficie->vet[B] *
		conf->camera->exterior[CY] * BB * conf->camera->exterior[CZ] +
		2 * conf->superficie->vet[C] * conf->superficie->vet[D] *
		conf->camera->exterior[CX] * BB * conf->camera->exterior[CZ] +
		2 * conf->superficie->vet[C] * conf->superficie->vet[G] * AA *
		conf->camera->exterior[CZ] + 2 * conf->superficie->vet[C]
		* conf->superficie->vet[D] * AA * conf->camera->exterior[CZ] *
		conf->camera->exterior[CY] - 2 * conf->superficie->vet[D]
		* AA * BB * conf->superficie->vet[K];
	if (resp >= 0) {
//      cout << "antes da raiz: " << resp << endl; 
		return sqrtf(resp);
	} else
		return -1;
}

void
Render::phonger()
{
	float x, y;					// x,y no sistema espaco imagem
	float AA, BB;
	float norm[3], dirL[3], dirO[3], ref[3], fbmp[3];
	float denominador, delta, Z1, Z2;
	float intersec1[2], intersec2[2];
	float dist1, dist2, cos_alfa, cos_teta;
	calcMatrizRotacao();
	for (int i = 0; i < bmp->TellWidth(); i++) {
		for (int j = 0; j < bmp->TellHeight(); j++) {
//          x = fRPx * (i * fMeioW); errei porra!!! umas 5 horas pra acha esse lixo de erro
			x = fRPx * (i - fMeioW);
			y = -(fRPy * (j - fMeioH));
//          cout << "fMeioW [" << i <<"," << j <<"]: " << fMeioW << " | fMeioH [" << i << "," << j <<"]: " << fMeioH << endl;
//          cout << "fRPx [" << i <<"," << j <<"]: " << fRPx << " | fRPy [" << i << "," << j <<"]: " << fRPy << endl;
//          cout << "x [" << i <<"," << j <<"]: " << x << " | y [" << i << "," << j <<"]: " << y << endl;
			AA = fRotation[0][0] * x + fRotation[1][0] * y +
				fRotation[2][0] * conf->camera->interior[DISTANCIA_FOCAL];
			AA = AA / (fRotation[0][2] * x + fRotation[1][2] * y +
					   fRotation[2][2] *
					   conf->camera->interior[DISTANCIA_FOCAL]);
			BB = fRotation[0][1] * x + fRotation[1][1] * y +
				fRotation[2][1] * conf->camera->interior[DISTANCIA_FOCAL];
			BB = BB / (fRotation[0][2] * x + fRotation[1][2] * y +
					   fRotation[2][2] *
					   conf->camera->interior[DISTANCIA_FOCAL]);
//          cout << "AA [" << i <<"," << j <<"]: " << AA << " | BB [" << i << "," << j <<"]: " << BB << endl;
			denominador = calcDenominador(AA, BB);
//          cout << "denominador [" << i <<"," << j <<"]: " << denominador << endl;
			if (denominador != 0) {
				delta = calcDelta(AA, BB);
//              cout << "delta [" << i <<"," << j <<"]: " << delta << endl;
				if (delta > -1) {
					float aux = calcNumerador(AA, BB);
					Z1 = 0.5 * (aux + 2 * delta) / denominador;
					Z2 = 0.5 * (aux - 2 * delta) / denominador;
//                  cout << "Z1 [" << i <<"," << j <<"]: " << Z1 << " || ";
//                  cout << "Z2 [" << i <<"," << j <<"]: " << Z2 << endl;
					aux = Z1 - conf->camera->exterior[CZ];
					intersec1[X] = conf->camera->exterior[CX] + aux * AA;
					intersec1[Y] = conf->camera->exterior[CY] + aux * BB;
					dist1 = calcDistancia(intersec1[X], intersec1[Y], Z1);
					aux = Z2 - conf->camera->exterior[CZ];
					intersec2[X] = conf->camera->exterior[CX] + aux * AA;
					intersec2[Y] = conf->camera->exterior[CY] + aux * BB;
					dist2 = calcDistancia(intersec2[X], intersec2[Y], Z2);
//                  cout << "dist1 [" << i <<"," << j <<"]: " << dist1 << " || ";
//                  cout << "dist2 [" << i <<"," << j <<"]: " << dist2 << " || " << endl;
//                  cout << "IntersecX1 [" << i <<"," << j <<"]: " << intersec1[X] << " || ";
//                  cout << "IntersecY1 [" << i <<"," << j <<"]: " << intersec1[Y] << " || ";
//                  cout << "IntersecX2 [" << i <<"," << j <<"]: " << intersec2[X] << " || ";
//                  cout << "IntersecY2 [" << i <<"," << j <<"]: " << intersec2[Y] << " || " << endl;
					if (dist1 > dist2) {
						intersec1[X] = intersec2[X];
						intersec1[Y] = intersec2[Y];
						Z1 = Z2;
					}
//                  cout << "Z1 [" << i <<"," << j <<"]: " << Z1 << " || ";
//                  cout << "Z2 [" << i <<"," << j <<"]: " << Z2 << endl;
//                  cout << "IntersecX1 [" << i <<"," << j <<"]: " << intersec1[X] << " || ";
//                  cout << "IntersecY1 [" << i <<"," << j <<"]: " << intersec1[Y] << " || ";
//                  cout << "IntersecX2 [" << i <<"," << j <<"]: " << intersec2[X] << " || ";
//                  cout << "IntersecY2 [" << i <<"," << j <<"]: " << intersec2[Y] << " || " << endl;
					//OK
					norm[X] = 2 * conf->superficie->vet[A] * intersec1[X]
						+ 2 * conf->superficie->vet[D] * intersec1[Y]
						+ 2 * conf->superficie->vet[F] * Z1
						+ 2 * conf->superficie->vet[G];
					norm[Y] = 2 * conf->superficie->vet[B] * intersec1[Y]
						+ 2 * conf->superficie->vet[D] * intersec1[X]
						+ 2 * conf->superficie->vet[E] * Z1
						+ 2 * conf->superficie->vet[H];
					norm[Z] = 2 * conf->superficie->vet[C] * Z1
						+ 2 * conf->superficie->vet[E] * intersec1[Y]
						+ 2 * conf->superficie->vet[F] * intersec1[X]
						+ 2 * conf->superficie->vet[J];
					dirL[X] = conf->iluminacao->posicao[X] - intersec1[X];
					dirL[Y] = conf->iluminacao->posicao[Y] - intersec1[Y];
					dirL[Z] = conf->iluminacao->posicao[Z] - Z1;
					dirO[X] = conf->camera->exterior[CX] - intersec1[X];
					dirO[Y] = conf->camera->exterior[CY] - intersec1[Y];
					dirO[Z] = conf->camera->exterior[CZ] - Z1;
					aux = calcProdutoEscalar(dirL, norm);
					ref[X] = 2 * aux * norm[X] - dirL[X];
					ref[Y] = 2 * aux * norm[Y] - dirL[Y];
					ref[Z] = 2 * aux * norm[Z] - dirL[Z];
//ok                cout << "produto escalar[" << i << "," << j << "]: " << aux << endl;
//ok                cout << "norm[" << i << "," << j << "]: [X] = " << norm[X] << " [Y] = " << norm[Y] << " [Z] = " << norm[Z] << endl;
//ok                cout << "dirL[" << i << "," << j << "]: [X] = " << dirL[X] << " [Y] = " << dirL[Y] << " [Z] = " << dirL[Z] << endl;
//ok                cout << "dirO[" << i << "," << j << "]: [X] = " << dirO[X] << " [Y] = " << dirO[Y] << " [Z] = " << dirO[Z] << endl;
//ok                cout << "_ref[" << i << "," << j << "]: [X] = " << ref[X] << " [Y] = " << ref[Y] << " [Z] = " << ref[Z] << endl;
					cos_alfa = calcAngloCos(ref, dirO);
					cos_teta = calcAngloCos(dirL, norm);
//ok                cout << "cos_alfa[" << i << "," << j << "]: " << cos_alfa << " || " << "cos_teta[" << i << "," << j << "]: " << cos_teta << endl;
					aux = power(cos_alfa, (int)rint(conf->reflexao->n));
//ok                cout << "aux[" << i << "," << j << "]: " << aux << endl;
					fbmp[CR] =
						conf->iluminacao->ambiente[CR] *
						conf->reflexao->ambiente[CR] +
						conf->iluminacao->indice[CR]
						* (conf->reflexao->difuso[CR] * cos_teta +
						   conf->reflexao->espectral[CR] * aux);
					fbmp[CG] =
						conf->iluminacao->ambiente[CG] *
						conf->reflexao->ambiente[CG] +
						conf->iluminacao->indice[CG]
						* (conf->reflexao->difuso[CG] * cos_teta +
						   conf->reflexao->espectral[CG] * aux);
					fbmp[CB] =
						conf->iluminacao->ambiente[CB] *
						conf->reflexao->ambiente[CB] +
						conf->iluminacao->indice[CB]
						* (conf->reflexao->difuso[CB] * cos_teta +
						   conf->reflexao->espectral[CB] * aux);
//                  cout << "fbmp[" << i << "," << j << "]: [R] = " << fbmp[CR] << " [G] = " << fbmp[CG] << " [B] = " << fbmp[CB] << endl;
					fMenor = getMenor(fbmp, fMenor);
					fMaior = getMaior(fbmp, fMaior);
					matriz[i][j].r = fbmp[CR];
					matriz[i][j].g = fbmp[CG];
					matriz[i][j].b = fbmp[CB];
//                  bmp->pintarPixel(i,j,fbmp);
				} else {
					matriz[i][j].r = 0;
					matriz[i][j].g = 0;
					matriz[i][j].b = 0;
//                  bmp->pintarPixel(i,j,0,0,0);
				}
			} else {
				matriz[i][j].r = 0;
				matriz[i][j].g = 0;
				matriz[i][j].b = 0;
//              bmp->pintarPixel(i,j,0,0,0);
			}
		}
	}
}

void
Render::print()
{
	cout << "fRPx: " << fRPx << " | " << "fRPy: " << fRPy << endl;
	cout << "fMeioW: " << fMeioW << " | " << "fMeioH: " << fMeioH << endl;
	cout << "fMenor: " << fMenor << " | " << "fMaior: " << fMaior << endl;
}

void
Render::init()
{
	cout << "antes do phonger" << endl;
	phonger();
	cout << "depois do phonger" << endl;
	cout << "antes de normalizar" << endl;
	normalizar();
	cout << "depois de normalizar" << endl;
	print();
}

float
Render::getMenor(float *fbmp, float menor)
{
	float aux;
	if (fbmp[CR] < fbmp[CG])
		aux = fbmp[CR];
	else
		aux = fbmp[CG];
	if (fbmp[CB] < aux)
		aux = fbmp[CB];
	if (aux < menor)
		return aux;
	return menor;
}

float
Render::getMaior(float *fbmp, float maior)
{
	float aux;
	if (fbmp[CR] > fbmp[CG])
		aux = fbmp[CR];
	else
		aux = fbmp[CG];
	if (fbmp[CB] > aux)
		aux = fbmp[CB];
	if (aux > maior)
		return aux;
	return maior;
}
