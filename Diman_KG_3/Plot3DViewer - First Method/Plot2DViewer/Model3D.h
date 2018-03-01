#pragma once
#ifndef MODEL_3D_H
#define MODEL_3D_H
#include <set>
#include <string>
#include <fstream>
#include "Matrix.h"
#include "AffineTransform.h"

class Model3D
{
private:
	Matrix<> Vertices;
	Matrix<int> Verges;
	Matrix<int> Edges;
	Matrix<> CumulativeAT;
	Matrix<> InitialVertices;
	
public:
	Matrix<> ProjectedVertices;
	Model3D() : Vertices(), Verges(), Edges() , CumulativeAT(Identity3D()), InitialVertices(), ProjectedVertices() {}
	Model3D(const Matrix<int> Verges, const Matrix<> Vertices) :
	Verges(Verges), Vertices(Vertices) , CumulativeAT(Identity3D()), InitialVertices(Vertices){SetEdges();}

	Model3D(string V, string E)
	{
		int r, c;
		CumulativeAT=Identity();
		ifstream Vfin(V);
		Vfin >> r >> c;
		Verges = Matrix<int>(r, c);
		Vfin >> Verges;
		Vfin.close();
		InitialVertices=Vertices;
		ifstream Efin(E);
		Efin >> r >> c;
		Vertices= Matrix<>(r, c);
		Efin >> Vertices;
		Efin.close();
		SetEdges();

	}
	Matrix<> GetVertices() { return Vertices; }
	Matrix<int> GetEdges() { return Edges; }
	Matrix<int> GetVerges (){return Verges;}

	void SetEdges()
	{

		typedef pair <int, int> Point; 
		typedef set <Point> V;  
		set<Point> :: iterator it;
		V vert;
		for (int i=0; i<Verges.getRows(); i++)
		{
			Point p1(Verges(i,0),Verges(i,1));
			if (Verges(i,0)<Verges(i,1))  p1.swap(p1);
			Point p2(Verges(i,0),Verges(i,2));
			if (Verges(i,0)<Verges(i,2))  p2.swap(p2);
			Point p3(Verges(i,1),Verges(i,2));
			if (Verges(i,1)<Verges(i,2))  p3.swap(p3);
			vert.insert(p1);
			vert.insert(p2);
			vert.insert(p3);
		}
		int i=0;
		Edges = Matrix<int>( vert.size(),2);
		for(it=vert.begin(); it!=vert.end(); it++)
		{
			Edges.set(i,0,it->first);
			Edges.set(i,1,it->second);
			i++;
		}
	}

	void Apply(Matrix<> Affin)
	{	
		CumulativeAT = Affin * CumulativeAT;
		Vertices = CumulativeAT * InitialVertices;


	}
	void Project(Matrix<> Project)
	{
		ProjectedVertices=Project*Vertices;
	}
	double GetVertexX(int i){
		double a=Vertices(0, i);
		double b=Vertices(3, i);
		return a/b;}
	double GetVertexY(int i){
		double a=Vertices(1, i);
		double b=Vertices(3, i);
		return a/b;}
	double GetVertexZ(int i){
		double a=Vertices(2, i);
		double b=Vertices(3, i);
		return a/b;}
	double GetProjectedX(int i){
		double a=ProjectedVertices(0, i);
		double b=ProjectedVertices(2, i);
		return a/b;}
	double GetProjectedY(int i){return ProjectedVertices(1, i)/ProjectedVertices(2, i);}
};

#endif MODEL_3D_H