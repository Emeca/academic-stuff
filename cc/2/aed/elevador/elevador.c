/* vim: set ts=4 sw=4: */

#include "elevador.h"

/*
 * retorna o elevamor mais próximo do andar passado como parametro
 */
int
elevador_mais_proximo(hospital *H, int andar)
{
	/*
	 * aux recebe 6 pq tem no maximo 5 andares
	 * a distancia maior sendo no maximo 5, 6 eh um valor de inicial valido
	 */
	int i, elevador, tmp, aux = 6;

	for (i = 0; i < N_ELEVADORES; i++)
		if ((tmp = MOD(andar - H->E[i].andar < aux))
			&& (H->E[i].bloqueado == 0)) {
			aux = tmp;
			elevador = i;
		}
	return elevador;
}

unsigned int
lock(hospital *H, int elevador)
{
	if (H->E[elevador].bloqueado == 0)
		return FALSE;
	else
		return TRUE;
}

unsigned int
pos(hospital *H, int elevador)
{
	return H->E[elevador].andar;
}

void
atualiza_elevador(hospital *H, int elevador, int sentido)
{
	if (!lock(H, elevador)) {

		if ((sentido == DESCER) && (pos(H, elevador) < ANDARES))
			H->E[elevador].andar--;
		if ((sentido == SUBIR) && (pos(H, elevador) >= 0))
			H->E[elevador].andar++;
	}
}

void
elevador_up(hospital *H, int elevador)
{
	atualiza_elevador(H, elevador, SUBIR);
}

void
elevador_down(hospital *H, int elevador)
{
	atualiza_elevador(H, elevador, DESCER);
}
