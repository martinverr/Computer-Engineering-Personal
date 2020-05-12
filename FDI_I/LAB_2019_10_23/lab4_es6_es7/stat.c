#include "stat.h"
#include <stdlib.h>

double media(double*x, unsigned int n) {
	if (n == 0)
		return 0.;
	double media = 0.;
	for (unsigned int i = 0; i < n; i++)
	{
		media += x[i];
	}
	return media / n;
}

double varianza(double *x, unsigned int n) {
	if (n < 2)
		return 0.;
	double varianza = 0;
	double media_x = media(x, n);
	for (unsigned int i = 0; i < n; i++) {
		varianza += (media_x - x[i])*(media_x - x[i]);
	}
	return varianza / n;
}
