#define _CRT_SECURE_NO_WARNINGS
#include "primitive.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* ES 1 */
const ElemType * Find(const Item *i, const char *name) {
	const Item * tmpl = i;
	while (tmpl) {
		const ElemType * currValue = GetHeadValueList(tmpl);
		if (strcmp(currValue->name, name) == 0) {
			return currValue;
		}
		tmpl = GetTailList(tmpl);
	}
	return NULL;
}

/* ES 2 */
Item *Delete(Item * i, const char *name) {
	Item * found_item = NULL;
	Item * prev_found = NULL; 
	Item * tmp = i;

	// get prevItem
	
	while (tmp) {
		const ElemType * currValue = GetHeadValueList(tmp);
		if (strcmp(currValue->name, name) == 0) {
			prev_found = tmp;
			break;
		}
	}

	// IF: found_item  is first item; DO: return second Item
	if (found_item == i)
		return GetTailList(i);

	// ELSE: There's a prev_found item -> get it and update .next, then free found_item
	prev_found->next = found_item->next;
	ElemDelete(&found_item->value);

	return i;
}

/* ES 3 */
void swap_Item(Item * a, Item * b) {
	Item temp = *a;
	*a = *b;
	*b = temp;
}

Item * Sort(Item * i) {
	Item * tmp1 = i;
	while(!IsEmptyList(tmp1)){
		Item * tmp2 = GetTailList(i);
		while (!IsEmptyList(tmp2)){
			if (ElemCompare(&tmp2->value, &tmp1->value) > 0)
				swap_Item(tmp1, tmp2);
			tmp2 = GetTailList(tmp2);
		}
		tmp1 = GetTailList(tmp1);
	}
	return i;
}

/* ES 4 */
Item * Filtra(Item * i, const char *city) {
	Item * res = CreateEmptyList();

	while (!IsEmptyList(i)) {
		if (strcmp(city, GetHeadValueList(i)->city) == 0)
			res = InsertBackList(res, GetHeadValueList(i));
		i = GetTailList(i);
	}

	return res;
}

/* ES 5 */
Item * Reverse(const Item * l) {
	Item * res = CreateEmptyList();

	const Item * l_tmp = l;
	while (!IsEmptyList(l_tmp)) {
		res = InsertHeadList(GetHeadValueList(l_tmp), res);
		l_tmp = l_tmp->next;
	}

	return res;
}

/* ES 6 */
Item * Append(const Item* l1, const Item*l2) {
	Item * res = CreateEmptyList();
	const Item * l1_tmp = l1;
	const Item * l2_tmp = l2;
	// add elems of l1 in res
	while (l1_tmp) {
		res = InsertBackList(res, &l1_tmp->value);
		l1_tmp = GetTailList(l1_tmp);
	}
	// add elems of l2 in res
	while (l2_tmp) {
		res = InsertBackList(res, &l2_tmp->value);
		l2_tmp = GetTailList(l2_tmp);
	}

	return res;
}

/* ES 7 */
Item * AppendMod(Item* l1, Item * l2) {
	// get last not-empty item of list l1 as tmp
	Item * tmp = l1;
	while (!IsEmptyList(tmp->next)) {
		tmp = GetTailList(tmp);
	}

	// change .next of tmp to head(l2)
	tmp->next = l2;

	return l1;
}