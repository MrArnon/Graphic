#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

using namespace std;


template <typename Cell = double>
class Matrix
{
private:
	int size;
	int rows;
	int cols;
	Cell **cells;
	void AllocateCells(int,int);
	void FreeCells();
public:
	Matrix() : size(0), cells(nullptr) {}	// Конструктор по умолчанию
	Matrix(const Matrix&);					// Конструктор копирования
	Matrix(int,int);							// Конструктор нулевой матрицы
	Matrix(int,int, Cell*);						// Конструктор матрицы из списка
	Matrix(int, int, vector<double>);
	~Matrix();								// Деструктор

	Cell &operator()(int i, int j) { return cells[i-1][j-1]; }
	
	Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
	Matrix  operator + (const Matrix&);		// Сложение матриц
	Matrix  operator - (const Matrix&);		// Вычитание матриц
	Matrix  operator * (const Matrix&);		// Умножение матриц

	friend istream& operator >> <> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
	//friend ostream& operator << <> (ostream&,  const Matrix&);	// Перегрузка оператора << для вывода матрицы
	friend ostream& operator << <> (ostream& fo, const Matrix<Cell>& M);
};


template <typename Cell>
Matrix<Cell>::Matrix(int Rows, int Cols, vector<double> List)
{
	AllocateCells(Rows, Cols);
	int r = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			cells[i][j] = List[r];
			r++;
			//list = list->next;
		}
}
template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.rows,M.cols);
	for (int i=0; i<rows; i++)
	for (int j=0; j<cols; j++)
		cells[i][j] = M.cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int Rows,int Cols)
{
	AllocateCells(Rows, Cols);
	for (int i=0; i<rows; i++)
	for (int j=0; j<cols; j++)
		cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int Rows,int Cols, Cell* list)
{
	//Matrix<Cell> res(Size);
	//AllocateCells(M.rows, M.cols);
	AllocateCells(Rows, Cols);
	int r = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			cells[i][j] = list[r];
			r++;
			//list = list->next;
		}
	//return res;
	/* ... */
}

template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	if ( rows != M.rows || cols != M.cols )
	{
		FreeCells();
		AllocateCells(M.rows,M.cols);
	}
	for (int i=0; i<rows; i++)
	for (int j=0; j<cols; j++)
		cells[i][j] = M.cells[i][j];
	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (rows == M.rows && cols == M.cols)
	{
		for (int i=0; i<rows; i++)
		for (int j=0; j<cols; j++)
			res.cells[i][j] += M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (rows == M.rows && cols == M.cols)
	{
		for (int i = 0; i<rows; i++)
			for (int j = 0; j<cols; j++)
				res.cells[i][j] -= M.cells[i][j];
	}
	return res;
	/* ... */
	//return Matrix();
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{

	
	Matrix<Cell> res(*this);
	//Matrix<Cell> S(rows,cols);
	int minR, minC;
	if (rows >= M.rows) minR = M.rows;
	else minR = rows;

	if (cols >= M.cols) minC = M.cols;
	else minC = cols;

	Matrix<Cell> S(minR, minC);

	if (rows == M.cols && cols == M.rows)
//	if(rows == M.cols)
	{
	
		for (int i = 0; i<rows; i++)
			for (int j = 0; j < cols; j++)
			{
				double temp = 0;
				for (int k = 0; k < cols; k++)
				{
				//	S.cells[i][j] += res.cells[i][k] * M.cells[k][j];
					temp+= res.cells[i][k] * M.cells[k][j];
					//cout << "!!!!!!" << res.cells[i][k];
				}
				S.cells[i][j] = temp;
			}
			}
	return S;
	/* ... */
	//return Matrix();
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int Rows,int Cols)
{
	cells = new Cell*[Rows];
	for (int i=0; i<Rows; i++)
		cells[i] = new Cell[Cols];
	rows = Rows;
	cols = Cols;
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	for (int i=0; i<rows; i++)
		delete cells[i];
	delete cells;
	cols = 0;
	rows = 0;
}


template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i=0; i<M.rows; i++)
	for (int j=0; j<M.cols; j++)
		fi >> M.cells[i][j];
	return fi;
}

template <typename Cell>
ostream& operator << <>(ostream& fo, const Matrix<Cell>& M)
{
	for (int i=0; i<M.rows; i++)
	{
		fo << "  ";
		for (int j=0; j<M.cols; j++)
			fo << M.cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}



#endif MATRIX_H
