#include "lettura.h"

int *leggiinteri2(const char *filename, size_t *size) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		fclose(f);
		return NULL;
	}

	//set n
	int n = 0;
	int temp;
	while (1) {
		if (fread(&temp, 4, 1, f))
			n++;
		else
			break;
	}
	rewind(f);

	if (n == 0) {
		fclose(f);
		return NULL;
	}
	*size = n;

	int * nletti = malloc(n * sizeof(int));
	size_t check = fread(nletti, 4, n, f);
	if (check != n) {
		fclose(f);
		return NULL;
	}

	fclose(f);
	return nletti;
}

int main(void) {
	size_t size1, size2, size3, size4;
	int *dati1 = leggiinteri2("dati1.bin", &size1);
	int *dati2 = leggiinteri2("dati2.bin", &size2);
	leggiinteri2("dati3.bin", &size3);
	leggiinteri2("dati4.bin", &size4);
	return 0;
}
