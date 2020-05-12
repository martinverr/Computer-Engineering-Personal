#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void stampa_cornicetta(const char *s) {
	size_t numero_trattini = strlen(s);
	char *trattini = malloc(numero_trattini+1);
	trattini[numero_trattini] = 0;
	memset(trattini, '-', numero_trattini);

	printf("/-%s-\\\n", trattini);
	printf("| %s |\n", s);
	printf("\\-%s-/\n", trattini);
	free(trattini);
}

int main(void) {
	char s1[] = {"ciao"};
	stampa_cornicetta(s1);
}