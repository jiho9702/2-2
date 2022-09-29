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
	static int startX, startY, oldX, oldY;
	/*static RECT rect[3] = { {100, 100, 200, 200}, {200, 200, 300,300}, {300, 300, 400, 400} };*/
	static BOOL Drag;
	int endX, endY;

	switch (iMsg)
	{
	case WM_CREATE:
		Drag = FALSE;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		/*for (int i = 0; i < 3; i++) {
			Ellipse(hdc, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);
		}*/
		Ellipse(hdc, startX, startY, oldX, oldY);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		oldX = startX = LOWORD(lParam);
		oldY = startY = HIWORD(lParam);
		Drag = TRUE;
		break;

	case WM_LBUTTONUP:
		Drag = FALSE;
		break;

	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		if (Drag) {							//흰바탕
			SetROP2(hdc, R2_XORPEN);		//펜의 XOR연산
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));		//흰 펜
			SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));	//도형속 색깔 지정

			endX = LOWORD(lParam);   //마우스 이동한 점의 좌표
			endY = HIWORD(lParam);

			Ellipse(hdc, startX, startY, oldX, oldY);	//원 지우기

			Ellipse(hdc, startX, startY, endX, endY);	//원 그리기

			oldX = endX;
			oldY = endY;					//현위치를 이전 지점으로 저장

		}
		ReleaseDC(hwnd, hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
