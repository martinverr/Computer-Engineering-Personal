#include <stdio.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

bool scrivi_intero(const char *filename, int i) {
	FILE *f = fopen(filename, "w");
	if (f != NULL) {
		return 0;
	}

	fprintf(f, "%d", i);

	return 1;
}

int main(void) {
	char nome_file[] = { "Dio bello" };
	int numero = 5;

	scrivi_intero(nome_file, numero);


	return 0;
}