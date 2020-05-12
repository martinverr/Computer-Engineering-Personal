#include <stdlib.h>
#include "stat.h"

/*
double media(double*x, unsigned int n){
	if (n == 0)
		return 0.;
	double media = 0.;
	for (unsigned int i = 0; i < n; i++)
	{
		media += x[i];
	}
	return media/n;
}

double varianza(double *x, unsigned int n) {
		if (n < 2)
			return 0.;
		double varianza = 0;
		double media_x = media(x,n);
		for (unsigned int i = 0; i < n; i++) {
			varianza += (media_x - x[i])*(media_x - x[i]);
		}
		return varianza / n;
	}
	*/

	int main(void) {
		unsigned int n = 4;
		double *x = malloc(n * sizeof(double));
		x[0] = 1;
		x[1] = 7;
		x[2] = 2;
		x[3] = 5;
		double media_x = media(x, n);
		double varianza_x = varianza(x, n);
		return 0;
}