#pragma once 

class Scene3D: public Camera3D
{
public:
	Model3D model;
	Scene3D( double L, double R, double B, double T, Matrix<int>Verges, Matrix<> Vertices ) : Camera3D( L, R, B, T )
	{
		model = Model3D(Verges, Vertices);
	}

	void Render(HDC dc, bool axes=true)
	{
		if (axes)
			Axes(dc);
		UpdateCamera(); 
		model.Project(WorldToProject);
		for ( int i=0; i<model.GetEdges().getRows(); i++)
		{
			double r=model.GetVertexX(2);
			r=model.GetVertexY(2);
			r=model.GetVertexZ(2);
			double a=model.GetEdges()(i, 0);
			double b=model.GetEdges()(i, 1);
			double c=model.GetEdges()(i, 0);
			double X1=model.GetProjectedX(a);
			double X2= model.GetProjectedX(b);
			double Y1=model.GetProjectedY(c);
			double Y2=model.GetProjectedY(model.GetEdges()(i, 1));
			MoveTo(X1, Y1 );
			LineTo(dc,X2, Y2);
		}
	}

};