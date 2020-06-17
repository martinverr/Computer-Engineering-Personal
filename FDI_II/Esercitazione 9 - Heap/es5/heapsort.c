#include "minheap_int.h"

#include <stdlib.h>
#include <string.h>


void HeapsortMinHeap(Heap *h)
{
	size_t origin_size = h->size; 

	while (h->size >= 2) {
		ElemSwap(GetNodeValueHeap(h, 0), GetNodeValueHeap(h, h->size - 1));
		h->size--;
		MoveDownMinHeap(h, 0);
	}
	h->size = origin_size;
}