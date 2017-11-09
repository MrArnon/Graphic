#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
public:
	Scene2D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{
	}
	void Plot(HDC dc, Func f, bool axes=true)
	{
		if (axes)
			Axes(dc);
		double x=L();//+(1/(2*px));
		MoveTo(x,f(x));
		for (x;x<R();x+=(1/px))
		{
		
			LineTo(dc,x,f(x));
		    
		}// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
	}
	void PolarPlot(HDC dc, Func f,double phimin, double phimax,  bool axes=true)
	{
	if (axes)
             Axes(dc);
          double shag = M_PI / 180, phi = phimin;
          MoveTo(f(phi)*cos(phi), f(phi)*sin(phi));
          phi += shag;
          while (phi <= phimax) {
          LineTo(dc, f(phi)*cos(phi), f(phi)*sin(phi));
          phi += shag;
           } 
            LineTo(dc, f(phimax)*cos(phimax), f(phimax)*sin(phimax));
         }
	

	void PolarParametricPlot(HDC dc, Func f, Func f1,double tmax, double tmin, bool axes=true)
	{
	if (axes)
             Axes(dc);
          double shag = M_PI / 180, t = tmin;
          MoveTo(f1(t)*cos(f(t)), f1(t)*sin(f(t)));
          t += shag;
          while (t <= tmax) {
          LineTo(dc, f1(t)*cos(f(t)), f1(t)*sin(f(t)));
          t += shag;
           } 
            //LineTo(dc, f(tmax)*cos(tmax), f(tmax)*sin(tmax));
         }
	

};

#endif SCENE_2D_H
