#include <windows.h>
#include <TCHAR.h>
#include <math.h>

#define ITEMNUM 30
int itemX[ITEMNUM], itemY[ITEMNUM], radius[ITEMNUM];
int startX, startY;
BOOL finish;

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

float LengthPts(int x1, int y1, int x2, int y2) {
	return(sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}

BOOL InCircle(int x, int y, int mx, int my) {
	if (LengthPts(x, y, mx, my) < 50) {
		return true;
	}
	else {
		return false;
	}
}

BOOL Collision(int x1, int y1, int r1, int x2, int y2, int r2) {
	if (r1 + r2 > LengthPts(x1, y1, x2, y2)) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		startX = 0;
		startY = 0;
		ItemGenerator(hwnd);
		finish = FALSE;
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		DrawItem(hdc);

		Ellipse(hdc, startX - 50, startY - 50. startX + 50, startY + 50);
		EndPaint(hwnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (InCircle(startX, startY, mx, my)) {
			Selection = TRUE;
		}
		break;

	case WM_LBUTTONUP:
		Selection = FALSE;
		break;

	case WM_MOUSEMOVE:
		if (finish) {
			break;
		}
		hdc = GetDC(hwnd);
		if (Selection) {
			HBRUSH oldBrush;
			HPEN oldPen;
			oldPen = (HPEN)SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
			oldBrush = (HBRUSH)SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH);

			mx = LOWORD(lParam);
			my = HIWORD(lParam);

			if (CheckCollision(mx, my, 50)) {
				InvalidateRgn(hwnd, NULL, TRUE);
			}

			SetROP2(hdc, R2_XORPEN);
			Ellipse(hdc, startX - 50, startY - 50, startX + 50, startY + 50);
			Ellipse(hdc, mx - 50, my - 50, mx + 50, my + 50);

			SelectObject(hdc, oldPen);
			SelectObject(hdc, oldBrush);
			startX = mx;
			startY = my;
		}
		ReleaseDC(hwnd, hdc);
		GetClientRect(hwnd, &rect);
		if (InCircle(startX, startY, rect.right, rect.bottom)) {
			Finish(hwnd);
		}
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
