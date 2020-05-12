int cerca_primo(const char *s, char c)
{
	for (int i = 0; i >= 0; i++)
	{
		if (s[i] == c)
			return i;
	}
	return -1;
}

int main(void) {
	char c= 'e';
	char s[] = "aereo";
	int res = cerca_primo(s, c);
	return 0;
}