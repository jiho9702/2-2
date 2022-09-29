#include <windows.h>
#include <TCHAR.H>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	hwnd;
	MSG 	msg;
	WNDCLASS	WndClass;
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



#define ITEMNUM 10
//애벌레 먹이의 개수

int board[22][22];
//게임판의 크기
int wormX[30], wormY[30];
//애벌레의 최대크기
int xDirect, yDirect, len;
//x축방향의 이동값, y축 방향의 이동값, 애벌레의 길이


void ItemGenerator()
//애벌레의 먹이를 만드는 함수이다.
{
	int i, x, y;
	
//정수형 변수 i, x, y 생성

	for (i = 0; i < ITEMNUM; i++)
		//전역변수로 입력한 ITEMNUM을 이용하여
		//10회를 반복하는 반복문을 실행해준다.
	{
		x = rand() % 20 + 1;
		y = rand() % 20 + 1;
		//벽을 제외하고 남는 20개의 공간중에서
		//먹이의 좌표를 랜덤으로 생성한다
		//+1이 들어가는 이유는 먹의의 좌표에
		//0값이 들어가면 벽과 겹치기 때문이다.
		if (board[y][x] == 0)
			board[y][x] = 2;
		//이렇게 생긴 먹의의 좌표값에 2를 넣어준다.
		else
		{
			i = i - 1;
			//먹이가 있는 위치에 먹이를 또 생성한경우
			//i값을 -1해주고 해당 반복문을 건너뛴다.
			continue;
		}
	}
	return;
}


void DrawGameBoard(HDC hdc)
//실질적으로 게임판에 대한 그림을 그리는 함수이다.
{
	int i, x, y;
	for (y = 0; y < 22; y++) {
		for (x = 0; x < 22; x++)
	//22*22의 공간에 대한 필요한 부분에
	//그림을 그리기 위해 이중반복문을 실행해준다.
		{
			switch (board[y][x])
			//board[y][x]에 들어간 값이
			{
			case -1:
			//-1이라면
				Rectangle(hdc, x * 20, y * 20, (x + 1) * 20, (y + 1) * 20);
			//속이 빈 가로 20 세로 20의 정사각형을 만들어준다.
				break;
			case 2:
			//2라면
				SelectObject(hdc, GetStockObject(BLACK_BRUSH));
				//검정색을 들고
				Ellipse(hdc, x * 20, y * 20, (x + 1) * 20, (y + 1) * 20);
				//지름이 20인 원을 그려준다.
				SelectObject(hdc, GetStockObject(WHITE_BRUSH));
				//펜을 원래대로 돌려준다.
				break;
			}
		}
	}

	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(255, 0, 0)));
	//빨간색을 들고
	Ellipse(hdc, wormX[0] * 20, wormY[0] * 20, (wormX[0] + 1) * 20, (wormY[0] + 1) * 20);
	//머리부분에 해당하는곳 wormX[0]와 wormY[0]에 
	//지름이 20인 원을 빨간색으로 그린다.
	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(0, 0, 255)));
	//파란색을 들고

	for (i = 1; i < len; i++)
		Ellipse(hdc, wormX[i] * 20, wormY[i] * 20, (wormX[i] + 1) * 20, (wormY[i] + 1) * 20);
	//꼬리부분에 해당하는곳 wormX[i]와 wormY[i]에 
	//지름이 20인 원을 파란색으로 그린다.
}


void GameInit()
//board배열에 대한 초기화를 하는 함수이다.
{
	int i;
	for (i = 0; i < 22; i++)
	{
		board[i][0] = -1;
		board[i][21] = -1;
		board[0][i] = -1;
		board[21][i] = -1;
		
		//벽에 해당하는 부분에 대한 초기화를 해주는 
		//반복문을 실행한다. -1로 초기화
	}
	wormX[0] = 2; wormY[0] = 1;
	wormX[1] = 1; wormY[1] = 1;
	//애벌레의 머리와 꼬리를 정하는 좌표를 초기화해주고
	board[wormY[0]][wormX[0]] = 3;
	board[wormY[1]][wormX[1]] = 3;
	//board상에 머리와 꼬리의 부분에 대한 값을
	//3으로 초기화 해준다.

	ItemGenerator();
	//먹이의 값을 설정하는 함수를 실행해준다.

	len = 2;
	//초기의 길이를 2로 잡고
	xDirect = 1; yDirect = 0;
	//프로그램이 실행하면 무조건 오른쪽으로 가게끔 설정해준다.
}


