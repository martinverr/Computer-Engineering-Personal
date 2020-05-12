#include "matrix.h"


struct matrix *mat_permute_rows(const struct matrix *m, const size_t *p) {
	struct matrix *res = malloc(sizeof(struct matrix));
	res->cols = m->cols;
	res->rows = m->rows;
	double *dataRes = malloc(sizeof(double) * res->cols * res->rows);
	res->data = dataRes;

	for (size_t rows = 0; rows < res->rows; rows++) {
		for (size_t cols = 0; cols < res->cols; cols++) {
			res->data[rows*m->cols + cols] = m->data[p[rows]*m->cols+cols];
		}
	}

	return res;
}

int main(void){
	size_t perm[] = {2,1,0};
	double data[] = {
		1, 2, 3,
		4, 5, 6,
		7, 8, 9, };
	struct matrix A = { 3, 3, data };
	struct matrix *Apermutato = mat_permute_rows(&A, perm);
	return 0;
}