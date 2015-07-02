/* vim: set ts=4 sw=4: */

#include <stdlib.h>

/*
 * Retorna um número randomico de 0 a n
 * necessario a chamada previa: srand(time(0));
 */
int
myrandom(int n)
{
	return ((int) ((float) n * rand() / (RAND_MAX + 1.0)));
}
