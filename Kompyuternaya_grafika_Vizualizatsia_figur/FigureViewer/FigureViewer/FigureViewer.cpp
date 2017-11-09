#include <windows.h>
#include <windowsx.h>
#include "Sight.h"
#include "Hello.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// прототип оконной процедуры
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// основная процедура
{
	// Первая составляющая часть основной процедуры - создание окна: сначала описывается оконный класс wc, затем создается окно hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// имя оконной процедуры, закрепленной за данным классом
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// идентификатор приложения, содержащий адрес начала выделенной ему области памяти
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// меню в оконном классе отсутствует
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// имя оконного класса, используемое при создании экземпляров окна
	RegisterClass(&wc);								// регистрация класса wc

	HWND hWnd = CreateWindow(						// hWnd - дескриптор, идентифицирующий окно; функция создания окна заполняет дескриптор hWnd ненулевым значением
		(LPCSTR)"MainWindowClass",					// имя оконного класса
		(LPCSTR)"Figure Viewer",					// заголовок окна
		WS_OVERLAPPEDWINDOW,						// стиль окна
		200,200,400,400,							// координаты на экране левого верхнего угла окна, его ширина и высота
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// Вторая составляющая часть основной процедуры - основной цикл обработки системных сообщений, который ожидает сообщения и рассылает их соответствующим окнам
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// функция GetMessage выбирает из очереди сообщение и заносит его в структуру msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// функция DispatchMessage оповещает систему о необходимости вызова оконной процедуры
	}

	return 0;
}

// В основном модуле объявляется только одна глобальная переменная - создаётся объект класса Sight
// Все дальнейшие действия осуществляются посредством обращения к методам, реализованным в этом классе
Sight sight(30);
Hello hello(40);
LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконная процедура принимает и обрабатывает все сообщения, отправленные окну
{
	switch(msg)
	{
	case WM_PAINT:						// системное сообщение WM_PAINT генерируется всякий раз, когда требуется отрисовка или перерисовка изображения
		{
			HDC dc = GetDC(hWnd);		// функция GetDC возвращает контекст устройства, в котором хранится информация о том, в какое окно производится вывод, каковы размеры рабочей области окна hWnd, в какой точке экрана находится начало координат рабочей области и т.п.
			sight.Clear(dc);
			sight.Draw(dc);
			hello.Clear(dc);
			hello.Draw(dc);
			ReleaseDC(hWnd, dc);		// функция ReleaseDC сообщает системе, что связанный с окном hWnd контекст dc больше не нужен
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
			InvalidateRect(hWnd, nullptr, false);	// функция InvalidateRect объявляет рабочую область окна hWnd требующей перерисовки, в результате чего генерируется системное сообщение WM_PAINT
			return 0;								// Таким образом мы добиваемся того, что перерисовка происходит и при уменьшении размеров окна
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
