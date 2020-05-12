int valprimo(int x){

	int i = x-1;

	while (i > 1)
	{
		if (x % i == 0)
			return 0;
		i--;
	}
	return 1;
}

int main(void) {
	int val = 11;
	int risultato;

	risultato = valprimo(val);
	return 0;
}