char max_pot10(unsigned int val)
{
	char exp = 0;
	if (val == 0)
		return -1;
	while (val>1)
	{
		val /= 10;
		exp++;
	}
	return exp;
}

main() {

	int exp = 0, val = 123;
	exp = max_pot10(val);
	return 0;

}