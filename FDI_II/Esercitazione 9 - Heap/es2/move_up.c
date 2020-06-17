#include "minheap_int.h"
#include <stdlib.h>

void swap(ElemType * a, ElemType * b) {
	ElemType tmp = *a;
	*a = *b;
	*b = tmp;
}
void MoveUpMinHeapRec(Heap * h, int i) {
	if (i < 0)
		return;
	if (ElemCompare( GetNodeValueHeap(h, i), GetNodeValueHeap(h, ParentHeap(i))) < 0){
		swap(GetNodeValueHeap(h, i), GetNodeValueHeap(h, ParentHeap(i)));
		MoveUpMinHeapRec(h, ParentHeap(i));
	}
		
}
/*

int main(void) {
	return 0;
}
*/