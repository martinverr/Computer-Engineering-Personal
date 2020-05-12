#include "shapes.h"

bool rect_load(FILE *f, struct rect *r) {
	
	size_t check = fread(&r->x, sizeof(int16_t), 1, f);
	if (check != 1)
		return false;

	check = fread(&r->y, sizeof(int16_t), 1, f);
	if (check != 1)
		return false;

	check = fread(&r->width, sizeof(int16_t), 1, f);
	if (check != 1)
		return false;

	check = fread(&r->height, sizeof(int16_t), 1, f);
	if (check != 1)
		return false;

	check = fread(&r->symbol, 1, 1, f);
	if (check != 1)
		return false;

	return true;
}

int main(void) {
	
	FILE *f = fopen("rect1.bin", "rb");
	struct rect *r1 = malloc(sizeof(struct rect));

	bool res = rect_load(f, r1);

	return 0;
}