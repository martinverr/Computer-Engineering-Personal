#include "matrix.h"
struct matrix *mat_constructor( int rows, int cols, struct matrix *m )
{
	m->rows = rows;
	m->cols = cols;
	m->data = malloc(rows*cols * sizeof(double));
	return m;
}

struct matrix *new_matrix(size_t rows, size_t cols) {
	
	return mat_constructor(rows, cols, malloc(sizeof(struct matrix)));
}

struct matrix *mat_transpose(const struct matrix *mat) {
	int i = 0;
	struct matrix *tA = new_matrix(mat->cols, mat->rows);
	for (size_t r = 0; r < mat->rows; r++) {
		for (size_t c = 0; c < mat->cols; c++) {
			tA->data[c*mat->rows+r] = mat->data[r*mat->cols + c];
			i++;
		}
	}
	return tA;
}

int main(void) {
	double datimat1[3 * 2] = {	1,2,3,
								4,5,6,	};
	struct matrix A = { 3,2, datimat1 };

	struct matrix *tA = mat_transpose(&A);

}