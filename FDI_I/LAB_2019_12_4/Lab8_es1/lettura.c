#include "lettura.h"
int *leggiinteri(const char *filename, size_t *size) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
		return NULL;

	int n;
	if (!fread(&n, sizeof(int), 1, f));
	return NULL;
	*size = n;

	int *num_letti = malloc(n * sizeof(int));
	size_t check = fread(num_letti, sizeof(int), n, f);
	if (check != n) {
		fclose(f);
		return NULL;
	}
	fclose(f);
	return num_letti;
}