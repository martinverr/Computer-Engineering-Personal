#if !defined PREZZOTOTALE_H
#define PREZZOTOTALE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct articolo {
	char nome[11];
	int prezzo;
} articolo;

extern void TrovaArticoli(const articolo* a, size_t a_size, int sum);
#endif