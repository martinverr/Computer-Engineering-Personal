#include "gioielli.h"

Gioiello* Gioielli(const char* filename, float b, int *ret_size) {
	//open file
	FILE * f = fopen(filename, "r");
	if (f == NULL) {
		fclose(f);
		return NULL;
	}

	// vars we use
	Gioiello * listGioielli = malloc(2 * sizeof(Gioiello)); // Allocazione iniziale
	unsigned int numGioielli = 0, numGioielliUsati = 0;
	unsigned int listGioielliSize = 2;
	char * codice = malloc(50);
	char * peso = malloc(50);
	char * prezzo = malloc(50);
	size_t i = 0;

	// create listGioielli from data stored in file
	while (fscanf(f, "%s", codice) != EOF) {
		numGioielli++;
		if (numGioielli > listGioielliSize) {	//realloc *2 if necessary
			listGioielli = realloc(listGioielli, listGioielliSize * 2 * sizeof(Gioiello));
			listGioielliSize *= 2;
		}

		// get <codice>
		listGioielli[numGioielli - 1].codice = atoi(codice);

		// get <peso>
		fscanf(f, "%s", peso);
		listGioielli[numGioielli - 1].peso = (float)atof(peso);

		// get <prezzo>
		fscanf(f, "%s", prezzo);
		listGioielli[numGioielli - 1].prezzo = (float)atof(prezzo);

	}

	//order by .prezzo/.peso descendent
	for (unsigned int j = 0; j < numGioielli; j++)
		for (unsigned int k = j + 1; k < numGioielli - j; k++)
			if (listGioielli[j].prezzo / listGioielli[j].peso >
				listGioielli[k].prezzo / listGioielli[k].peso) {

				Gioiello temp = listGioielli[j];
				listGioielli[j] = listGioielli[k];
				listGioielli[k] = temp;
			}
	//greedy
	Gioiello * res = malloc(numGioielli * sizeof(Gioiello)); // Allocazione iniziale
	i = 0;
	while (i<numGioielli) {
		if (b >= listGioielli[i].prezzo) {
			res[numGioielliUsati].prezzo = listGioielli[i].prezzo;
			res[numGioielliUsati].codice = listGioielli[i].codice;
			res[numGioielliUsati].peso = listGioielli[i].peso;
			b -= listGioielli[i].prezzo;
			numGioielliUsati++;
		}
		i++;
	}

	// free unneeded mem
	fclose(f);
	free(peso);
	free(prezzo);
	free(codice);
	free(listGioielli);

	//return
	res = realloc(res, numGioielliUsati * sizeof(Gioiello));
	*ret_size = numGioielliUsati;
	return res;
}

/*
int main(void) {

	int ret1 = 0;
	Gioiello * res1 = Gioielli("Gioielli_1.txt", 121, &ret1);
	free(res1);

	int ret2 = 0;
	Gioiello * res2 = Gioielli("Gioielli_2.txt", 121, &ret2);
	free(res2);

	int ret3 = 0;
	Gioiello * res3 = Gioielli("Gioielli_3.txt", 200, &ret3);
	free(res3);


	return 0;
}
*/
