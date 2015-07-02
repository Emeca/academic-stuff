/* vim: set ts=4 sw=4: */

#include "interface.h"
#include "fila.h"

void
print_andares(hospital *H)
{
	int i;
	for (i = ANDARES - 1; i >= 0; i--) {

		printf("\t\t|------------------------------------------------\n");
		printf("\t\t|Andar: %i\n", i);
		printf("\t\t|Pessoas que estao na fila: %i\n", H->A[i].F.tam);

		if (H->E[2].andar == i)
			printf("\r          EM");
		if (H->E[1].andar == i)
			printf("\r      E2");
		if (H->E[0].andar == i)
			printf("\r  E1");

		print_fila(&(H->A[i].F));
		print_fila_prioridade(&(H->A[i].F));

		printf("\t\t|------------------------------------------------\n");
		printf("\n");

	}
}

void
print_elevadores(hospital *H)
{
	int i;

	printf("\r___________________________________________________________\n\n");

	for (i = 0; i < N_ELEVADORES; i++) {
		printf("  Elevador: %i => Andar: %i, Prioridade: %i\n", i,
			   H->E[i].andar, H->P[i].andar);
	}
	printf("\n");
}

void
print_hospital(hospital *H)
{
	system("clear");
	printf("Hospital Originale de La Assuncion - HOLA\n");
	printf("===============================================================\n");
	print_andares(H);
	print_elevadores(H);
	printf("===============================================================\n");
}

int
get_usuarios(hospital *H)
{
	int i;
	int usuarios = 0;
	for (i = 0; i < ANDARES; i++)

		usuarios += H->A[i].usuarios;

	return usuarios;
}

int
get_tempo_total(hospital *H)
{
	int i;
	int tempo = 0;
	for (i = 0; i < ANDARES; i++)

		tempo += H->A[i].espera_total;
	return tempo;
}

float
tempo_medio_espera(hospital *H)
{
	int i, usuarios, espera_total;

	usuarios = espera_total = 0;
	for (i = 0; i < ANDARES; i++) {

		usuarios += H->A[i].usuarios;
		espera_total += H->A[i].espera_total;
	}
	return (float) espera_total / usuarios;
}

int
maior_fila(hospital *H, int *max)
{
	int andar = 0;
	int i;
	*max = 0;

	for (i = 0; i < ANDARES; i++) {

		if (*max < H->A[i].F.max) {
			*max = H->A[i].F.max;
			andar = i;
		}
	}
	return andar;
}

void
print_relatorio(hospital *H)
{

	int max_fila;
	int andar = maior_fila(H, &max_fila);
	int uhet1 = 0;

	printf("\n");
	printf("-> Tempo medio de espera para usar o elevador: %f\n",
		   tempo_medio_espera(H));
	printf("-> Quantidade de pacientes que foram a obito: %i\n", uhet1);
	printf("-> Maxima fila formada: %i, Andar: %i\n", max_fila, andar);
	printf("-> Usuarios: %i\n", get_usuarios(H));
	printf("-> Tempo: %i\n", get_tempo_total(H));
}
