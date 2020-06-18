#include <stdlib.h>

int * genRandVec(size_t size) {
	if (size == 0)
		return NULL;

	int * v = malloc(size * sizeof(int));
	for (size_t i = 0; i < size; i++) {
		v[i] = rand();
	}

	return v;
}

void swap(int*a, int*b) {
	int temp = *a;
	*a = *b;
	*b = temp;

}

void bubblesort(int * v, int size) {
	_Bool swapped = 1;

	for (int i = 0; i < size && swapped; i++) {
		swapped = 0;
		for (int j = i; j < size - 1 - i; j++)
			if (v[j] > v[j + 1]) {
				swap(&v[j], &v[j + 1]);
				swapped = 1;
			}
	}
}

int findMax(int * v, int size) {
	int indexMax = 0;
	for (int i = 0; i < size; i++)
		if (v[i] > v[indexMax])
			indexMax = i;
	return indexMax;
}

void selectionsort(int * v, int size) {
	for (; size>0; size--) {
		// find max
		int iMax = findMax(v, size);

		// set max in ending
		swap(&v[iMax], &v[size-1]);
	}
}

void insertionsort(int * v, int size) {
	for (int i = 1; i < size; i++) {
		int key = v[i];
		int j = i - 1;
		for (; j >= 0 && v[j] > key; j--)
			v[j + 1] = v[j];
		v[j + 1] = key;
	}

}

void quicksort(int * v, int min, int max) {
	if (min < max) {
		int i = min, j = max;
		int pivot = (v[max] + v[min]) / 2;

		do {
			while (v[i] < pivot) i++;
			while (v[j] > pivot) j--;
			if (i <= j) {
				swap(&v[i], &v[j]);
				i++; j--;
			}
		} while (i <= j);

		quicksort(v, min, j);
		quicksort(v, i, max);
	}

}

void merge(int v[], int first, int mid, int last) {
	int vout[last - first + 1];
	int i = first, j = mid, k = first;
	while (i < mid && j <= last) {
		if (v[i] < v[j])
			vout[k] = v[i++];
		else
			vout[k] = v[j++];
		k++;
	}
	while (i < i2) {
		vout[k] = v[i++];
		k++;
	}
	while (j <= last) {
		vout[k] = v[j++];
		k++;
	}
	for (i = i1; i <= last; i++)
		v[i] = vout[i];
}

void mergeSort(int v[], int first, int last) {
	int mid;
	if (first < last) {
		mid = (first + last) / 2;
		mergeSort(v, first, mid);
		mergeSort(v, mid + 1, last);
		merge(v, first, mid + 1, last);
	}
}
}

/*
int main(void) {
	int * v1 = genRandVec(6);
	bubblesort(v1, 10);
	free(v1);

	int * v2 = genRandVec(6);
	selectionsort(v2, 10);
	free(v2);

	int * v3 = genRandVec(6);
	insertionsort(v3, 10);
	free(v3);

	int * v4 = genRandVec(6);
	quicksort(v4, 0, 5);
	free(v4);

	return 0;
}
*/