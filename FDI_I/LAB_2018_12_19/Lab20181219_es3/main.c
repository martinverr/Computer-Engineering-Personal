#include "matrix.h"
int main(void) {
	double dataA[3 * 3] = {
		1, 2, 3,
		4, 5, 6,
		7, 8, 9,
	};
	struct matrix A = { 3, 3, dataA };

	struct matrix *B = scambia_diagonali(&A);

	return 0;
}