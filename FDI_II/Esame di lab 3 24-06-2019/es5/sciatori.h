#if !defined SCIATORI_H
#define SCIATORI_H

#include <stdlib.h>
typedef struct sciatore {
	double a;
	double l;
}sciatore;

extern sciatore * Accoppia(double *altezze, double * lunghezze, int size);

#endif