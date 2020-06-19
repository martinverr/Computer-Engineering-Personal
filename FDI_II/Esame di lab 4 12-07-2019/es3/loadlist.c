#include "tree_char.h"
#include <stdio.h>

// NOTA: aggiungere funzioni splitter dopo un carattere o un .carattere
//		con \n per correggere caso di scrittura in singola linea

tree rec(tree t, FILE *f) {
	char valoreLetto[3]; // 3 caratteri max: (.)\c0
	if (feof(f))
		return EmptyTree();
	fscanf(f, "%s", valoreLetto);


	element value;
	if (valoreLetto[0] == '.') {
		value = valoreLetto[1];
		return ConsTree(&value, EmptyTree(), EmptyTree());
	}
	else {
		value = valoreLetto[0];
		return ConsTree(&value, rec(t, f), rec(t,f));
	}
}
tree LoadTree(const char *filename) {
	tree res = EmptyTree();
	FILE * f = fopen(filename, "r");
	if (f == NULL)
		return res;

	res = rec(res, f);
	
	return res;
}