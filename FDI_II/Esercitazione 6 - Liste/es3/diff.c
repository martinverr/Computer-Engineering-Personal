#define _CRT_SECURE_NO_WARNINGS
#include "list_int.h"
#include <stdlib.h>
#include <stdbool.h>

Item* Diff(const Item * i1, const Item * i2) {
	Item * list = CreateEmptyList();

	const Item * temp = i1;
	const Item * temp2 = i2;
	while (temp) {
		const ElemType * currEl = GetHeadValueList(temp);
		temp2 = i2;
		bool take = true;

		while (temp2) {
			const ElemType * cmpEl = GetHeadValueList(temp2);
			if (ElemCompare(currEl, cmpEl) == 0) {
				take = false;
				break;
			}
			temp2 = temp2->next;
		}

		if (take)
			list = InsertHeadList(currEl, list);
		temp = temp->next;
	}

	return list;
}