
#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double( *Func )( double );
	typedef double( *FuncEll )(double, double, double);
	

public:
	Model2D model;
	Scene2D( double L, double R, double B, double T, Matrix<>Vertices, Matrix<int> Edges ) : Camera2D( L, R, B, T )
	{
		model = Model2D(Vertices, Edges);
	}

	void Plot(HDC dc, Func f, bool axes = true)
	{
		if ( axes )
			Axes( dc );

		MoveTo( L, f( L ) );

		double Step = ( R - L ) / W;

		for ( double x = L; x <= R; x += Step )
		{
			LineTo( dc, x, f( x ) );
		}
	}
	void ParametricPlot( HDC dc, FuncEll X, FuncEll Y, Func U, Func V, double c, double t_min, double t_max, bool axes=true)
	{
		if (axes)
			Axes(dc);

		

		double step = (( R - L ) / W)*0.1;

		MoveTo(X(c,U(t_min),V(t_min)), Y(c,U(t_min),V(t_min)));

		for (double t=t_min; t<t_max; t+=step)
		{
			LineTo(dc, X(c,U(t),V(t)), Y(c,U(t),V(t)));
		}

		LineTo(dc, X(c,U(t_max),V(t_max)), Y(c,U(t_max),V(t_max)));
	}
	void Render(HDC dc, int count_e ,bool axes=true)
	{
		if (axes)
			Axes(dc);
		for (int i=0; i<count_e; i++)
		{
			MoveTo(model.GetVertexX(model.GetEdges()(i, 0)), model.GetVertexY(model.GetEdges()(i, 0)) );
			LineTo(dc, model.GetVertexX(model.GetEdges()(i, 1)), model.GetVertexY(model.GetEdges()(i, 1)));
		}

		
	}
};

#endif SCENE_2D_H
