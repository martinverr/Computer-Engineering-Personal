#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int * b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void quicksort(int * v, int first, int last) {
	if (first < last) {
		int i = first, j = last;
		int pivot = (v[j] + v[i]) / 2;

		do {
			while (v[i] < pivot) i++;
			while (v[j] > pivot) j--;

			if (i <= j) {
				swap(&v[i], &v[j]);
				i++; j--;
			}
		} while (i <= j);

		quicksort(v, first, j);
		quicksort(v, i, last);
	}

}

bool QuickSort(int *v, int v_size, int first, int last) {
	if (first<0 || last > v_size || last < first || v == NULL)
		return false;

	quicksort(v, first, last);
	return true;
}