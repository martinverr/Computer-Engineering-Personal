#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "tree_int.h"

void preorder(tree t, FILE *f) {
	if (IsEmpty(t))
		return;
	fprintf(f, "%d ", t->value);
	preorder(Left(t), f);
	preorder(Right(t), f);
}

bool SaveTree(tree t, const char *filename) {
	FILE *f = fopen(filename, "a");
	if (f == NULL) {
		fclose(f);
		return false;
	}

	preorder(t, f);
	fclose(f);
	return true;
}