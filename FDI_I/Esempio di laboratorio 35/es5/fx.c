#include "fire_sym.h"

void propagate_fire(const struct forest *f) {
	struct forest *res = malloc(sizeof(struct forest));
	res->cols = f->cols;
	res->rows = f->rows;
	res->data = malloc(f->cols * f->rows);
	//copy
	for (size_t i = 0; i < f->cols * f->rows; i++) {
		(res->data)[i] = (f->data)[i];
	}

	//fire symulation
	for (size_t i = 0; i < f->cols * f->rows; i++) {
		if (f->data[i] == 'F') {
			if (i + 1 > 0 && i + 1 < f->rows*f->cols - 1)
				res->data[i+1] = 'F';

			if (i - 1 > 0 && i - 1 < f->rows*f->cols - 1)
				res->data[i-1] = 'F';
			
			if (i + f->cols > 0 && i + f->cols < f->rows*f->cols - 1)
				res->data[i+f->cols] = 'F';
			
			if (i - f->cols > 0 && i - f->cols < f->rows*f->cols - 1)
				res->data[i-f->cols] = 'F';
		}
	}

	//result in f
	for (size_t i = 0; i < f->cols * f->rows; i++) {
		f->data[i] = res->data[i];
	}

	free(res->data);
	free(res);
}

int main(void) {
	struct forest *f = malloc(sizeof(struct forest));
	f->cols = 10;
	f->rows = 10;
	char data[100] = {
		'.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
		'.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
		'.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
		'.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
		'.', '.', '.', '.', '.', 'F', 'F', '.', '.', '.',
		'.', '.', '.', '.', 'F', 'F', 'F', '.', '.', '.',
		'.', '.', '.', '.', '.', 'F', '.', '.', '.', '.',
		'.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
		'.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
		'.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
	};
	f->data = data;
	
	propagate_fire(f);

	return 0;
}