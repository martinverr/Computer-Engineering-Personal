#include "matrix.h"

int main(void) {
	FILE *f = fopen("A.txt", "r");
	struct matrix *A = malloc(sizeof(struct matrix));
	matrix_read(A, f);

	return 0;
}