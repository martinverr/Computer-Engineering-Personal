#include "tirocini.h"

int main(void) {
	FILE *f1 = fopen("input1.txt", "r");
	struct tirocinio *t1 = malloc(sizeof(struct tirocinio));
	struct tirocinio *t2 = malloc(sizeof(struct tirocinio));
	struct tirocinio *t3 = malloc(sizeof(struct tirocinio));
	struct tirocinio *t4 = malloc(sizeof(struct tirocinio));
	tirocinio_load(f1, t1);
	tirocinio_load(f1, t2);
	tirocinio_load(f1, t3);
	tirocinio_load(f1, t4);
	tirocinio_load(f1, t1);
	tirocinio_load(f1, t1);
	tirocinio_load(f1, t1);


	return 0;
}