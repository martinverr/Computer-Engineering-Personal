#define _CRT_SECURE_NO_WARNINGS
#include "list_int.h"
#include <stdlib.h>
#include <stdbool.h>

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