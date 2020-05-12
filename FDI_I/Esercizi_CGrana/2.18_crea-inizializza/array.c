#include <stdlib.h>

int *crea_inizializza(size_t n, int val) {
	int *res = malloc(n * sizeof(int));
	for (size_t i=0; i <n; i++) {
		res[i] = val--;
	}

	return res;
}

//int main(void) {
//	int *prova = crea_inizializza(5, 3);
//	free(prova);
//}