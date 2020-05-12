int ismultiple(int x, int y)
{
	if (x%y == 0)
		return 1;
	return 0;

}

int main(void)
{
	int x, y, z;
	x = 6;
	y = 3;
	z = ismultiple(x, y);
	return 0;
}