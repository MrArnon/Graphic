#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double X0, Y0;						// �������� ���������� ������ ������� ������� ���������
	double px, py;						// ������� �������� ������� ������� ���������, ���������� � ��������
	int W, H;							// ���������� ������� ������� ����
	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return (int)(X0+px*X);
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return (int)(Y0-py*Y);
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return (X-X0)/px;
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return -(Y-Y0)/py;
	}
	double L()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return (-X0)/px;
	}
	double R()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	{
		return (W-X0)/px;
	}
	double B()
	{
	return (Y0/py);
	}
	double T()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	{
		return (Y0-H)/py;
	}

private:
	double posX, posY;					// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
public:
	Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py)
	{
	}
	void Clear(HDC dc)
	{
		 RECT r;
		GetClientRect(WindowFromDC(dc),&r);
	Rectangle(dc,0,0,r.right,r.bottom);
		// ������� ������� ������� ����
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
		
		
		
	
		// ������ ��������� ���������� ��� ��������� �������� ����
		// � ��� �������� �������� ������� W, H, � ����� ������������� �������� ���������� X0, Y0, px, py ����� �������, ����� ���������� ���������� �������� �� ������������ ����
	}
	void MoveTo(double X, double Y)
	{
		posX=X;
		posY=Y;
		// ����������� ������������ ������� (posX, posY)
		// �������� ��������, ��� �� ��������� � ������� �����������
	}
	void LineTo(HDC dc, double X, double Y)
	{
	   
		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		::LineTo(dc, WorldToScreenX(X),WorldToScreenY(Y));
		MoveTo(X,Y);
		// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
		// �������� ��������, ��� �� ��������� � ������� �����������
		// ��� ��������� ����� ����� ���� ������������ WinApi �������
		// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
	}
	void Axes(HDC dc)
	{
   MoveTo(L(),0);
	LineTo(dc,R(),0);

	MoveTo(0,T());
	LineTo(dc,0,B());

		// ��������� ������������ ����
	}
};

#endif CAMERA_2D_H
