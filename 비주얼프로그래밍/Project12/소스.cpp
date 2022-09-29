#include <windows.h>
#include <TCHAR.h>
#include <math.h>

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

float LengthPts(int x1, int y1, int x2, int y2)							// sqrt 수학함수
{
	return (sqrt((float)(x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}


bool InCircle(int startX, int startY, int mx, int my) {
	if (LengthPts(startX, startY, mx, my) < BSIZE) {
		return true;
	}
	else {
		return false;
	}
}

double check(int startX, int startY, int x, int y) {
	double distance = sqrt(pow((startX - x), 2) + pow((startY - y), 2));
	return distance;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rectView;
	static int x, y;
	static int startX, startY, oldX, oldY;
	static BOOL Drag, Selection, MouseUPP;
	int endX, endY;
	int mx, my;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static int movex, movey;
	static int count = 0;


	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		startX = oldX = x = 20;
		startY = oldY = y = 20;
		MouseUPP = FALSE;
		Selection = FALSE;
		Drag = FALSE;
		break;

	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (InCircle(x, y, mx, my)) {
			Selection = TRUE;
			Drag = TRUE;
			oldX = startX = LOWORD(lParam);
			oldY = startY = HIWORD(lParam);
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		
		break;

	case WM_LBUTTONUP:
		movex = (oldX - startX) / 20;
		movey = (oldY - startY) / 20;
		MouseUPP = TRUE;
		Selection = FALSE;
		Drag = FALSE;
		oldX = startX;
		oldY = startY;
		SetTimer(hwnd, 1, 50, NULL);
		InvalidateRgn(hwnd, NULL, TRUE);
		break;


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (Selection) {
			Ellipse(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
		}
		Rectangle(hdc, 0, 0, 40, 40);
		Ellipse(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
		
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if(!Selection && check(startX, startY, x, y) > 40) {
			Ellipse(hdc, startX - BSIZE, startY - BSIZE, startX + BSIZE, startY + BSIZE);
			/*Ellipse(hdc, startX - BSIZE-28, startY - BSIZE - 28, startX + BSIZE - 28, startY + BSIZE - 28);*/
		}
		
		if (!Selection && check(startX, startY, x, y) <= 40 && check(startX, startY, x, y)>0) {
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, startX - BSIZE, startY - BSIZE, startX + BSIZE, startY + BSIZE);
			TextOut(hdc, x, y, _T("깡통"), _tcslen(_T("깡통")));
		}
		
		EndPaint(hwnd, &ps);
		break;

	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		
		if (Selection) {
			mx = LOWORD(lParam);
			my = HIWORD(lParam);

			x = mx;
			y = my;

			InvalidateRgn(hwnd, NULL, TRUE);
		}

		if (Drag && Selection) {
			SetROP2(hdc, R2_XORPEN);
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
			SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));

			endX = LOWORD(lParam);
			endY = HIWORD(lParam);

			Ellipse(hdc, oldX - BSIZE, oldY - BSIZE, oldX + BSIZE, oldY + BSIZE);
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, oldX, oldY);

			Ellipse(hdc, endX - BSIZE, endY - BSIZE, endX + BSIZE, endY + BSIZE);
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, endX, endY);

			oldX = endX;
			oldY = endY;
		}
		ReleaseDC(hwnd, hdc);
		break;

	case WM_TIMER:
		count++;
		startX += movex;
		startY += movey;
		InvalidateRgn(hwnd, NULL, TRUE);
		if (check(startX, startY, x, y) <= 40) {
			KillTimer(hwnd, 1);
			InvalidateRgn(hwnd, NULL, TRUE);
			count = 0;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
