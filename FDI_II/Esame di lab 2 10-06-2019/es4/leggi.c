
#define _CRT_SECURE_NO_WARNINGS
#include "list_coords.h"
#include <stdio.h>


list LoadList(const char * filename) {
	list res = EmptyList();
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		return res;
		fclose(f);
	}

	while (1) {
	coords * punto = malloc(sizeof(coords));
	int check = fscanf(f, "%d%d", &punto->x, &punto->y);
	if (check == EOF)
		break;
	// res = InsertBack(res, punto);
	res = Cons(punto, res);
	}

	fclose(f);
	return res;
}

int main(void) {
	LoadList("list_coords01.txt");

}