#include "geometria.h"


int main(void) {
	double angolo1 = PI / 3;
	double angolo2 = PI / 2;

	struct punto punto1 = { 1,0 };
	struct punto punto2 = { .x = 0,.y = 1 };
	rotazione(&punto1, angolo1);
	rotazione(&punto2, angolo2);

	return 0;
}