#include "funzione.h"

unsigned long long fattn(unsigned int n) {
	unsigned long long fattn = 1;

	while (n > 1) {
		fattn *= n;
		n--;
	}
	return fattn;
}

double pot(double b, unsigned int exp) {
	double res = 1;
	if (exp == 0)
		return res;

	for (exp; exp > 0; exp--) {
		res *= b;
	}

	return res;
}

double seno_iperbolico(double x) {
	double res = 0, res_prec;
	double err=1;
	unsigned int n = 0;

	while (err > 0.01) {

		res_prec = res;
		res += pot(x, 2 * n + 1) / fattn(2 * n + 1);

		if (res > res_prec)
			err = res - res_prec;
		else
			err = res_prec - res;

		n++;
	}

	return res;
}