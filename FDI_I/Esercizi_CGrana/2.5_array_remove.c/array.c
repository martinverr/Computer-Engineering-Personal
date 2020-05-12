#include <stdlib.h>
#include "array.h"

void array_remove(double *arr, size_t *pn, size_t pos) {
	if (pos < (*pn - 1))
	{
		for (pos; pos < *pn - 1; pos++) {
			arr[pos] = arr[pos + 1];
		}

		*pn--;
		arr[pos] = 0;
	}
}

/*
int main(void) {
	size_t pn = 5, pos = 3;
	double v[5] = {0,2,4,6,8};

	array_remove(v, &pn, pos);
	return 0;
}
*/