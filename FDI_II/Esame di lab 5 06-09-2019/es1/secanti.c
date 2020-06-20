#include "secanti.h"
double resolveFx(const polinomio * p, double x) {
	double res = 0;
	for (size_t i = 0; i < p->size; i++)
		res += p->coeffs[i] * pow(x, i);
	return res;
}

double resolveSecanti(const polinomio *p, double x0, double x1, double t, int max_iter, int iter) {
	if (fabs(x1 - x0) < t)
		return x1;
	if (iter == max_iter)
		return x1;

	double x2;
	//x_(n + 1) = x_n - (x_n - x_(n - 1)) / (f(x_n) - f(x_(n - 1)))? f(x_n)
	x2 = x1 - (x1 - x0) / (resolveFx(p, x1) - resolveFx(p, x0)) * resolveFx(p, x1);

	return resolveSecanti(p, x1, x2, t, max_iter, iter + 1);
}

double Secanti(const polinomio *p, double x0, double x1, double t, int max_iter) {
	double res = 0;
	
	
	return resolveSecanti(p, x0, x1, t, max_iter, 0);
}