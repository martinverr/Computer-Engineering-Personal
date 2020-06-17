#include "minheap_int.h"
#include <stdlib.h>

void swap(ElemType * a, ElemType * b) {
	ElemType tmp = *a;
	*a = *b;
	*b = tmp;
}

bool PopMinHeap(Heap * h, ElemType *e) {
	if (IsEmptyHeap(h))
		return false;
	
	*e = *GetNodeValueHeap(h, 0);
	
	swap(GetNodeValueHeap(h, 0), GetNodeValueHeap(h, h->size - 1));
	h->size--;
	h->data = realloc(h->data, h->size * sizeof(ElemType));

	MoveDownMinHeap(h, 0);
	return true;
}