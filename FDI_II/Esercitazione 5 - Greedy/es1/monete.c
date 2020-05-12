#include <stdlib.h>

* Monete(int *t, int size, int b) {

	if (t == NULL || b <= 0)
		return NULL;

	int * res = calloc(size, sizeof(int));

	int index = 0;
	while (index < size) {
		if (b >= t[index]) {
			b -= t[index];
			res[index]++;
		}
		else
			index++;
	}

	return res;
}

/*
int main(void) {
	int banconote[] = { 50, 20, 10, 5, 2, 1 };

	int * res1 = Monete(banconote, 6, 126);
	int * res2 = Monete(banconote, 6, -10);
	int * res3 = Monete(banconote, 6, 0);
	int * res4 = Monete(NULL, 0, 250);
	int * res5 = Monete(banconote, 6, 500);

	return 0;
}
*/
