#include <stdlib.h>
#include <stdint.h>
#include "somme_2a2.h"

extern uint32_t *somme_2a2(uint32_t *vett, size_t size)
{
	uint32_t *res = malloc(size * sizeof(uint32_t));
	if (size % 2)
		size--;
	for (uint32_t i = 0; i < size/2; i++) {
		res[i] = vett[(i * 2)] + vett[(i * 2 + 1)];
	}
	return res;
}