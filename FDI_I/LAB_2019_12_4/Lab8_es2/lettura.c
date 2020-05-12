#include "lettura.h"
int *leggiinteri2(const char *filename, size_t *size) {
	
	//open file
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
		return NULL;

	//lenght of file
	fseek(f, 0, SEEK_END);
	long numOfElememts = ftell(f) / 4;	//note: number of POSSIBLE elements
	rewind(f);
	if (numOfElememts < 1){
		fclose(f);
		return NULL;
	}

	//alloc and read elements
	int *elements = malloc(numOfElememts * sizeof(int));
	size_t check = fread(elements, sizeof(int), numOfElememts, f);
	if (check != numOfElememts) {
		fclose(f);
		return NULL;
	}
	fclose(f);

	//result
	*size = numOfElememts;
	return elements;
}