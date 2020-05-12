#if !defined FIRE_SYM_H
#define FIRE_SYM_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct forest {
	size_t rows, cols;
	char *data;
};

extern void propagate_fire(const struct forest *f);



#endif