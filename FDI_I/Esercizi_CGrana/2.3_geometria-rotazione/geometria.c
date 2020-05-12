#include "geometria.h"

void rotazione(struct punto *p, double alfa) {
	/*
	*	x'=xcos(alfa)-ysin(alfa)
	*	y'=xsin(alfa)+ycos(alfa)
	*/
	(*p).x = (*p).x*cos(alfa) - (*p).y *sin(alfa);
	p->y = (p->x) * sin(alfa) + (p->y) * cos(alfa);
}

