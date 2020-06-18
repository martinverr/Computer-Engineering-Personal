#define _CRT_SECURE_NO_WARNINGS
#include "list_coords.h"
#include <stdio.h>

list Taglia(list l, int n) {
	if (n <= 0)
		return l;
	if( n == 1 || IsEmpty(l))
		return NULL;

	list tmp = l;
	int count = 0;
	while (!IsEmpty(tmp)) {
		count++;
		if (count == n) {
			FreeList(tmp);
			tmp = NULL;
			return l;
		}
		tmp = tmp->next;
	}
	
	return l;
}