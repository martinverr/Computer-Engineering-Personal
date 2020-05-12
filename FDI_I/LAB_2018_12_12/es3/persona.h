#if !defined PERSONA_H
#define PERSONA_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct persona {
	char *nome;
	uint16_t eta;
	char sesso;
};

extern bool persona_scrivi(const struct persona *p, FILE *f);

#endif