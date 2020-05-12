#include "lettura.h"
double * leggidouble(const char *filename, size_t *size) {

	//open file
	FILE *f = fopen(filename, "r");
	if (f == NULL)
		return NULL;

	//number of elements
	double temp;
	int numOfElem = 0;
	while (1) {
		if (fscanf(f, "%lf", &temp) == EOF)
			break;
		numOfElem++;
	}
	if (numOfElem == 0) {
		fclose(f);
		return NULL;
	}
	rewind(f);

	//alloc and read elements
	double *elements = malloc(numOfElem * sizeof(double));	//
	int count=0;
	while (1) {
		if (fscanf(f, "%lf", elements + count) == EOF)
			break;
		count++;
	}
	fclose(f);

	//result
	*size = numOfElem;
	return elements;
}