/* vim: set ts=4 sw=4: */

#include "fila.h"
#include "aux.h"

/* retorna um novo paciente em um determinado estado */
box *
novo_paciente(char estado)
{
	box *aux;
	aux = (box *) malloc(sizeof(box));
	aux->p.estado = estado;
	aux->p.tempo_espera = 0;
	aux->prox = NULL;
	aux->ant = NULL;
	return aux;
}

void
insere_nfim(fila *F, char c)
{
	box *new_box = novo_paciente(c);

	if (!F->ini) {
		F->ini = new_box;
		F->nfim = new_box;
	} else {
		if (F->nfim) {
			new_box->ant = F->nfim;
			F->nfim->prox = new_box;
			F->nfim = new_box;

		} else { /* (!F->nfim) */

			if (F->efim) {
				new_box->ant = F->efim;
				F->efim->prox = new_box;
				F->nfim = new_box;
			}
		}
	}

	F->tam++;
	if (F->tam > F->max)
		F->max = F->tam; /* guarda o maior tamanho da fila */
}

void
insere_efim(fila *F, char c)
{
	box *new_box = novo_paciente(c);

	if (!F->ini) {
		F->ini = new_box;
		F->efim = new_box;
	} else {
		if (F->efim) { /* e <-> e <-> e <-> x */

			if (F->nfim) { /* e <-> e <-> n <-> n <-> || */

				new_box->ant = F->efim;
				new_box->prox = F->efim->prox;
				F->efim->prox = new_box;
				F->efim->prox->ant = new_box; /* 1 dia depois */
				F->efim = new_box;

			} else { /* (!F->nfim) e <-> e <-> e <-> || */

				new_box->ant = F->efim;
				F->efim->prox = new_box;
				F->efim = new_box;
			}

		} else { /* (!F->efim) e <-> || */

			if (F->nfim) { /* n <-> n <-> n || */

				/* insere no começo */
				F->ini->ant = new_box;
				new_box->prox = F->ini;
				F->ini = new_box;
			} else { /* (!F->nfim) mesma situacao do primeiro if (!F->ini) */

				F->ini = new_box;
				F->efim = new_box;
			}
		}
	}
	F->tam++;

	if (F->tam > F->max)
		F->max = F->tam; /* guarda o maior tamanho da fila */
}

/* insere na fila um paciente */
int
chega_paciente(fila *F, char c)
{
	if (c == 'n')
		insere_nfim(F, c);
	else if (c == 'e')
		insere_efim(F, c);

	return 0;
}

void
diminui_fila(hospital *H, int andar, int n)
{
	fila *F = &(H->A[andar].F);
	int i;

	for (i = 0; i < n; i++) {

		if (F->ini) {

			if (F->ini == F->nfim)
				F->nfim = NULL;
			if (F->ini == F->efim)
				F->efim = NULL;

			H->A[andar].espera_total += F->ini->p.tempo_espera;
			H->A[andar].usuarios++;

			if (F->ini->prox) {
				F->ini = F->ini->prox;
				free(F->ini->ant);
				F->ini->ant = NULL;
				F->tam--;

			} else {
				free(F->ini);
				F->ini = NULL;
				F->tam--;
			}
		}
	}
}

int
fila_tam(hospital *H, int andar)
{
	return H->A[andar].F.tam;
}

void
incrementa_tempo_de_espera(fila * F)
{
	box *aux = F->ini;
	while (aux != NULL) {
		aux->p.tempo_espera++;
		aux = aux->prox;
	}
}

int
eh_emergencia(fila * F)
{
	if (F->e_cont == 10) {
		F->e_cont = 0;
		F->e = 0;
		return FALSE;
	} else {
		F->e_cont++;
		if ((F->e < 3) && (myrandom(10) < 8)) {
			F->e++;
			return TRUE;
		}
	}
	return FALSE;
}

int
andar_emergencial(fila * F)
{
	if (F->e_cont != -1)
		return TRUE;
	return FALSE;
}

int
atualiza_fila(fila * F)
{
	int i;
	int aux = myrandom(CHEGAM);

	incrementa_tempo_de_espera(F);

	for (i = 0; i < aux; i++)

		if (andar_emergencial(F) && eh_emergencia(F))
			chega_paciente(F, 'e');
		else
			chega_paciente(F, 'n');

	return aux;
}

/* imprime na tela a fila */
void
print_fila(fila *F)
{
	box *aux = F->ini;

	printf("\r\t\t");
	while (aux != NULL) {
		printf("%c, ", aux->p.estado);
		aux = aux->prox;
	}
	printf("\n");
}

void
print_fila_prioridade(fila *F)
{
	box *aux = F->ini;

	printf("\r\t\t");
	while (aux != NULL) {
		printf("%i, ", aux->p.tempo_espera);
		aux = aux->prox;
	}
	printf("\n");
}

/* imprime na tela a fila */
void
print_fila_contrario(fila *F)
{
	box *aux = F->nfim;
	while (aux != NULL) {
		printf("%c, ", aux->p.estado);
		aux = aux->ant;
	}
	printf("\n");
}

void
inicia_fila(fila *F)
{
	F->e = 0;
	F->e_cont = -1;
	F->max = 0;
	F->tam = 0;
	F->obito = 0;
	F->ini = NULL;
	F->efim = NULL;
	F->nfim = NULL;
}
