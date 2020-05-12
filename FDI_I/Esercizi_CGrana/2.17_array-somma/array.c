#include "array.h"

double *array_somma(const double *arr1, const double *arr2, size_t n) {
	if (arr1 == NULL || arr2 == NULL || n <= 0)
		return NULL;

	double *sum = malloc(n * sizeof(double));

	for (size_t i = 0; i < n; i++) {
		sum[i] = arr1[i] + arr2[i];
	}


	return sum;
}