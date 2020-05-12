#include <math.h>
struct punto { double x, y; };

double distanza(struct punto *a, struct punto *b) {
	return sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
}


//int main(void) {
//	struct punto p1 = { 0,0 };
//	struct punto p2 = { 3,4 };
//
//	double dist_p1_p2 = distanza(&p1, &p2);
//
//	return 0;
//}