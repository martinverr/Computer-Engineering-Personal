#include "matrix.h"

struct bmatrix *mat_boolean(const struct matrix *m, double rhs, enum comparisons cmp) {
	if (m == NULL)
		return NULL;
	struct bmatrix *res = malloc(sizeof(struct bmatrix));
	bool *data = malloc(m->cols*m->rows * sizeof(bool));
	for (size_t i = 0; i < m->cols*m->rows; i++) {
		data[i] = m->data[i];
	}
	res->cols = m->cols;
	res->rows = m->rows;
	res->data = data;

	for (size_t i = 0; i < m->rows*m->cols; i++) {
		switch (cmp) {
			case LT: res->data[i] = m->data[i] < rhs; break;
			case LE: res->data[i] = m->data[i] <= rhs; break;
			case EQ: res->data[i] = m->data[i] == rhs; break;
			case NE: res->data[i] = m->data[i] != rhs; break;
			case GE: res->data[i] = m->data[i] >= rhs; break;
			case GT: res->data[i] = m->data[i] > rhs; break;
		}
	}

	return res;
}

int main(void) {

	double data[] = {
		1, 2, 3,
		4, 5, 6,
		7, 8, 9,
	};
	struct matrix A = { 3,3,data };
	struct bmatrix *B = mat_boolean(&A, 5, GE);


	return 0;
}