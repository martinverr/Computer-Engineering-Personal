#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
void raddoppia_tre(uint32_t*x, size_t n) {
	for (size_t i = 0; i < n; i++) {
		x[i] *= 2;
	}
}

int main(void) {
	size_t n = 3;
	uint32_t *v = malloc(3 * sizeof(uint32_t));
	v[0] = 12;
	v[1] = 59;
	v[2] = 83;
	raddoppia_tre(v, n);
	visualizza_array(v, n);
	free(v);
	return 0;
}