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

Item* LoadList(const char * filename) {
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
	Item * res1 = LoadList("data_00.txt");
	WriteStdoutList(res1);
	Item * res2 = LoadList("data_01.txt");
	WriteStdoutList(res2);

	Item * res12diff = Diff(res1, res2);
	WriteStdoutList(res12diff);

	DeleteList(res2);
	DeleteList(res1);
	return 0;
}
