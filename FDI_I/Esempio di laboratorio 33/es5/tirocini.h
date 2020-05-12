#if !defined TIROCINI_H
#define TIROCINI_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tirocinio {
	char *nome;
	char *azienda1;
	char *azienda2;
	char *azienda3;
};

extern bool tirocinio_load(FILE *f, struct tirocinio *t);

#endif