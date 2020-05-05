int Somma(n){
	/*
	param: <n>
	return the sum of first n numbers if <n> > 0
	if <n> is 0 or a negative number return -1
	*/
	
	if (n < 1)
		return -1;
	if (n == 1)	//recurs base
		return 1;
	return Somma(n - 1) + n;
}

int main(void) {
	int res1 = Somma(5);
	int res2 = Somma(0);
	int res3 = Somma(-5);
	int res4 = Somma(1);
	return 0;
}