#if !defined GEOMETRIA_H

#define GEOMETRIA_H
#include <math.h>
#define PI 3.14159265359

struct punto { double x, y; };
extern void rotazione(struct punto *p, double alfa);

#endif //(!GEOMETRIA_H)