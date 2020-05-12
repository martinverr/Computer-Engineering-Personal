#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

unsigned int conta_righe(FILE *f) {
	unsigned int righe=1;
	int c;
	while (1) {
		c = fgetc(f);
		if (c == EOF)
			break;
		if (c == '\n')
			righe++;
	}
	return righe;
}