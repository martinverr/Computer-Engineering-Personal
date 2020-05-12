#if !defined MATRIX_H
#define MATRIX_H

#include <stdlib.h>
struct matrix {
	size_t rows, cols;
	double *data;
};
extern struct matrix *mat_transpose(const struct matrix *mat);

#endif