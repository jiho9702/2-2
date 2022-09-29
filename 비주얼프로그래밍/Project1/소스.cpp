#include <windows.h>
#include <math.h>
#include <TCHAR.h>

#define TRUE 1
#define FALSE 0

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

BOOL Catch(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < 20) return TRUE;
	else return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static POINT mouse, cat;
	static BOOL Drag;
	static int stepX, stepY, count;

	switch (iMessage)
	{
	case WM_CREATE:
		cat.x = 100; cat.y = 100;
		Drag = FALSE;
		count = 0;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (Drag)
		{
			TextOut(hdc, mouse.x, mouse.y, L"쥐", 1);
		}
		TextOut(hdc, cat.x, cat.y, L"고양이", 3);
		if (Catch(cat.x, cat.y, mouse.x, mouse.y))
		{
			KillTimer(hWnd, 1);
			stepX = NULL;
			stepY = NULL;
			MessageBeep(1);
			if (MessageBox(hWnd, TEXT("Catch You"), TEXT("Re-Game?"), MB_OKCANCEL) == IDOK)
			{
				return 0;
			}
			else exit(1);
		}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		Drag = TRUE;
		stepX = (mouse.x - cat.x) / 10;
		stepY = (mouse.y - cat.y) / 10;
		InvalidateRect(hWnd, NULL, TRUE);
		count = 0;
		SetTimer(hWnd, 1, 100, NULL);
		return 0;

	case WM_LBUTTONUP:
		Drag = FALSE;
		KillTimer(hWnd, 1);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_MOUSEMOVE:
		if (!Drag) return 0;
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		stepX = (mouse.x - cat.x) / 10;
		stepY = (mouse.y - cat.y) / 10;
		count = 0;
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_TIMER:
		count++;
		cat.x += stepX;
		cat.y += stepY;
		InvalidateRect(hWnd, NULL, TRUE);
		if (count == 10)
		{
			stepX = 0;
			stepY = 0;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(1);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
