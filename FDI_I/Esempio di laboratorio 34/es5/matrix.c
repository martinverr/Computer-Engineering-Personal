#include "matrix.h"

bool matrix_read(struct matrix *m, FILE *f) {
	int check = fscanf(f, "%i", &m->rows);
	if (check != 1)
		return false;

	check = fscanf(f, "%i", &m->cols);
	if (check != 1)
		return false;

	//number of elements
	int numElem = 0;
	double temp = 0;
	while (1) {
		if (fscanf(f, "%lf", &temp)==1)
			numElem++;
		else
			break;
	}
	if (numElem != m->cols*m->rows)
		return false;

	//stream of file before the third number(begin of data)
	rewind(f);
	fscanf(f, "%lf", &temp);	
	fscanf(f, "%lf", &temp);

	//alloc and copy data
	m->data = malloc(sizeof(double)*numElem);
	for (size_t r = 0; r < m->rows; r++) {
		for(size_t c=0; c<m->cols; c++){
			fscanf(f, "%lf", &(m->data[r*m->cols + c]));
		}
	}

	return true;
}