#include <windows.h>
#include <math.h>
#include <TCHAR.h>
#define BSIZE 20

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
double LengthPts(int x1, int y1, int x2, int y2) {
	return(sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}
BOOL InCircle(int x, int y, int mx, int my) {
	if (LengthPts(x, y, mx, my) < BSIZE) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int mx, my;
	static RECT rectView;
	static int startX, startY, oldX, oldY;
	static BOOL Selection;
	static BOOL Drag;
	static int moveX, moveY;
	static int count = 0;
	int endX, endY;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;


	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		startX = oldX = 20;
		startY = oldY = 20;
		Selection = FALSE; 
		Drag = FALSE;
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		if (Selection) {
			hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		}
		//MoveToEx(hdc, startX, startY, NULL);
		//LineTo(hdc, oldX, oldY);
		Ellipse(hdc, startX - BSIZE, startY - BSIZE, startX + BSIZE, startY + BSIZE);
		EndPaint(hwnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (InCircle(startX, startY, mx, my)) {
			Selection = TRUE;
			Drag = TRUE;
			oldX = startX = LOWORD(lParam);
			oldY = startY = HIWORD(lParam);
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		break;

	case WM_LBUTTONUP:
		moveX = (oldX - startX) / 15;
		moveY = (oldY - startY) / 15;
		Selection = FALSE;
		Drag = FALSE;
		oldX = startX;
		oldY = startY;
		SetTimer(hwnd, 1, 30, NULL);
		InvalidateRgn(hwnd, NULL, TRUE);
		break;


	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		if (Drag && Selection) {
			SetROP2(hdc, R2_XORPEN);
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, oldX, oldY);
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, endX, endY);
			oldX = endX;
			oldY = endY;
		}
		ReleaseDC(hwnd, hdc);
		break;

	case WM_TIMER:
		count++;
		startX += moveX;
		startY += moveY;
		InvalidateRect(hwnd, NULL, TRUE);
		if (count == 15) {
			KillTimer(hwnd, 1);
			InvalidateRect(hwnd, NULL, TRUE);
			count = 0;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
