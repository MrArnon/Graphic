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
public:
	Model2D() : Vertices(), Edges() {}
	Model2D(const Matrix<> Vertices, const Matrix<int> Edges) :
		Vertices(Vertices), Edges(Edges) {}
/*	Model2D(string file_Vertices, string file_Edges)
	{
		ifstream fin(file_Vertices);
		int i = 0;
		while (fin.eof())
		{
			for(int j=0;j<3;j++)
			fin << Vertices.(i)(j);
			i++;
		}
		fin.close();
		ifstream fin(file_Edges);
		i = 0;
		while (fin.eof())
		{
			for (int j = 0; j<3; j++)
				fin << Edges.(i)(j);
			i++;
		}
		fin.close();
	}*/

	Matrix<> GetVertices() { return Vertices; }
	//Matrix<> GetEdges() { return Edges; }
};
#endif MODEL_2D_H#pragma once
