#include "heap_int.h"

#include <stdlib.h>
#include <string.h>

int Left(int i)
{
    return 2 * i;
}

int Right(int i)
{
    return 2 * i + 1;
}

int Parent(int i)
{
    return i / 2;
}

int Compare(const element *e1, const element *e2)
{
    return *e1 < *e2 ? -1 : *e1 > *e2;
}

void Swap(element *e1, element *e2)
{
    element tmp;
    tmp = *e1;
    *e1 = *e2;
    *e2 = tmp;
}

void MoveUpMaxHeap(element *h, int i) {

    while (i != 1 && Compare(&h[i], &h[Parent(i)]) > 0) {
        Swap(&h[i], &h[Parent(i)]);
        i = Parent(i);
    }
}

void MoveDownMaxHeap(element *h, int i) {

    int l, r, largest = i;
    bool done;
    do {
        done = true;
        l = Left(i);
        r = Right(i);

        if ((l <= h[0]) && Compare(&h[l], &h[largest]) > 0) {
            largest = l;
        }

        if ((r <= h[0]) && Compare(&h[r], &h[largest]) > 0) {
            largest = r;
        }

        if (largest != i) {
            Swap(&h[i], &h[largest]);
            i = largest;
            done = false;
        }

    } while (!done);

    return;
}

element *CreateHeap() {
    element *h = malloc(1 * sizeof(element));
    *h = 0;
    return h;
}

void FreeHeap(element *h) {
    free(h);
}

element* HeapifyMaxHeap(element *v, size_t v_size) {

	element *h = malloc(sizeof(element)*(v_size + 1));
	h[0] = (int)(v_size);
	memcpy(h + 1, v, v_size * sizeof(size_t));

	for (int i = h[0] / 2; i >= 1; i--) {
		MoveDownMaxHeap(h, i);
	}
	return h;
}
