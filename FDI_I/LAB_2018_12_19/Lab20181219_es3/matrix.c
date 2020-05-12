#include "matrix.h"

void swap(double *a, double *b) {
	double tempa = *a;
	*a = *b;
	*b = tempa;
}

struct matrix *scambia_diagonali(const struct matrix *m) {
	//check if m is a correct matrix
	if (m == NULL || m->data == NULL || m->cols != m->rows)
		return NULL;

	//create matrix res
	struct matrix *res = malloc(sizeof(struct matrix));
	res->rows = m->rows;
	res->cols = m->cols;
	double *dataRes = malloc(res->rows*res->cols*sizeof(double));
	res->data = dataRes;

	//copy
	for (size_t r = 0; r < res->rows; r++) {
		for (size_t c = 0; c < res->cols; c++) {
				res->data[r*res->cols + c] = m->data[r*m->cols + c];
		}
	}

	//swap of diag
	for (size_t r = 0; r < res->rows; r++) {
		for (size_t c = 0; c < res->cols; c++) {
			if (c == r)
			{
				swap(	
					&(res->data[r*res->cols + c]),
					&(res->data[r*res->cols + (res->cols - c - 1)])	
					);
			}
		}
	}

	return res;
}