#include <windows.h>
#include <windowsx.h>
#include "Sight.h"
#include "Hello.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{
	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� ��������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass(&wc);								// ����������� ������ wc

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Figure Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200,200,400,400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

// � �������� ������ ����������� ������ ���� ���������� ���������� - �������� ������ ������ Sight
// ��� ���������� �������� �������������� ����������� ��������� � �������, ������������� � ���� ������
Sight sight(30);
Hello hello(40);
LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch(msg)
	{
	case WM_PAINT:						// ��������� ��������� WM_PAINT ������������ ������ ���, ����� ��������� ��������� ��� ����������� �����������
		{
			HDC dc = GetDC(hWnd);		// ������� GetDC ���������� �������� ����������, � ������� �������� ���������� � ���, � ����� ���� ������������ �����, ������ ������� ������� ������� ���� hWnd, � ����� ����� ������ ��������� ������ ��������� ������� ������� � �.�.
			sight.Clear(dc);
			sight.Draw(dc);
			hello.Clear(dc);
			hello.Draw(dc);
			ReleaseDC(hWnd, dc);		// ������� ReleaseDC �������� �������, ��� ��������� � ����� hWnd �������� dc ������ �� �����
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_LEFT:
				{
					sight.Move(-2, 0);
					break;
				}
			case VK_RIGHT:
				{
					sight.Move(2, 0);
					break;
				}
			case VK_UP:
				{
					sight.Move(0, -2);
					break;
				}case VK_DOWN:
				{
					sight.Move(0, 2);
					break;
				}


			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			sight.MoveTo(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			sight.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			if (sight.IsDragging())
			{
				sight.Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				InvalidateRect(hWnd, nullptr, false);
			}
			return 0;
		}
	case WM_LBUTTONUP:
		{
			sight.StopDragging();
			return 0;
		}
	case WM_SIZE:
		{
			InvalidateRect(hWnd, nullptr, false);	// ������� InvalidateRect ��������� ������� ������� ���� hWnd ��������� �����������, � ���������� ���� ������������ ��������� ��������� WM_PAINT
			return 0;								// ����� ������� �� ���������� ����, ��� ����������� ���������� � ��� ���������� �������� ����
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_MOUSEWHEEL:
		{
		
			int minSize=1;
			int maxSize=50;
			sight.Sizeing(GET_WHEEL_DELTA_WPARAM(wParam),minSize,maxSize);
			InvalidateRect(hWnd, nullptr, false);
			
		return 0;
		}
	default:
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
	return 0;
}
