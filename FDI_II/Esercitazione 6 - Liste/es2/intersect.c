#define _CRT_SECURE_NO_WARNINGS
#include "list_int.h"
#include <stdlib.h>


Item* Intersect(const Item * i1, const Item * i2) {
	Item * list = CreateEmptyList();

	const Item * temp = i1;
	const Item * temp2 = i2;
	while (temp) {
		const ElemType * currEl = GetHeadValueList(temp);
		temp2 = i2;

		while (temp2) {
			const ElemType * cmpEl = GetHeadValueList(temp2);
			if (ElemCompare(currEl, cmpEl) == 0)
				list = InsertHeadList(currEl, list);
			temp2 = temp2->next;
		}

		temp = temp->next;
	}

	return list;
}