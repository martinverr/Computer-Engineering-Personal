#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void stampa_cornicetta(const char * s) {
	printf("/");
	printf("-");
	for(size_t i = 0; i<strlen(s); i++)
		printf("-");
	printf("-");
	printf("\\\n");

	printf("| ");
	printf("%s", s);
	printf(" |\n");

	printf("\\");
	printf("-");
	for (size_t i = 0; i < strlen(s); i++)
		printf("-");
	printf("-");
	printf("/\n");
}

//int main(void) {
//	char parola[] = { "Diocane" };
//	stampa_cornicetta(parola);
//	return 0;
//}