void DirectControl(int DirectKey)
//방향키로 누르는 값을 매개변수로 받아 처리해주는 함수이다.
{
	switch (DirectKey) {
	case VK_LEFT:
		//왼쪽키를 입력했을때
		if (xDirect == 1)
			//오른쪽 키값이 입력되어있는경우
	//이 경우를 설정하는 이유 : 애벌레는 180도 회전을 바로하지 못한다.
			break;
		//아래의 case문을 실행할수 없으므로 빠져나간다.
		if (board[wormY[0]][wormX[0] - 1] != -1)
			//board위의 애벌레의 값이 벽과 같지 않다면
		{
			xDirect = -1;
			yDirect = 0;
			//x축으로 -1의 방향으로 이동
			//y축으로의 이동이 없음을 표시한다.
		}
		break;
	case VK_RIGHT:
		//오른쪽 키를 입력했을때
		if (xDirect == -1)
			break;
		//왼쪽키가 입력된 상태라면
		//아래의 case문을 실행할수 없으므로 빠져나온다.
		if (board[wormY[0]][wormX[0] + 1] != -1)
			//오른쪽으로 이동하는 애벌레의 머리의 좌표값이
			//벽이 아니라면
		{
			xDirect = 1;
			yDirect = 0;
			//x축으로 +1의 방향으로이동 
			//y축으로의 이동이 없음을 알려준다.
		}
		break;
	case VK_UP:
		//위의 방향키를 입력했을때
		if (yDirect == 1)
			break;
		//아래의 방향으로 이동하고 있다면
		//아래의 case문을 실행할 수 없으므로 빠져나온다.
		if (board[wormY[0] - 1][wormX[0]] != -1)
			//위로 이동하는 애벌레의 머리가 벽이 아니라면
		{
			xDirect = 0;
			yDirect = -1;
			//x축 방향으로의 이동은 없고
			//y축 방향으로 -1의 방향으로 이동하고있다.
		}
		break;
	case VK_DOWN:
		//아래의 방향키를 눌렀을 경우
		if (yDirect == -1)
			break;
		//위쪽의 방향으로 이동하고 있다면
		//아래의 case문을 실행할 수 없으므로 case문을 빠져나온다.
		if (board[wormY[0] + 1][wormX[0]] != -1)
			//아래로 이동하는 애벌레의 머리가 벽이 아니라면
		{
			xDirect = 0;
			yDirect = 1;
			//x축 방향으로 이동은 없고
			//y축 방향으로 1의 방향으로 이동한다.
		}
		break;
	}
}


void MovingWorm()
{
	int tmpx, tmpy, i;

	tmpx = wormX[0];
	tmpy = wormY[0];
	//애벌레의 머리를 임시로 tmpx와 tmpy에 저장해둔다.
	//나중에 변화할수 있기때문에 임시로 저장.
	//값에 직접 저장해두면 먼저 들어있던 값이 없어진다.
	wormX[0] += xDirect; wormY[0] += yDirect;
	//키 다운으로 입력된 값만큼 애벌레의 머리값에 더해준다.

	if (board[wormY[0]][wormX[0]] == -1 || board[wormY[0]][wormX[0]] == 3)
	//board의 애벌레의 좌표값이 벽이 아니거나 3으로 저장된 경우
	{
		wormX[0] = tmpx;
		wormY[0] = tmpy;
		//머리의 값이 임시로 저장되어있던 tmpx와 tmpy의 값을 원래대로 돌려준다.
	}
	else
		//위의 경우가 아닌경우
	{
		if (board[wormY[0]][wormX[0]] == 2)
			//애벌레의 머리가 먹이의 부분과 겹치게 된다면
		{
			len = len + 1;
			board[wormY[0]][wormX[0]] = 0;
			//길이를 1 늘여주고 그 위치의 먹이를 없애준다.
		}
		else
			board[wormY[len - 1]][wormX[len - 1]] = 0;
		//먹이의 부분을 지나지 않는 경우
		//애벌레가 지나간 부분의 값들을 0으로 초기화 해준다.

		for (i = len - 1; i > 1; i--)
		{
			wormX[i] = wormX[i - 1];
			wormY[i] = wormY[i - 1];
			//애벌레의 이동을 나타내준다.
		}
		wormX[1] = tmpx;
		wormY[1] = tmpy;
		//원래 들어있던 값을 worm[1]에 넣어주고
		board[wormY[0]][wormX[0]] = 3;
		//애벌레의 머리에 대한 좌표를 3으로 저장해준다.
		//그래야지 머리는 빨간색 꼬리는 파란색의 
		//길이가 늘어난 애벌레를 표현할 수 있다.
	}
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMsg) {
	case WM_CREATE:
		GameInit();  //보드의 값의 초기화를 해주는 함수.
		SetTimer(hwnd, 1, 100, NULL);  
		//timer를 설정하는 함수.
		//WM_TIMER의 메세지를 0.1초 간격으로 보낸다.
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//hdc를 통해 paict객체를 생성해주고
		DrawGameBoard(hdc);
		//생성된 객체를 DrawGameBoard함수에 매개변수로 전달
		//게임보드에 대한 시각화를 하는 함수이다.
		EndPaint(hwnd, &ps);
		//페인트 객체를 생성하면 항상 돌려줘야 하기 때문에
		//EndPaint를 실행한다.
		break;
	case WM_KEYDOWN:
		DirectControl((int)wParam);
		//방향키가 눌릴때 마다 값을 저장하여 반환해주는 함수이다.
		break;
	case WM_TIMER:
		MovingWorm();
		//SetTimer에 대해 작동되는 함수이며 애벌레의 움직임을
		//표현해주는 함수이다.
		InvalidateRgn(hwnd, NULL, TRUE);
		//그리기 영역을 유효화하는 함수이다.
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		//타이머를 꺼주는 함수이다.
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}