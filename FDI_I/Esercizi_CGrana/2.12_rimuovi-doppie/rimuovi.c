#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int rimuovidoppie(const char *filein, const char * fileout) {
	FILE *fIn = fopen(filein, "r");
	FILE *fOut = fopen(fileout, "w");
	int this_char, previous_char = -2;	//-2 not a char
	if (fIn == NULL)
		return 0;
	if (fOut == NULL)
		return 0;

	while (1) {
		this_char = fgetc(fIn);
		if (this_char == EOF)
			break;

		if (this_char != previous_char) {
			putc(this_char, fOut);
			previous_char = this_char;
		}

	}

	fclose(fIn);
	fclose(fOut);
	return 1;
}

//int main(void) {
//	char sorgente[] = { "a.txt" };
//	char destinazione[] = { "b.txt" };
//	rimuovidoppie(sorgente, destinazione);
//
//	return 0;
//}