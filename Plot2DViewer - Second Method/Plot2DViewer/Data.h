#define _USE_MATH_DEFINES
#include <cmath>

double					// Исходные значения параметров X0, Y0, px, py
	X0=200,
	Y0=200,
	px=50,
	py=100,
    r,
	phimax = 8*M_PI,
	phimin = 0,
    tmax = 4*M_PI,
	tmin=0;
    

double Parabola(double x)
{
	return x*x-2;
}

double Sinusoid(double x)
{
	return sin(x);
}
double Butterfly(double x)
{
return 0.05*x;
}
double Arch_R(double t)
{
return 2-4*sin(t);
}
double Arch_Phi(double t)
{
return t;
}