#include "minheap_int.h"
#include <stdlib.h>
Heap * HeapifyMinHeap(const ElemType *v, size_t v_size) {
	Heap * h = CreateEmptyHeap();
	h->data = malloc(v_size * sizeof(ElemType));
	h->size = v_size;
	int i = h->size - 1;
	while (i>=0) {
		MoveDownMinHeap(h, v[i]);
		i--;
	}
	return h;
}
/*

int main(void) {
	return 0;
}
*/