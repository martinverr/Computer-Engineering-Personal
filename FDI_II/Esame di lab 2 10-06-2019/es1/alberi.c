#include "tree_int.h"
#include <stdlib.h>

void preorder(tree t, int * i, element * v) {
	if (IsEmpty(t))
		return;
	(*i)++;
	v = realloc(v, sizeof(element) * (*i));
	v[*i-1] = *GetRoot(t);
	preorder(Left(t), i, v);
	preorder(Right(t), i, v);
}

tree Tree2Bst(tree t) {
	tree res = EmptyTree();
	if (IsEmpty(t))
		return res;
	element * vect = malloc(sizeof(element) * 100);
	tree tmp = t;
	int i = 0;
	preorder(tmp, &i, vect);

	for (int j = 0; j < i; j++) {
		res = InsertBinOrd(vect + j, res);
	}
	free(vect);
	return res;
}
