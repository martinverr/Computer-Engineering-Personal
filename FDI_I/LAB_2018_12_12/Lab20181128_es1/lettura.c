#include "lettura.h"

int *leggiinteri(const char *filename, size_t *size) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		fclose(f);
		return NULL;
	}

	//set n
	int n = 0;
	size_t check = fread(&n, 4, 1, f);
	if (check != 1)
	{
		fclose(f);
		return NULL;
	}
	if (n == 0) {
		fclose(f);
		return NULL;
	}
	*size = n;

	int * nletti = malloc(n * sizeof(int));
	check = fread(nletti, 4, n, f);
	if (check != n) {
		fclose(f);
		return NULL;
	}

	fclose(f);
	return nletti;
}

int main(void) {
	size_t size1, size2, size3, size4;
	int *dati1=	leggiinteri("dati1.bin", &size1);
	int *dati2=	leggiinteri("dati2.bin", &size2);
	leggiinteri("dati3.bin", &size3);
	leggiinteri("dati4.bin", &size4);
	return 0;
}
