#include <windows.h>
#include <TCHAR.h>

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

	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);  	// ƒøº≠ ¡ˆ¡§

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
	static int startX, startY, oldX, oldY;
	static BOOL Drag;
	int endX, endY;

	switch (iMsg)
	{
	case WM_CREATE:
		startX = 50;
		startY = 50;
		Drag = FALSE;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd ,&ps);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, oldX, oldY);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		Drag = TRUE;
		break;

	case WM_LBUTTONUP:
		Drag = FALSE;
		break;

	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		if (Drag) {							//»ÚπŸ≈¡
			SetROP2(hdc, R2_XORPEN);		//∆Ê¿« XORø¨ªÍ
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));		//»Ú ∆Ê

			endX = LOWORD(lParam);
			endY = HIWORD(lParam);

			MoveToEx(hdc, startX,startY, NULL);		//∏« √≥¿Ωø°¥¬ µø¿œ¡°
			LineTo(hdc, oldX, oldY);				//¡ˆøÏ±‚ : ∞À¿∫πŸ≈¡(0) XOR»Ú ∆Ê(1) = »Ú º±(1)

			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, endX, endY);				//±◊∏Æ±‚ : »ÚπŸ≈¡(1) XOR»Ú ∆Ê(1) = ∞À¿∫º±(0)

			oldX = endX;
			oldY = endY;					//«ˆ¿ßƒ°∏¶ ¿Ã¿¸ ¡ˆ¡°¿∏∑Œ ¿˙¿Â
		}
		ReleaseDC(hwnd, hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
