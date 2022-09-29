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

	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);  	// Ŀ�� ����

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
		if (Drag) {							//�����
			SetROP2(hdc, R2_XORPEN);		//���� XOR����
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));		//�� ��
			SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));	//������ ���� ����

			endX = LOWORD(lParam);   //���콺 �̵��� ���� ��ǥ
			endY = HIWORD(lParam);

			Ellipse(hdc, startX, startY, oldX, oldY);	//�� �����

			Ellipse(hdc, startX, startY, endX, endY);	//�� �׸���

			oldX = endX;
			oldY = endY;					//����ġ�� ���� �������� ����

		}
		ReleaseDC(hwnd, hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
