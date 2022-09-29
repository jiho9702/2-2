#include <Windows.h>
#include<tchar.h>
#include<string.h>
#include<math.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;

	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");

	RegisterClass(&WndClass); //윈도우 클래스를 커널에 등록

	hwnd = CreateWindow( //윈도우 핸들값 반환
		_T("Window Class Name"), //윈도우 클래스 이름
		_T("홍길동의 첫 번째 윈도우"), //윈도우 타이틀이름
		WS_OVERLAPPEDWINDOW, //윈도우 스타일
		100, //윈도우 위치 x좌표
		100,//윈도우 위치 y좌표
		1000, //윈도우 가로크기
		600, //윈도우 세로크기
		NULL, //부모 윈도우핸들
		NULL, //메뉴핸들
		hInstance, //응용프로그램 인스턴스
		NULL); //생성 윈도우 정보

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
	HPEN redPen, blackPen, bluePen;
	static int temp = 0;
	static int  mX, mY;
	static int empty[4][8];
	static int circleX[4][8], circleY[4][8];
	static int circleColor[4][8];
	static int circleCount = 0;
	switch (iMsg)
	{
	case WM_CREATE:
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 8; j++)
			{
				circleX[i][j] = -100;
				circleY[i][j] = -100;
				circleColor[i][j] = 0;
				empty[i][j] = 0;
			}

		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		for (int i = 0; i < 5; i++)			//--------------프레임
		{
			MoveToEx(hdc, 0, i * 100, NULL);
			LineTo(hdc, 800, i * 100);
		}
		for (int i = 0; i < 9; i++)
		{
			MoveToEx(hdc, i * 100, 0, NULL);
			LineTo(hdc, i * 100, 400);
		}									//--------------프레임
		mX = LOWORD(lParam);
		mY = HIWORD(lParam);
		circleX[mY / 100][mX / 100] = (mX / 100) * 100;
		circleY[mY / 100][mX / 100] = (mY / 100) * 100;


		if (circleColor[mY / 100][mX / 100] == 0 && circleCount == 0 && empty[mY / 100][mX / 100] == 0) {
			empty[mY / 100][mX / 100] = 1;
			circleColor[mY / 100][mX / 100] = 1; //빨강
			circleCount = 1;
			empty[mY / 100][mX / 100] = 0;
		}
		else if (circleColor[mY / 100][mX / 100] == 0 && circleCount == 1 && empty[mY / 100][mX / 100] == 0) {
			empty[mY / 100][mX / 100] = 0;
			circleColor[mY / 100][mX / 100] = 2; //파랑
			circleCount = 0;
			empty[mY / 100][mX / 100] = 1;
		}
		else if (circleColor[mY / 100][mX / 100] == 2 && empty[mY / 100][mX / 100] == 0) {
			circleCount = 1;
			empty[mY / 100][mX / 100] = 0;
			circleColor[mY / 100][mX / 100] = 1;
			empty[mY / 100][mX / 100] = 1;

		}		
		
		//else if (circleColor[mY / 100][mX / 100] == 2 && isEmpty[mY / 100][mX / 100] == 0) {
		//	circleColor[mY / 100][mX / 100] = 1; //빨강
		//}
			
		blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		bluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 8; j++)
			{

				if (circleColor[i][j] == 1)
					SelectObject(hdc, redPen);
				else if (circleColor[i][j] == 2)
					SelectObject(hdc, bluePen);
				Ellipse(hdc, circleX[i][j], circleY[i][j], circleX[i][j] + 100, circleY[i][j] + 100);
			}
		ReleaseDC(hwnd, hdc);
		//InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		for (int i = 0; i < 5; i++)			//--------------프레임
		{
			MoveToEx(hdc, 0, i * 100, NULL);
			LineTo(hdc, 800, i * 100);
		}
		for (int i = 0; i < 9; i++)
		{
			MoveToEx(hdc, i * 100, 0, NULL);
			LineTo(hdc, i * 100, 400);
		}									//--------------프레임

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}