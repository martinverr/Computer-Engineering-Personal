#include "libri.h"
int main(void) {
	FILE *f = fopen("prova", "wb");
	uint16_t *anni = malloc(3 * sizeof(uint16_t));
	anni[0] = 2001;
	anni[1] = 2002;
	anni[2] = 0;
	struct libro esempio = { "Geometria", anni };
	libro_scrivi(&esempio, f);

	return 0;
}