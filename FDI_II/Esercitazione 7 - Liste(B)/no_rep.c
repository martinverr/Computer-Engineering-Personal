#define _CRT_SECURE_NO_WARNINGS
#include "primitive.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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
