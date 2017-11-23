#include "Matrix.h"
#include "AffineTransform.h"
#include "Model2D.h"


using namespace std;

void main()
{
/*
	Matrix<int> M(2);
	cout << "Input M ->\n ";
	cin >> M;
*/
	/*double a[6] = {1, -2, 3, 0,1,2};
	Matrix<> A(2,3, a);

	double b[6] = {2, 2, 0, 1,3,1};
	Matrix<> B(3,2, b);

	Matrix<> C = A*B;
	cout
		<< endl << "A =" << endl << A
		<< endl << "B =" << endl << B
		<< endl << "C =" << endl << C
		<< endl << "A+B =" << endl << (A + B)
		<< endl << "A-B =" << endl << (A - B)
		<< endl << "T(1,2) =" << endl << Rotation(0.31);
		*/

	double v[6] = { 2,1,3,0,1,1 };
	Matrix<> V(3, 2, v);
		int e[2] = { 1,2 };
	Matrix <int> E(1, 2, e);
	Model2D model(V, E);
	cout << endl << "Edges:" << endl << model.GetEdges()
		<< endl << "Vertices before AT  " << endl << model.GetVertices();
	//model.Apply(Translation(1, 2));
	model.Apply(Rotation(0.5));
	cout << endl << "Vertices after AT " << endl << model.GetVertices();
	system("pause");
}
