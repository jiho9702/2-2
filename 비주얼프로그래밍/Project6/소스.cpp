#include <Windows.h>
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU_KIND);
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
	
	//virtual Draw(HDC hdc);
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen;
	HBRUSH hBrush;
	CHOOSECOLOR COLOR;
	static int object_mode = 0;

	static COLORREF temp[16], PenColor = RGB(0, 0, 0), FaceColor = RGB(255, 255, 255);	

	static bool isClick = false;
	static int startX, startY, endX, endY;
	static int FigureCount = 0;

	Object* inform[200] = {};

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case  WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_PENCOLOR:
			for (int i = 0; i < 16; i++)
				temp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);
			memset(&COLOR, 0, sizeof(CHOOSECOLOR));
			COLOR.lStructSize = sizeof(CHOOSECOLOR);
			COLOR.hwndOwner = hwnd;
			COLOR.lpCustColors = temp;
			COLOR.Flags = CC_FULLOPEN;
			if (ChooseColor(&COLOR) != 0)
			{

				for (int i = FigureCount; i < 100; i++)
					inform[i]->PenColor = COLOR.rgbResult;
			}
			break;
		case ID_FACECOLOR:
			for (int i = 0; i < 16; i++)
				temp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);
			memset(&COLOR, 0, sizeof(CHOOSECOLOR));
			COLOR.lStructSize = sizeof(CHOOSECOLOR);
			COLOR.hwndOwner = hwnd;
			COLOR.lpCustColors = temp;
			COLOR.Flags = CC_FULLOPEN;
			if (ChooseColor(&COLOR) != 0)
			{
				for (int i = FigureCount; i < 100; i++)
					inform[i]->FaceColor = COLOR.rgbResult;
			}
			break;
		case ID_LINE:
			for (int i = FigureCount; i < 100; i++)
				inform[i]->kind = 1;
			break;
		case ID_ELLIPSE:
			for (int i = FigureCount; i < 100; i++)
				inform[i]->kind = 2;
			break;
		case ID_RECTANGLE:
			for (int i = FigureCount; i < 100; i++)
				inform[i]->kind = 3;
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		//hdc = GetDC(hwnd);
		isClick = true;
		inform[FigureCount]->startX = startX = LOWORD(lParam);
		inform[FigureCount]->startY = startY = HIWORD(lParam);

		//ReleaseDC(hwnd, hdc);
		break;

	case WM_LBUTTONUP:
		isClick = false;
		inform[FigureCount]->endX = endX = LOWORD(lParam);
		inform[FigureCount]->endY = endY = HIWORD(lParam);
		InvalidateRgn(hwnd, NULL, TRUE);
		FigureCount++;
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);


		for (int i = 0; i <= FigureCount; i++)
		{
			hPen = CreatePen(PS_SOLID, 1, inform[i]->PenColor);
			SelectObject(hdc, hPen);
			hBrush = CreateSolidBrush(inform[i]->FaceColor);
			SelectObject(hdc, hBrush);
			switch (inform[i]->kind)
			{
			case 1:
				MoveToEx(hdc, inform[i]->startX, inform[i]->startY, NULL);
				LineTo(hdc, inform[i]->endX, inform[i]->endY);
				break;
			case 2:
				Ellipse(hdc, inform[i]->startX, inform[i]->startY, inform[i]->endX, inform[i]->endY);
				break;
			case 3:
				Rectangle(hdc, inform[i]->startX, inform[i]->startY, inform[i]->endX, inform[i]->endY);
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
