#define _CRT_SECURE_NO_WARNINGS
#include "list_int.h"
#include <stdlib.h>
#include <stdbool.h>

Item* remove_rep(Item * i);

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

	// The only difference is to return a list with no multiple Items
	return remove_rep(list);
}

Item* remove_rep(Item * i) {
	if (IsEmptyList(i))
		return i;

	Item * tmp = i;
	while (!IsEmptyList(tmp)) { // loop trough Items in i

		// loop trough next Items after the current tmp Item
		Item * tmp2 = GetTailList(tmp);
		while (!IsEmptyList(tmp2)) {
			// IF: we find same Element, DO: remove tmp2 Item
			if (ElemCompare(GetHeadValueList(tmp), GetHeadValueList(tmp2)) == 0) {
				tmp->next = tmp2->next;
			}
			tmp2 = GetTailList(tmp2);
		}

		// update tmp to next Item
		tmp = GetTailList(tmp);
	}

	return i;
}
