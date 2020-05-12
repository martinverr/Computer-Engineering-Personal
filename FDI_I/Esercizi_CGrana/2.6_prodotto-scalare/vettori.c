#include <stdlib.h>
#include "vettori.h"

double prodotto_scalare(const double *x, const double *y, size_t n) {
	double res = 0;
	
	if (x == NULL || y == NULL || n == 0)
		return 0;

	for (size_t i = 0; i < n; i++) {
		res += (x[i]) * (y[i]);
	}
	return res;
}

/*
int main(void) {
	size_t n = 4;
	double v[4] = { 5,3,1 };
	double w[4] = { 1,2,3,7 };
	double res = prodotto_scalare(v, w, n);
	return 0;
}
*/