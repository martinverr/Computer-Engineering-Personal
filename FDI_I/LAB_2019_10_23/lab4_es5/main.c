#include <stdint.h>
#include <stdlib.h>

extern uint32_t somme_2a2(uint32_t * vett, size_t n) {
	if (n % 2)
		n = n - 1;
	uint32_t * somme = malloc(n * sizeof(uint32_t) / 2);
	for (uint32_t i = 0, j=0; i < n; i++)
	{
		somme[i]=vett[j]+vett[j+1];
		j += 2;
	}
	
	return somme;
}

int main(void) {
	size_t n = 6;
	uint32_t *v = malloc(n * sizeof(uint32_t));
	v[0] = 3;
	v[1] = 87;
	v[2] = 5;
	v[0] = 7;
	v[1] = 12;
	v[2] = 9;
	uint32_t *somme = somme_2a2(v, n);
	free(v);
	free(somme);

	return 0;
}