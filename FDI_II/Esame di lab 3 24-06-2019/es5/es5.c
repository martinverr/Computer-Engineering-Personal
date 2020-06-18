#include "sciatori.h"

void swap(double *a, double *b) {
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort(double *v, int size) {

}

sciatore * Accoppia(double *altezze, double * lunghezze, int size) {
	if (size == 0)
		return NULL;
	sciatore * res = malloc(sizeof(sciatore) * size);

	// sort non funzionante
	for(int j = 0; j<size; j++)
		for (int k = 0; k < size; k++)
			if ((altezze[j] - lunghezze[k]) > (altezze[j] - lunghezze[j]))
				swap(lunghezze + k, lunghezze + j);

	for (int i = 0; i < size; i++) {
		res[i].a = altezze[i];
		res[i].l = lunghezze[i];
	}


	return res;
}