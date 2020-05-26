#include "list_int.h"
#include <limits.h>

ElemType MaxElement(const Item* i) {
	ElemType max = INT_MIN;
	while (!IsEmptyList(i)) {
		if (*GetHeadValueList(i) > max) {
			max = *GetHeadValueList(i);
		}
		i = GetTailList(i);
	}
	return max;
}