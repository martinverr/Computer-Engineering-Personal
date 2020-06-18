#include <stdbool.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

bool BubbleSort(int *v, int v_size) {
	if (v == NULL)
		return false;
	bool swapped = true;
	for (int i = 0; i < v_size && swapped; i++) {
		swapped = false;
		for (int j = 0; j < v_size - i - 1; j++)
			if (v[j] > v[j + 1]) {
				swap(&v[j], &v[j + 1]);
				swapped = true;
			}
	}
	return true;
}
/*
int main(void) {
	int vect[] = { 5, 7, 8, 3, 6, 8 };
	BubbleSort(vect, 6);
	return 0;
}
*/