#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

Matrix<> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1};
	return Matrix<>(3,3, T);
}
Matrix<> Rotation(double t)
{
	double R[9] = {
		cos(t), -sin(t), 0,
		sin(t), cos(t), 0,
		0,		0,		1 };
	return Matrix<>(3,3, R);
}
Matrix<> Rotation(double c,double s)
{
	double R[9] = {
		c, -s, 0,
		s, c, 0,
		0,0,1 };
	return Matrix<>(3,3, R);
}
Matrix<> Scaling(double kx, double ky)
{
	double S[9] = {
		kx, 0, 0,
		0, ky, 0,
		0,0,1 };
return Matrix<>(3,3, S);
}
Matrix<> Mapping(double x)
{
	double M[9] = {
		1, 0, 0,
		0, -1, 0,
		0,0,1 };
	return Matrix<>(3,3, M);
}
/*Matrix<> Mapping(double y)
{
	double M[9] = {
		-1, 0, 0,
		0, 1, 0,
		0,0,1 };
	return Matrix<>(3,3, M);
}*/
Matrix<> Mapping(double x,double y)
{
	double M[9] = {
		-1, 0, 0,
		0, -1, 0,
		0,0,1 };
	return Matrix<>(3,3, M);
}
// Здесь требуется реализовать функции, возвращающие матрицы базовых АП:
// Identity() - тождественное АП;
// Rotation(t) - поворот на угол t;
// Rotation(c, s) - поворот на угол, косинус и синус которого пропорциональны величинам c и s;
// Scaling(kx, ky) - масштабирование;
// Mapping (различные виды отражений) - по желанию, для создания матриц отражения можно использовать функцию Scaling.

// В приведённом примере используется конструктор матрицы из списка.
// Приветствуются идеи о других способах создания матриц.
// Например, вызов функции, создающей единичную матрицу,
// с последующим переопределением некоторых её коэффициентов.

#endif AFFINE_TRANSFORM_H
