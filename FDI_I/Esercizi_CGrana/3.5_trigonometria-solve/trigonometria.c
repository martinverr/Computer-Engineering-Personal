#include <math.h>

double solve(double a) {
	double err = 1;
	double x = 0, xprec=0;

	while (err < 1e-10) {
		x = xprec + (cos(xprec) - a * xprec) / (sin(xprec) + a);

		err = fabs(x - xprec);
	}

	return x;
}