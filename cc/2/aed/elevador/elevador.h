#ifndef _ELEVADOR_H
#define _ELEVADOR_H

/* elevador mais próximo do andar passado como parametro */
int elevador_mais_proximo(hospital *H, int andar);

/* retorna TRUE se o elevador estiver bloqueado */
unsigned int lock(hospital *H, int elevador);

/* retorna qual o andar do elevador */
unsigned int pos(hospital *H, int elevador);

/* conforme sentido, sobe ou desce o elevador */
void atualiza_elevador(hospital *H, int elevador, int sentido);

/* sobe o elevador em um andar */
void elevador_up(hospital *H, int elevador);

/* desce o elevador em um andar */
void elevador_down(hospital *H, int elevador);

#endif
