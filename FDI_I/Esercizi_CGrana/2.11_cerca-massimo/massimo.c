#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int cercaMassimo(const char *filename) {
	int this_num = 0, max = 0;
	FILE *f = fopen(filename,"r");
	if (f == NULL)
		return -1;

	while (1) {
		if (fscanf(f, "%d", &this_num) == EOF)
			break;
		if (this_num > max)
			max = this_num;

	}

	fclose(f);
	return max;
}
//
//int main(void) {
//	char fileName[] = {"file1.txt"};
//
//	int maxOfFile1 = cercaMassimo(fileName);
//	int maxOfFile2 = cercaMassimo("file2.txt");
//
//	return 0;
//}