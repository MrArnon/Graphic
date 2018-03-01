
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#include <cmath>

double					// Исходные значения параметров L, R, B, T
	L = -M_PI,
	R = M_PI,
	B = -1.5,
	T = 1.5,
	c=0.25,
	t_min = 1*M_PI,
	t_max = 9*M_PI;

double Vert[] = { 2, 2, 6, 4,
                 0, 0, 0, 5,
                 4, 2, 2, 3,
                 1, 1, 1, 1 };

int Verg[] = { 0, 1, 2,
1, 3, 0,
1, 3, 2,
0, 3, 2,
};




double Parabola(double x)
{
	return x * x - 2;
}

double Sinusoid(double x)
{
	return  x ;
}

double U(double t)
{
	return pow(2,cos(t*19/4));
}

double V(double t)
{
	//return t;
	return t;
}

double XEllipt(double c, double u, double v)
{
	return c*cosh(u)*cos(v);
}

double YEllipt(double c, double u, double v)
{
	return c*sinh(u)*sin(v);
}




#endif _USE_MATH_DEFINES