// ������� : 15
/*
������������� ������� ���������
����� ������ ������� �������
��������������� � ����������� ��������� ������� � ������ ������ ����
*/

#include <windows.h>
#include <windowsx.h>
#include "Data.h"
#include "Matrix.h"
#include "AffineTransform.h"
#include "Model2D.h"
#include "Scene2D.h"
#include "Vector3D.h"
#include "Model3D.h"
#include "Camera3D.h"
#include "Scene3D.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{
	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� �������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
	wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wc.hbrBackground = ( HBRUSH ) ( 6 );
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = ( LPCSTR )"MainWindowClass"; // ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass( &wc );					        // ����������� ������ wc

	HWND hWnd = CreateWindow
	(												// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Plot2D Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200,200,400,400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr,nullptr,hInstance,nullptr
	);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while ( GetMessage( &msg, nullptr, 0, 0 ) )				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg ); 					// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

// � �������� ������ ����������� ������ ���� ���������� ���������� - �������� ������ ������ Scene2D
// ��� ���������� �������� �������������� ����������� ��������� � �������, ������������� � ���� ������
Matrix<> Vertices(4, 4, Vert);
Matrix<int> Verges(4, 3, Verg);
Scene3D Scene( L, R, B, T, Verges, Vertices );

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch( msg )
	{
	case WM_PAINT:
		{
			HDC dc = GetDC( hWnd );
			Scene.Clear( dc );				// ����� �������������� � ������ Camera2D ������, ����������� �� ������� ������� ������� ���� hWnd
			//Scene.Plot( dc, Sinusoid );		// ����� �������������� � ������ Scene2D ������, ����������� �� ��������� ������� ���������
			//Scene.ParametricPlot(dc, XEllipt, YEllipt, U, V ,c , t_min, t_max);
			Scene.Render(dc);
			ReleaseDC( hWnd,dc );
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
	case WM_LBUTTONDOWN:
		{
			Scene.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			if (Scene.IsDragging())
			{
				Scene.Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				InvalidateRect(hWnd, nullptr, false);
			}
			return 0;
		}

	

	case WM_LBUTTONUP:
		{
			Scene.StopDragging();
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_LEFT : {Scene.model.Apply(Translation(-0.5, 0, 0));  break;}
			case VK_RIGHT : {Scene.model.Apply(Translation(0.5, 0, 0));  break;}
			case VK_UP : {Scene.model.Apply(Translation(0, 0.5, 0));  break;}
			case VK_DOWN : {Scene.model.Apply(Translation(0, -0.5, 0));  break;}
			case 0x31: {Scene.model.Apply(RotationX( M_PI/90)); break;}//1
			case 0x32: {Scene.model.Apply(RotationX(-M_PI/90)); break;}//2
			case 0x33: {Scene.model.Apply(RotationY( M_PI/90)); break;}//3
			case 0x34: {Scene.model.Apply(RotationY(-M_PI/90)); break;}//4
			case 0x35: {Scene.model.Apply(RotationZ( M_PI/90)); break;}//5
			case 0x36: {Scene.model.Apply(RotationZ(-M_PI/90)); Scene.UpdateCamera();break;}//6
			case 0x57: {Scene.model.Apply(Scaling( 1.5, 1.5, 1.5));break;}//W
			case 0x53: {Scene.model.Apply(Scaling( 2.0/3.0, 2.0/3.0, 2.0/3.0)); break;}//S
			case 0x51: {Scene.model.Apply(Mapping( true)); break;}//Q
			case 0x45: {Scene.model.Apply(Mapping( false)); break;}//E
			case 0x46: {
				double X1 =Scene.model.GetVertexX(0);
				double X2 =Scene.model.GetVertexX(1);
				double Y1= Scene.model.GetVertexY(0);
				double Y2= Scene.model.GetVertexY(1);
				double Z1 = Scene.model.GetVertexZ(0);
				
				double Z2 = Scene.model.GetVertexZ(1);
				double A=X2-X1;
				double B=Y2-Y1;
				double C=Z2-Z1;
				Matrix<>Affin=Identity3D();
						Affin=Affin * Translation(X1,Y1,Z1);
						Affin=Affin* RotationX(B,C);
						Affin=Affin* RotationZ(A, sqrt(B*B+C*C));
						Affin=Affin*RotationX((-M_PI/90));
						Affin=Affin* RotationZ(A, -sqrt(B*B+C*C));
						Affin=Affin* RotationX(B,-C);
					    Affin=Affin * Translation(-X1,-Y1,-Z1);
					    Scene.model.Apply(Affin);  break;
					    }//F
			};
			
	
			InvalidateRect(hWnd, nullptr, false);


			return 0;
		}
	

	case WM_MOUSEWHEEL:
		{
			POINT P;
			P.x = GET_X_LPARAM(lParam);
			P.y = GET_Y_LPARAM(lParam);
			ScreenToClient(hWnd, &P);

			Scene.Scaling(P.x, P.y, GET_WHEEL_DELTA_WPARAM(wParam));
			InvalidateRect(hWnd, nullptr, false);
			return 0;

		}
	case WM_SIZE:
		{
			HDC dc = GetDC( hWnd );
			Scene.SetResolution( dc );
			ReleaseDC( hWnd, dc );
			InvalidateRect(hWnd,nullptr,false);
			return 0;
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

	default:
		{
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
	}
	return 0;
}
