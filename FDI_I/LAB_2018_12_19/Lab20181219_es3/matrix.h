#if !defined MATRIX_H
#define MATRIX_H

#include <stdlib.h>

extern struct matrix *scambia_diagonali(const struct matrix *m);

struct matrix {
	size_t rows, cols;
	double *data;
};

#endif
