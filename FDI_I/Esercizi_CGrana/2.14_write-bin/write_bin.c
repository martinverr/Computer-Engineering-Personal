#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void write_bin(double* values, size_t n, FILE *f) {
	if (n != 0 || values != NULL) {
		size_t check = fwrite(values, sizeof(double), n, f);
		if (check != n)
			exit(0);
	}
}

int main(void) {
	double numeri[4] = {3.0, 75.0, 1, 0};
	FILE *f=fopen("prova", "%wb");
	if (f == NULL)
		return -1;
	write_bin(numeri, 4, f);

	return 0;
}