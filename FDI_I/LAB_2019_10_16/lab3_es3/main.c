double square_dist(double x1, double y1, double x2, double y2)
{
	return ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));

}

int main(void) {
	double x1, x2, y1, y2, d;
	x1 = 5;
	x2 = 3;
	y1 = 4;
	y2 = 2;
	d= square_dist(x1, y1, x2, y2);
	return 0;

}