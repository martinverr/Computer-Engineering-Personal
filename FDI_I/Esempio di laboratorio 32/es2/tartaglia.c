#include <stdio.h>
#include <stdlib.h>

unsigned int *tartaglia(unsigned int *v, size_t n) {
	if (n == 0) {
		unsigned int *res = malloc(sizeof(int));
		res[0]=1;
		return res;
	}
	if (n == 1) {
		unsigned int *res=malloc(sizeof(int)*2);
		res[0] = 1;
		res[1] = 1;
		return res;
	}

	unsigned int *res = malloc((n+1)*sizeof(int));
	res[0] = 1;
	res[n] = 1;
	for (unsigned int i = 1; i < n; i++) {
		res[i] = v[i] + v[i - 1];
	}


	return res;
}

int main(void) {
	unsigned int rigaNmeno1[] = { 1,5,10,10,5,1 };
	unsigned int *tart = tartaglia(rigaNmeno1, 6);

	return 0;
}