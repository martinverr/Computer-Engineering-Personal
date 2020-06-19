#include "newton.h"

// risolvi polinomio f(x) data x
double f(const polinomio * p, double x) {
	double res = 0;
	for (size_t i = 0; i < p->size; i++)
		res += p->coeffs[i] * pow(x, i);
	return res;
}

// risolvi zero di un polinomio con algoritmo di Newton
double NewtonRec(const polinomio *p, const polinomio *d, double xn, double t, 
				int max_iter, int passo, double prec) {
	if (fabs(xn - prec) <= t)
		return xn;
	if (max_iter > 1 && max_iter == passo)
		return xn;

	double xnSucc = xn - f(p, xn) / f(d, xn);
	return NewtonRec(p, d, xnSucc, t, max_iter, passo+1, xn);
}

// chiama NewtonRec
double Newton(const polinomio *p, const polinomio *d, double xn, double t, int max_iter) {
	return NewtonRec(p, d, xn, t, max_iter, 0, 1000);
}

/*
// f() risolve le equazioni correttamente
int main(void) {
	int coef1[] = { 5,0,1 };
	polinomio pol1 = { coef1, 3 };
	double res1 = f(&pol1, 4); //21

	return 0;
}
*/