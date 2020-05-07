#if !defined TORRECARTONI_H
#define TORRECARTONI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	unsigned p; // Peso
	unsigned a; // Altezza
	unsigned l; // Limite
}cartone;

extern void TorreCartoni(cartone *c, int n);

#endif