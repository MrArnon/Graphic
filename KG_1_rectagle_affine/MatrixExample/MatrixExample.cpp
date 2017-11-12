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
	double a[4] = {1, -2, 3, 0};
	Matrix<> A(2,2, a);

	double b[4] = {2, 2, 0, 1};
	Matrix<> B(2,2, b);

	Matrix<> C = A*B;
	cout
		<< endl <<   "A =" << endl << A
		<< endl <<   "B =" << endl << B
		<< endl <<   "C =" << endl << C
		<< endl << "A+B =" << endl << (A+B)
		<< endl << "A-B =" << endl << (A-B)
		<< endl << "T(1,2) =" << endl << Translation(1, 2);

	system("pause");
}
