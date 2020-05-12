unsigned int fattoriale(int val) {
	int fatt = 1;
	
	while (val != 1)
	{
		fatt *= val;
		val--;
	}
	return fatt;
}
main() {

	int fatt = 0, val = 4;
	fatt = fattoriale(val);
	return 0;
}