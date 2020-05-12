double pot_alla_n(int x,int n){
	double risultato = 1;

	for (n; n > 0; n--) {
		risultato *= x;
	}
	return risultato;
}

unsigned int fattn(int n) {
	int fattn = 1;
	while (n > 1) {
		fattn *= n;		//oppure fattn *= n--;
		n--;
	}
	return fattn;
}

double exp(int x) {
	double risultato = 0;

	for (int n = 0; n < 10; n++) {
		risultato += pot_alla_n(x,n) / fattn(n);
	}
	return risultato;
}

int main(void) {
	int x = 7;
	double e_alla_x = exp(x);
	
	return 0;
}