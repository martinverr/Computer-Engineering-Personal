#include "persona.h"

bool persona_scrivi(const struct persona *p, FILE *f) {
	size_t check = 0;
	
	check = fwrite(p->nome, 1, strlen(p->nome), f);
	if (check != strlen(p->nome))
		return 0;
	
	fputc('\0', f);
	//fputc(p->eta, f);
	check = fwrite(&(p->eta), sizeof(uint16_t), 1, f);

	fputc(p->sesso, f);
	
	return true;
}

int main(void) {
	FILE *f = fopen("prova", "wb");
	if (f == NULL)
		return -1;
	char nomep1[] = { "Martin" };
	struct persona martin = {nomep1, 19, 'M'};
	persona_scrivi(&martin, f);
	
	return 0;
}