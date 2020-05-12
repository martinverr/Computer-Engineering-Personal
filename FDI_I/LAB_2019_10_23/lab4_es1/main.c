#include <stdlib.h>
#include <stdint.h>

void raddoppia_tre(uint32_t*v) {
	v[0] *= 2;
	v[1] *= 2;
	v[2] *= 2;

}

int main(void) {
	uint32_t *v = malloc(3 * sizeof(uint32_t));
	v[0] = 12;
	v[1] = 59;
	v[2] = 83;
	raddoppia_tre(&v[0]);
	free(v);
	return 0;
}