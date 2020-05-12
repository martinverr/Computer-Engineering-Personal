#include <stdint.h>
#include <stdlib.h>

extern void iota(uint32_t * x, size_t n) {
	for (uint32_t i = 0; i < n; i++) {
		x[i] = i;
	}
}

int main(void) {
	size_t n = 3;
	uint32_t *v = malloc(n * sizeof(uint32_t));
	iota(v, n);
/*	int v0 = v[0];
	int v1 = v[1];
	int v2 = v[2];
*/
	return 0;
}