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
/*
Item* Loadlist(const char * filename) {
	FILE * file = fopen(filename, "r");
	Item * list = CreateEmptyList();
	if (file == NULL) {
		return list;
	}

	// count = numero di elementi nel file
	int count = 0, temp;
	while (fscanf(file, "%d", &temp) != EOF)
		count++;
	rewind(file);

	for (int i = 0; i < count; i++) {
		ElemType el = ReadElem(file);
		list = InsertHeadList(&el, list);
	}

	fclose(file);
	return list;
}

int main(void) {
	Item * res1 = Loadlist("data_00.txt");
	WriteStdoutList(res1);
	Item * res2 = Loadlist("data_01.txt");
	WriteStdoutList(res2);

	Item * res12diff = Intersect(res1, res2);
	WriteStdoutList(res12diff);

	DeleteList(res2);
	DeleteList(res1);
	return 0;
}
*/