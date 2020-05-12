#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void stampa_onde(FILE *f, int n) {
	if (n == 0) {
		fprintf(f, "\n\n\n");
	}

	fprintf(f, " ");
	for (int i=0; i<n; i++)
		fprintf(f, " _    ");
	fprintf(f, "\n");

	fprintf(f, " ");
	for (int i = 0; i < n; i++)
		fprintf(f, "/ \\   ");
	fprintf(f, "\n");

	fprintf(f, " ");
	for (int i = 0; i < n; i++)
		fprintf(f, "   \\_/");
	fprintf(f, "\n");

}

//int main(void) {
//	FILE *f = fopen("prova.txt", "w");
//	stampa_onde(f, 3);
//	stampa_onde(f, 0);
//	stampa_onde(f, 10);
//	return 0;
//}