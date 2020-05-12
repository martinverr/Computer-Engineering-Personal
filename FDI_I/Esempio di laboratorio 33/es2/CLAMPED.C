#include <stdlib.h>


int *clamped(const int *v, size_t n, int min, int max) {
	if (min > max || n == 0 || v == NULL)
		return NULL;

	int *res = malloc(n * sizeof(int));

	for (size_t i = 0; i < n; i++) {
		res[i] = v[i];
		if (v[i] < min)
			res[i] = min;
		if (v[i] > max)
			res[i] = max;

	}

	return res;
}

int main(void) {
	int v[] = { 0,9,3,25,4 };
	int *res = clamped(v, 5, 2, 10);

	return 0;
}