#include "list_int.h"
#include <string.h>

Item * Filtra(Item * l, const char * citta) {
	Item * res = CreateEmptyList();

	if (IsEmptyList(l))
		return res;

	while (l) {
		if (strcmp(l->value.citta, citta) == 0) {
			InsertBackList(res, GetHeadValueList(l));
		}
		l = l->next;
	}
	return res;
}