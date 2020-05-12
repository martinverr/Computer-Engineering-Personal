#include "geometria.h"

int colineari(struct punto p1, struct punto p2, struct punto p3) {
	if ((p3.x - p2.x)*(p1.y - p2.y) == (p3.y - p2.y)*(p1.x - p2.x))
		return 1;
	else
		return 0;
}

int main(void) {
	struct punto p1 = { 0,0 };
	struct punto p2 = { 0,1 };
	struct punto p3 = { 0,2 };

	int res = collineari(p1,p2,p3);
}