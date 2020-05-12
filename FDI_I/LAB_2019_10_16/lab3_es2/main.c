int ismultiple(char x, char y)
{
	return !(x % y);
}

int main(void)
{
	char x, y, z;
	x = 5;
	y = -3;
	z = ismultiple(x, y);

	return 0;
}
