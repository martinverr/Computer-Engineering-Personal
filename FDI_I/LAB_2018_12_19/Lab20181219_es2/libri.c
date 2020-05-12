#include "libri.h"

int nAnni(uint16_t* anni) {
	int count = 0;

	for (count; anni[count] != 0; count++) {
	}

	return count+1;
}

bool libro_scrivi(const struct libro *p, FILE *f) {
	int n = nAnni(p->anni_ristampe);

	size_t check = fwrite(p->titolo, 1, strlen(p->titolo), f);
	if (check != strlen(p->titolo))
		return false;
	fputc('\0', f);
	check = fwrite(p->anni_ristampe, sizeof(uint16_t), n, f);
	if (check != n)
		return false;

	return 1;
}