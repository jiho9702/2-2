#include <windows.h>
#include <TCHAR.h>
#include "resource.h"

#define BSIZE 80
#define ONE 1
#define TWO 2

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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	int xi, yi;
	static int rect[3][3];
	static int x, y, flag;
	static int a;
	static bool isClick;

	switch (iMsg)
	{
	case WM_CREATE:
		
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rect[j][i] = 0;
			}
		}
		flag = 0;
		a = 3;
		isClick = FALSE;
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ONE:
			a = ONE;
			break;

		case ID_TWO:
			a = TWO;
			break;

		default:
			break;
		}

	case WM_LBUTTONDOWN:

		isClick = TRUE;

		switch (a)
		{
		case 1:
			x = LOWORD(lParam) / BSIZE;
			y = HIWORD(lParam) / BSIZE;
			if (x < 3 && y < 3 && rect[y][x] == 0) {
				flag = 1 - flag;
				if (flag == 1) {
					rect[y][x] = 1;
				}
				else {
					rect[y][x] = 2;
				}
			}

		default:
			break;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		switch (a)
		{
		case 1:

			Rectangle(hdc, 250, 95, 300, 120);
			TextOut(hdc, 260, 100, _T("종료"), _tcslen(_T("종료")));

			for (xi = 0; xi < 3; xi++) {
				for (yi = 0; yi < 3; yi++) {
					Rectangle(hdc, xi * BSIZE, yi * BSIZE, (xi + 1) * BSIZE, (yi + 1) * BSIZE);
					if (rect[yi][xi]) {
						if (rect[yi][xi] == 1) {
							hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
						}
						else {
							hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
						}
						oldPen = (HPEN)SelectObject(hdc, hPen);

						Ellipse(hdc, xi * BSIZE, yi * BSIZE, (xi + 1) * BSIZE, (yi + 1) * BSIZE);
						SelectObject(hdc, oldPen);
					}
				}
			}
			break;
		

		default:
			break;
		}
		
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
