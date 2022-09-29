#include <windows.h>
#include <TCHAR.h>
#include "resource.h"

#define LINE 1
#define ELLIPSE 2
#define RECTANGLE 3

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);  	// 커서 지정

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU4);
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

class Object {
public:
	int startX, startY, endX, endY;
	int kind;
	Object(int sx = 0, int sy = 0, int ex = 0, int ey = 0) {
		startX = sx;
		startY = sy;
		endX = ex;
		endY = ey;
	}
	virtual void Draw(HDC hdc) {

	}
};

class Line : public Object{
public:
	Line(int sx, int sy, int ex, int ey) : Object(sx, sy, ex, ey){

	}
	void Draw(HDC hdc) {
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, endX, endY);
	}
};

class Circle : public Object {
public:
	Circle(int sx, int sy, int ex, int ey) : Object(sx, sy, ex,ey){}
	void Draw(HDC hdc) {
		Ellipse(hdc, startX, startY, endX, endY);
	}
};

class Recta : public Object {
public:
	Recta(int sx, int sy, int ex, int ey) : Object(sx, sy, ex, ey){}
	void Draw(HDC hdc) {
		Rectangle(hdc, startX, startY, endX, endY);
	}
};

Object* inform[200];
int count;

void DrawAllObjects(HDC hdc) {
	
	Object* p;
	int i;

	for (i = 0; i < count; i++) {
		p = inform[i];
		p->Draw(hdc);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int startX, startY, endX, endY;
	static int oldX, oldY;
	static BOOL Drag;
	static int object_mode;
	switch (iMsg)
	{
	case WM_CREATE:
		object_mode = LINE;
		Drag = FALSE;
		count = 0;
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		DrawAllObjects(hdc);
		EndPaint(hwnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		startX = oldX = LOWORD(lParam);
		startY = oldY = HIWORD(lParam);
		Drag = TRUE;
		break;

	case WM_LBUTTONUP:
		Drag = FALSE;
		switch (object_mode) {
			case LINE:
				inform[count] = new Line(startX, startY, oldX, oldY);
				break;
			case ELLIPSE:
				inform[count] = new Circle(startX, startY, oldX, oldY);
				break;
			case RECTANGLE:
				inform[count] = new Recta(startX, startY, oldX, oldY);
				break;
		}
		count++;
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_LINE:
			object_mode = LINE;
			break;
		case ID_ELLIPSE:
			object_mode = ELLIPSE;
			break;
		case ID_RECTANGLE:
			object_mode = RECTANGLE;
			break;
		}
		break;

	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		if (Drag) {
			SetROP2(hdc, R2_NOTXORPEN);
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);
			switch (object_mode) {
			case LINE:
				MoveToEx(hdc, startX, startY, NULL);
				LineTo(hdc, oldX, oldY);
				MoveToEx(hdc, startX, startY, NULL);
				LineTo(hdc, endX, endY);
				break;
			case ELLIPSE:
				Ellipse(hdc, startX, startY, oldX, oldY);
				Ellipse(hdc, startX, startY, endX, endY);
				break;
			case RECTANGLE:
				Rectangle(hdc, startX, startY, oldX, oldY);
				Rectangle(hdc, startX, startY, endX, endY);
				break;
			}
			oldX = endX;
			oldY = endY;
		}
		ReleaseDC(hwnd, hdc);
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
