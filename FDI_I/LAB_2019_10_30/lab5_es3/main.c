#include <stdlib.h>

void potenza(double *d, size_t exp) {
	size_t i;
	double res = 1;
	for (i = 0; i < exp; i++) {
		res *= *d;
	}
	*d = res;
}

int main(void) {
	double a[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	size_t i, n = 10;

	for (i = 0; i < n; ++i) {

		a[i]=potenza(a[i], i);
	}
	return 0;

}