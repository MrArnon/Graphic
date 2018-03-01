
#ifndef MODEL_2D_H
#define MODEL_2D_H
#include <string>
#include <fstream>
#include "Matrix.h"

class Model2D
{
private:
	Matrix<> Vertices;
	Matrix<int> Edges;
	Matrix<> CumulativeAT;
	Matrix<> InitialVertices;
public:
	Model2D() : Vertices(), Edges() , CumulativeAT(Identity()), InitialVertices() {}
	Model2D(const Matrix<> Vertices, const Matrix<int> Edges) :
	Vertices(Vertices), Edges(Edges) , CumulativeAT(Identity()), InitialVertices(Vertices){}

	Model2D(string V, string E)
	{
		int r, c;
		CumulativeAT=Identity();
		ifstream Vfin(V);
		Vfin >> r >> c;
		Vertices = Matrix<>(r, c);
		Vfin >> Vertices;
		Vfin.close();
		InitialVertices=Vertices;
		ifstream Efin(E);
		Efin >> r >> c;
		Edges= Matrix<int>(r, c);
		Efin >> Edges;
		Efin.close();

	}
	Matrix<> GetVertices() { return Vertices; }
	Matrix<int> GetEdges() { return Edges; }


	void Apply(Matrix<> Affin)
	{	
		CumulativeAT = Affin * CumulativeAT;
		Vertices = CumulativeAT * InitialVertices;

	}
	double GetVertexX(int i){return Vertices(0, i)/Vertices(2, i);}
	double GetVertexY(int i){return Vertices(1, i)/Vertices(2, i);}

};

#endif MODEL_2D_H