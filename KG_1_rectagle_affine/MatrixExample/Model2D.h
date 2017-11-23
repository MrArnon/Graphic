#ifndef MODEL_2D_H
#define MODEL_2D_H
#include <string>
#include <fstream>
#include "Matrix.h"
#include "Vector"
class Model2D
{
private:
	Matrix<> Vertices;
	Matrix<int> Edges;
	vector<double> List;
public:
	Model2D() : Vertices(), Edges() {}
	Model2D(const Matrix<> Vertices, const Matrix<int> Edges) :
		Vertices(Vertices), Edges(Edges) {}
	Model2D(string file_Vertices, string file_Edges)
	{
		ifstream fin1(file_Vertices);
		int i = 0;
		while (fin1.eof())
		{
			//for (int j = 0; j < 3; j++)
				//fin << Vertices;double a[6] = {1, -2, 3, 0,1,2};
					//Matrix<> A(2, 3, a);
				//fin << a[j + i];
			int temp;
			fin1 >> temp;
			List.insert(List.end(), temp);
			i++;
		}
		Matrix<> Vertices(3, (List.size())/3, List);// 3 na m
		List.clear();
		fin1.close();
		ifstream fin2(file_Edges);
		i = 0;
		while (fin2.eof())
		{
			//for (int j = 0; j<3; j++)
				//fin << Edges.(i)(j);
			int temp;
			fin2 >> temp;
			List.insert(List.end(), temp);
				i++;
		}
		
		Matrix<> Edges((List.size())/2, 2, List); //k na 2
		List.clear();
		fin2.close();
	}
	void Apply(Matrix<> M)
	{
		Vertices= M*Vertices;
	}
	double GetVertexX(int i)
	{
		return Vertices(0, i);
	}
	double GetVertexY(int i)
	{
		return Vertices(1, i);
	}
	Matrix<> GetVertices() { return Vertices; }
	Matrix<int> GetEdges() { return Edges; }
};
#endif MODEL_2D_H#pragma once
