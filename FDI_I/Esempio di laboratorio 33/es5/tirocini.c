#include "tirocini.h"

bool tirocinio_load(FILE *f, struct tirocinio *t) {
	if (f == NULL)
		return false;
	if (t == NULL)
		return false;

	int min_lenght = 32;
	//int lenght_nome = min_lenght;
	//int lenght_az1 = min_lenght;
	//int lenght_az2 = min_lenght;
	//int lenght_az3 = min_lenght;
	char *nome = malloc(min_lenght);	//standard alloc of min 32 char
	char *az1 = malloc(min_lenght);
	char *az2 = malloc(min_lenght);
	char *az3 = malloc(min_lenght);
	char c = 0;
	int count = 0;

	//nome
	while (1) {
		c = fgetc(f);
		if (c == EOF || c == '\n')
			return false;
		if (c == ',')
			break;
		//if (count > lenght_nome) {
		//	realloc(nome, lenght_nome * 2);
		//	lenght_nome *= 2;
		//}

		nome[count] = c;

		count++;
	}
	nome[count] = 0;
	t->nome = nome;

	//az1
	count = 0;
	while (1) {
		c = fgetc(f);
		if (c == EOF || c == '\n')
			return false;
		if (c == ',')
			break;
		//if (count > lenght_az1) {
		//	realloc(nome, lenght_az1 * 2);
		//	lenght_az1 *= 2;
		//}
		az1[count] = c;

		count++;
	}
	az1[count] = 0;
	t->azienda1 = az1;

	//az2
	count = 0;
	while (1) {
		c = fgetc(f);
		if (c == EOF || c == '\n')
			return false;
		if (c == ',')
			break;
		//if (count > lenght_az2) {
		//	realloc(nome, lenght_az2 * 2);
		//	lenght_az2 *= 2;
		//}
		az2[count] = c;

		count++;
	}
	az2[count] = 0;
	t->azienda2 = az2;

	//az3
	count = 0;
	while (1) {
		c = fgetc(f);
		if (c == EOF)
			return false;
		if (c == '\n')
			break;
		//if (count >= lenght_az3) {
		//	realloc(az3, lenght_az3 * 2);
		//	lenght_az3 *= 2;
		//}

		az3[count] = c;

		count++;
	}
	az3[count] = 0;
	t->azienda3 = az3;

	return true;
}