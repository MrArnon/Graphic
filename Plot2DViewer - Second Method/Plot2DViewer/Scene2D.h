#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include "Model2D.h"
#include "Matrix.h"


class Scene2D : public Camera2D
{

private:
	
	typedef double (*Func)(double);
	
public:
	Model2D model;
	//Model2D model;
	Scene2D(double X0, double Y0, double px, double py,string f1,string f2) : Camera2D(X0, Y0, px, py), model(f1,f2)
	{
		
	}
	void Render(HDC dc, bool axes = true)
	{
		/*	Matrix<int> Ed =  Matrix<int>(5,5);
			Matrix <> Vert = Matrix<>(2,4);
			Ed=model.GetEdges();
			Vert=model.GetVertices();
	*/
		model= Model2D("vertices.txt", "edges.txt");
		Matrix<int> Ed = model.GetEdges();
		
	if (axes)
			Axes(dc);

		/*double Ex = Ed(0, 0);
		double Ey = Ed(0, 1);
		double x = Vert(0,Ex);//+(1/(2*px));
		double y = Vert(1, Ey);
		MoveTo(x, y);
		
		for (int i =1; i<5;i++)
		{
			Ex = Ed(i, 0);
			Ey = Ed(i, 1);
			x = Vert(0, Ex);
			y = Vert(1, Ey);
			LineTo(dc, x, y);

		}
		*/
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Ed(i, j) == 1)
			{
				int v1 = i;
				int v2 = j;

				double x1 = model.GetVertexX(v1);
				double y1 = model.GetVertexY(v1);
				MoveTo(x1, y1);

				double x2 = model.GetVertexX(v2);
				double y2 = model.GetVertexY(v2);
				LineTo(dc,x2, y2);
			}

		
		}
	}

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
