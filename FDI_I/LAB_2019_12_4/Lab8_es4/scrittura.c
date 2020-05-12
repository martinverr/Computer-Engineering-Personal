#include "scrittura.h"

int scrivimaiuscolo(const char *filename) {
	//open file
	FILE *f = fopen(filename, "r");
	if (f == NULL)
		return 0;

	int thisChar = 0;
	while (1) {
		thisChar = fgetc(f);
		if (thisChar == EOF)
			break;
		printf("%c", toupper(thisChar));
		//or:	fprintf(stdout, "%c", toupper(thisChar));
	}
	
	return 1;
}