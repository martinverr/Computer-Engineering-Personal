#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void stampa_tavola_pitagorica(FILE *f, unsigned int n) {
	if (f == NULL)
		exit(EXIT_FAILURE);
	for (unsigned int riga = 1; riga <= n; riga++) {
		for (unsigned int colonna = 1; colonna <= n; colonna++) {
			fprintf(f, "%d\t", riga*colonna);
		}
		fprintf(f, "\n");
	}



}

int main(void) {
	FILE *f=fopen("prova.txt", "w");
	//non controllo, main non mio
	stampa_tavola_pitagorica(f, 5);

	return 0;
}