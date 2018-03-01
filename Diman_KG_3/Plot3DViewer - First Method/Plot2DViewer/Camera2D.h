#ifndef CAMERA_2D_H
#define CAMERA_2D_H



class Camera2D
{
protected:
	double L, R, B, T;					// ������� ���������� ������ ������� ������� ����
	int W, H;							// ���������� ������� ������� ����
	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return (X-L)/(R-L)*W;
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return ( T - Y ) / ( T - B ) * H;
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return ((X+0.5)*(R-L))/W+L;
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return T-((Y+0.5)*(T-B))/H;
	}
private:
	double posX, posY;					// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
	bool isDragging;
	double prevX, prevY;
public:
	Camera2D(double L, double R, double B, double T) : L(L), R(R), B(B), T(T)
	{
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		Rectangle(dc,r.left, r.top, r.right, r.bottom);
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		W=r.right-r.left+1;
		H=r.bottom-r.top+1;
		double nL = ( L + R ) / 2 - ( T - B ) / 2 * W / H; 
		double nR = ( L + R ) / 2 + ( T - B ) / 2 * W / H; 
		L = nL; 
		R = nR;
		
		                                                                                                            
	}
	void MoveTo(double X, double Y)
	{
		// ����������� ������������ ������� (posX, posY)
		// �������� ��������, ��� �� ��������� � ������� �����������
		posX=WorldToScreenX(X);
		posY=WorldToScreenY(Y);
	}
	void LineTo(HDC dc, double X, double Y)
	{
		// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
		// �������� ��������, ��� �� ��������� � ������� �����������
		// ��� ��������� ����� ����� ���� ������������ WinApi �������
		// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
   		MoveToEx(dc,posX,posY,nullptr);
		MoveTo(X,Y);
		::LineTo(dc,posX,posY);
		}

	void StartDragging(double X, double Y)
	{
		isDragging = true;
		prevX=X;
		prevY=Y;
	}
	void Drag(double X, double Y)
	{
		double a = ScreenToWorldX(X);
		double b = ScreenToWorldX(prevX);
		double c = a-b;
		double d = ScreenToWorldX(X-prevX);
		L-= ( ScreenToWorldX(X)-ScreenToWorldX(prevX));
		R-= ( ScreenToWorldX(X)-ScreenToWorldX(prevX));

		B-= ScreenToWorldY(Y)-ScreenToWorldY(prevY);
		T-= ScreenToWorldY(Y)-ScreenToWorldY(prevY);
		
		prevX=X;
		prevY=Y;
	}
	void StopDragging()
	{
		isDragging = false;
	}
	bool IsDragging()
	{
		return isDragging;
	}
	void Scaling(double X, double Y, double delta)
	{
		delta = delta>0?1.1:0.9;
		double Xw = ScreenToWorldX(X);
		double Yw = ScreenToWorldY(Y);
		L = Xw-(Xw-L)/delta;
		R = Xw-(Xw-R)/delta;
		B = Yw-(Yw-B)/delta;
		T = Yw-(Yw-T)/delta;
	}
	void Axes(HDC dc)
	{
		MoveTo(L,0);
		LineTo(dc,R,0);
		MoveTo(0,T);
		LineTo(dc,0,B);
	}
};

#endif CAMERA_2D_H
