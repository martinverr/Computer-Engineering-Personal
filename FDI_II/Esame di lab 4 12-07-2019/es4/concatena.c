#include "list_int.h"

list lastItem(list l) {
	while (l->next)
		l = l->next;
	return l;
}

list Concatena(list *ls, int ls_size) {
	for (int i = 1; i < ls_size; i++) {
		if (ls[0])
			lastItem(ls[0])->next = ls[i];
		else
			ls[0] = ls[i];
	}
	return ls[0];
}