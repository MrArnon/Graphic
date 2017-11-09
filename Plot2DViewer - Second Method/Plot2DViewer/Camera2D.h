#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double X0, Y0;						// Экранные координаты начала мировой системы координат
	double px, py;						// Единицы масштаба мировой системы координат, выраженные в пикселях
	int W, H;							// Разрешение рабочей области окна
	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return (int)(X0+px*X);
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return (int)(Y0-py*Y);
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		return (X-X0)/px;
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		return -(Y-Y0)/py;
	}
	double L()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return (-X0)/px;
	}
	double R()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return (W-X0)/px;
	}
	double B()
	{
	return (Y0/py);
	}
	double T()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return (Y0-H)/py;
	}

private:
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
public:
	Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py)
	{
	}
	void Clear(HDC dc)
	{
		 RECT r;
		GetClientRect(WindowFromDC(dc),&r);
	Rectangle(dc,0,0,r.right,r.bottom);
		// Очистка рабочей области окна
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc),&r);
	    if(!(W>0 && H>0))
		{
		W= r.right+1;
		H=r.bottom+1;
	    }
		int W_old=W;
		int H_old=H;
		W= r.right+1;
		H=r.bottom+1;
		double KW=(double)W/W_old;
		double KH=(double)H/H_old;
		X0=(KW*X0);
		Y0=KW*px/py*Y0+(double)H/2*(KH-KW*px/py);
		px=(KW*px);
		py=(KH*py);
		
		
		
	
		// Данная процедура вызывается при изменении размеров окна
		// В ней задаются значения величин W, H, а также настраиваются значения параметров X0, Y0, px, py таким образом, чтобы обеспечить одинаковые масштабы по координатным осям
	}
	void MoveTo(double X, double Y)
	{
		posX=X;
		posY=Y;
		// Перемещение графического курсора (posX, posY)
		// Обратите внимание, что мы действуем в мировых координатах
	}
	void LineTo(HDC dc, double X, double Y)
	{
	   
		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		::LineTo(dc, WorldToScreenX(X),WorldToScreenY(Y));
		MoveTo(X,Y);
		// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
		// Обратите внимание, что мы действуем в мировых координатах
		// При отрисовке линии могут быть использованы WinApi функции
		// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)
	}
	void Axes(HDC dc)
	{
   MoveTo(L(),0);
	LineTo(dc,R(),0);

	MoveTo(0,T());
	LineTo(dc,0,B());

		// Отрисовка координатных осей
	}
};

#endif CAMERA_2D_H
