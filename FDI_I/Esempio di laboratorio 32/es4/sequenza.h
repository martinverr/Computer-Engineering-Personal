#if !defined SEQUENZA_H
#define SEQUENZA_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
struct seq {
	size_t len;
	uint16_t *values;
};
extern bool seq_load(const char *filename, struct seq *s);

#endif