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
	double a[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
	size_t i, n = 10;

	for (i = 0; i < n; ++i) {
		double d = a[i];
		potenza(&d, i);
		a[i] = d;
	}
 return 0;

}