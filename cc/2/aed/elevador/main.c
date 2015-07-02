/* vim: set ts=4 sw=4: */

#include <time.h>
#include "fila.h"
#include "interface.h"
#include "mygetch.h"

#define MOD(x) (x < 0) ? -x : x
#define PAUSA mygetch();

unsigned int
lock(hospital *H, int elevador)
{
	if (H->E[elevador].bloqueado == 0)
		return FALSE;
	else
		return TRUE;
}

unsigned int
elevador_pos(hospital *H, int elevador)
{
	return H->E[elevador].andar;
}

void
move_elevador(hospital *H, int elevador, int sentido)
{
	if (!lock(H, elevador)) {

		if ((sentido == DESCER) && (elevador_pos(H, elevador) < ANDARES))
			H->E[elevador].andar--;
		if ((sentido == SUBIR) /* && (elevador_pos(H, elevador) >= 0) */ )
			H->E[elevador].andar++;
	}
}

void
elevador_up(hospital *H, int elevador)
{
	move_elevador(H, elevador, SUBIR);
}

void
elevador_down(hospital *H, int elevador)
{
	move_elevador(H, elevador, DESCER);
}

/* retorna o elevador mais próximo do andar passado como parametro */
int
elevador_mais_proximo(hospital *H, int andar)
{
	int i, elevador, tmp;

	/*
	 * aux recebe ANDARES+1 pq tem no maximo ANDARES andares, a distancia maior
	 * sendo no maximo ANDARES, ANDARES+1 eh um valor de inicializacao valido
	 */
	int aux = ANDARES + 1;

	for (i = 0; i < N_ELEVADORES; i++)
		tmp = MOD(andar - H->E[i].andar);
		if (tmp < aux && H->E[i].bloqueado == 0) {
			aux = tmp;
			elevador = i;
		}
	return elevador;
}

void
enche_elevador(hospital *H)
{
	int j, aux_andar;
	for (j = 0; j < N_ELEVADORES; j++) {

		aux_andar = H->E[j].andar;
		diminui_fila(H, aux_andar, 4);
	}
}

void
atualiza_hospital(hospital *H)
{
	int i;
	for (i = 0; i < ANDARES; i++) {

		atualiza_fila(&(H->A[i].F));

	}
}

void
inicia_andares(hospital *H)
{
	int i;
	for (i = 0; i < ANDARES; i++) {
		inicia_fila(&(H->A[i].F));
		H->A[i].usuarios = 0;
		H->A[i].espera_total = 0;
	}

	H->A[0].F.e_cont = 0;
	H->A[ANDARES - 1].F.e_cont = 0;

}

void
zera_prioridade(hospital *H)
{
	int i;
	for (i = 0; i < N_ELEVADORES; i++) {

		H->P[i].tempo_espera = -1;
		H->P[i].andar = 0;
	}
}

void
inicia_hospital(hospital *H)
{
	int i;
	inicia_andares(H);
	zera_prioridade(H);

	for (i = 0; i < N_ELEVADORES; i++) {

		H->E[i].bloqueado = 0;
		H->E[i].andar = 0;
	}
}

int
tempo_de_espera(hospital *H, int i)
{
	return H->A[i].F.ini->p.tempo_espera;
}

void
atualiza_prioridade(hospital *H, int tempo, int andar, int prioridade)
{
	int i;
	for (i = N_ELEVADORES - 1; i > prioridade; i--) {

		H->P[i].andar = H->P[i - 1].andar;
		H->P[i].tempo_espera = H->P[i - 1].tempo_espera;
	}
	H->P[prioridade].andar = andar;
	H->P[prioridade].tempo_espera = tempo;
}

void
determinar_prioridade(hospital *H)
{
	int aux_tempo;
	int i;

	zera_prioridade(H);

	for (i = 0; i < ANDARES; i++) {

		if (fila_tam(H, i) > 0) {

			aux_tempo = tempo_de_espera(H, i);

			if (aux_tempo > H->P[0].tempo_espera)
				atualiza_prioridade(H, aux_tempo, i, 0);
			else if (aux_tempo > H->P[1].tempo_espera)
				atualiza_prioridade(H, aux_tempo, i, 1);
			else if (aux_tempo > H->P[2].tempo_espera)
				atualiza_prioridade(H, aux_tempo, i, 2);

		}
	}
}

void
atualiza_elevador(hospital *H)
{
	int i;
	int pos;

	for (i = 0; i < N_ELEVADORES; i++) {

		pos = elevador_pos(H, i);
		if (pos < H->P[i].andar)
			elevador_up(H, i);
		else if (pos > H->P[i].andar)
			elevador_down(H, i);
	}
}

void
free_hospital(hospital *H)
{
	box *aux;
	int i;
	for (i = 0; i < ANDARES; i++) {

		aux = H->A[i].F.ini;
		while (aux != NULL) {
			H->A[i].F.ini = H->A[i].F.ini->prox;
			free(aux);
			aux = H->A[i].F.ini;
		}
		H->A[i].F.nfim = NULL;
	}
}

int
main(int argc, char *argv[])
{
	hospital H;
	int i, vezes;

	srand(time(0));
	inicia_hospital(&H);

	print_hospital(&H);
	PAUSA

	if (argc > 1)
		vezes = atoi(argv[1]);
	else
		vezes = 10;

	for (i = 0; i < vezes; i++) {

		atualiza_hospital(&H);
		print_hospital(&H);
		printf("Chegou pessoas\n");
		printf("Ciclos: %i\n", i);
		PAUSA determinar_prioridade(&H);
		atualiza_elevador(&H);
		print_hospital(&H);
		printf("Elevadores se movem conforme prioridade\n");
		printf("Ciclos: %i\n", i);
		PAUSA enche_elevador(&H);
		print_hospital(&H);
		printf("Elevadores levam as pessoas\n");
		PAUSA printf("Ciclos: %i\n", i);
	}

	print_hospital(&H);
	print_relatorio(&H);
	free_hospital(&H);
	return 0;
}
