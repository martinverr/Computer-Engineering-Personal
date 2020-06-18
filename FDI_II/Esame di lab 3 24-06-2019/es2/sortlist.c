#include "list_int.h"

list SortList(list l) {
	list tmp = l;
	while (!IsEmpty(tmp)) {
		list tmp2 = tmp;
		while (!IsEmpty(tmp2)) {
			if (Head(tmp) > Head(tmp2)) {
				element temp = tmp->value;
				tmp->value = tmp2->value;
				tmp2->value = temp;
			}
			tmp2 = Tail(tmp2);
		}
		tmp = Tail(tmp);
	}
	return l;
}