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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	RegisterClass(&WndClass);
	hwnd = CreateWindow(
		_T("Window Class Name"),
		_T("Window Class Name"),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		1000,
		1000,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

COLORREF ColorSelection(HWND hwnd, COLORREF oldColor) {
	COLORREF tmp[16];
	CHOOSECOLOR COLOR;

	for (int i = 0; i < 16; i++) {
		tmp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	memset(&COLOR, 0, sizeof(CHOOSECOLOR));
	COLOR.lStructSize = sizeof(CHOOSECOLOR);
	COLOR.hwndOwner = hwnd;
	COLOR.lpCustColors = tmp;
	COLOR.Flags = CC_FULLOPEN;

	if (ChooseColor(&COLOR) != 0) {
		return COLOR.rgbResult;
	}
	else {
		return oldColor;
	}
}

class Object {
public:
	int startX, startY, endX, endY;
	int kind;
	COLORREF PenColor = RGB(0, 0, 0), FaceColor = RGB(255, 255, 255);
	Object(int sx, int sy, int ex, int ey, int k) {
		startX = sx; startY = sy; endX = ex; endY = ey; kind = k;
	}

	virtual void Draw(HDC hdc) {

	}
};

class Line : public Object {
public:
	Object* ob;
	Line(int sx, int sy, int ex, int ey, int k) :Object(sx, sy, ex, ey, k) {
		ob = new Object(sx, sy, ex, ey, k);
	}
	void Draw(HDC hdc) {
		MoveToEx(hdc, ob->startX, ob->startY, NULL);
		LineTo(hdc, ob->endX, ob->endY);
	}
};

class Ellipse1 : public Object {
public:
	Object* ob;
	Ellipse1(int sx, int sy, int ex, int ey, int k) : Object(sx, sy, ex, ey, 2) {
		ob = new Object(sx, sy, ex, ey, k);
	}
	void Draw(HDC hdc) {
		Ellipse(hdc, ob->startX, ob->startY, ob->endX, ob->endY);
	}
};

class Rectangle1 : public Object {
public:
	Object* ob;
	Rectangle1(int sx, int sy, int ex, int ey, int k) : Object(sx, sy, ex, ey, 3) {
		ob = new Object(sx, sy, ex, ey, k);
	}
	void Draw(HDC hdc) {
		Rectangle(hdc, ob->startX, ob->startY, ob->endX, ob->endY);
	}
};


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen;
	HBRUSH hBrush;
	CHOOSECOLOR COLOR;
	static int object_mode = 0;
	static COLORREF oldColor = RGB(255, 255, 255);
	static COLORREF temp[16], PenColor = RGB(0, 0, 0), FaceColor = RGB(255, 255, 255);

	static bool isClick = false;
	static int sX, sY, eX, eY;
	static int FigureCount = 0;

	struct Object1
	{
		int kind;
		COLORREF PenColor = RGB(0, 0, 0), FaceColor = RGB(255, 255, 255);
	};

	static Object1 object[200];

	static Object* inform[200];

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case  WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_PENCOLOR:
			ColorSelection(hwnd, oldColor);
			break;
		case ID_FACECOLOR:
			ColorSelection(hwnd, oldColor);
			break;
		case ID_LINE:
			for (int i = FigureCount; i < 200; i++)
				object[i].kind = 1;
			break;
		case ID_ELLIPSE:
			for (int i = FigureCount; i < 200; i++)
				object[i].kind = 2;
			break;
		case ID_RECTANGLE:
			for (int i = FigureCount; i < 200; i++)
				object[i].kind = 3;
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		//hdc = GetDC(hwnd);
		isClick = true;
		if (0 != FigureCount) {
			inform[FigureCount]->startX = sX = LOWORD(lParam);
			inform[FigureCount]->startY = sY = HIWORD(lParam);
		}

		//ReleaseDC(hwnd, hdc);
		break;

	case WM_LBUTTONUP:
		isClick = false;
		if (0 != FigureCount) {
			inform[FigureCount]->endX = eX = LOWORD(lParam);
			inform[FigureCount]->endY = eY = HIWORD(lParam);
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		FigureCount++;
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);


		for (int i = 1; i < FigureCount; i++)
		{
			hPen = CreatePen(PS_SOLID, 1, object[i].PenColor);
			SelectObject(hdc, hPen);
			
			hBrush = CreateSolidBrush(object[i].FaceColor);
			SelectObject(hdc, hBrush);
			Line line(sX, sY, eX, eY, inform[i]->kind);
			Ellipse1 el(sX, sY, eX, eY, inform[i]->kind);
			Rectangle1 rect(sX, sY, eX, eY, inform[i]->kind);
			switch (inform[i]->kind){
			
			case 1:
				line.Draw(hdc);
				break;
			case 2:
				el.Draw(hdc);
				break;
			case 3:
				rect.Draw(hdc);
				break;
			}
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
