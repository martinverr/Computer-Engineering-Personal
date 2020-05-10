#if !defined GIOIELLI_H
#define GIOIELLI_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int codice;
	float peso;
	float prezzo;
} Gioiello;

extern Gioiello* Gioielli(const char* filename, float b, int *ret_size);

#endif