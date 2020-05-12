#include "sequenza.h"

bool seq_load(const char *filename, struct seq *s) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		fclose(f);
		return false;
	}
	
	int num = 0;
	uint16_t letto = 0;
	while (1) {
		if (fread(&letto, sizeof(uint16_t), 1, f) != 1)
			break;
		num++;
	}
	rewind(f);

	uint16_t * letti = malloc(sizeof(uint16_t)*num);
	//size_t check = 0;
	//check = 
	fread(letti, sizeof(uint16_t), num, f);
	//if (check != s->len) {
	//	fclose(f);
	//	return false;
	//}

	(*s).values = letti;
	s->len = num;

	fclose(f);
	return true;
}

int main(void) {
	uint16_t cosa[] = { 5,8,2,4,0 };
	struct seq prova = { 5, cosa};
	seq_load("prova", &prova);
	return 0;
}
