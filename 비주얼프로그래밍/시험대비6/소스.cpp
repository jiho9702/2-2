#include <windows.h>
#include <TCHAR.h>
#define BSIZE 80	

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
	static int xi, yi;
	static int rect[4][8];
	static int x, y, flag;

	switch (iMsg)
	{
	case WM_CREATE:
		x = 0;
		y = 0;
		flag = 0;
		break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam) / BSIZE;
		y = HIWORD(lParam) / BSIZE;
		if (x < 8 && y < 4 && rect[y][x] == 0) {
			flag = 1-flag;
			if (flag == 1) {
				rect[y][x] = 1;
			}
			else {
				rect[y][x] = 2;
			}
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
		 
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (xi = 0; xi < 8; xi++) {
			for (yi = 0; yi < 4; yi++) {
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

		EndPaint(hwnd, &ps);
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
