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
//�ֹ��� ������ ����

int board[22][22];
//�������� ũ��
int wormX[30], wormY[30];
//�ֹ����� �ִ�ũ��
int xDirect, yDirect, len;
//x������� �̵���, y�� ������ �̵���, �ֹ����� ����


void ItemGenerator()
//�ֹ����� ���̸� ����� �Լ��̴�.
{
	int i, x, y;
	
//������ ���� i, x, y ����

	for (i = 0; i < ITEMNUM; i++)
		//���������� �Է��� ITEMNUM�� �̿��Ͽ�
		//10ȸ�� �ݺ��ϴ� �ݺ����� �������ش�.
	{
		x = rand() % 20 + 1;
		y = rand() % 20 + 1;
		//���� �����ϰ� ���� 20���� �����߿���
		//������ ��ǥ�� �������� �����Ѵ�
		//+1�� ���� ������ ������ ��ǥ��
		//0���� ���� ���� ��ġ�� �����̴�.
		if (board[y][x] == 0)
			board[y][x] = 2;
		//�̷��� ���� ������ ��ǥ���� 2�� �־��ش�.
		else
		{
			i = i - 1;
			//���̰� �ִ� ��ġ�� ���̸� �� �����Ѱ��
			//i���� -1���ְ� �ش� �ݺ����� �ǳʶڴ�.
			continue;
		}
	}
	return;
}


void DrawGameBoard(HDC hdc)
//���������� �����ǿ� ���� �׸��� �׸��� �Լ��̴�.
{
	int i, x, y;
	for (y = 0; y < 22; y++) {
		for (x = 0; x < 22; x++)
	//22*22�� ������ ���� �ʿ��� �κп�
	//�׸��� �׸��� ���� ���߹ݺ����� �������ش�.
		{
			switch (board[y][x])
			//board[y][x]�� �� ����
			{
			case -1:
			//-1�̶��
				Rectangle(hdc, x * 20, y * 20, (x + 1) * 20, (y + 1) * 20);
			//���� �� ���� 20 ���� 20�� ���簢���� ������ش�.
				break;
			case 2:
			//2���
				SelectObject(hdc, GetStockObject(BLACK_BRUSH));
				//�������� ���
				Ellipse(hdc, x * 20, y * 20, (x + 1) * 20, (y + 1) * 20);
				//������ 20�� ���� �׷��ش�.
				SelectObject(hdc, GetStockObject(WHITE_BRUSH));
				//���� ������� �����ش�.
				break;
			}
		}
	}

	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(255, 0, 0)));
	//�������� ���
	Ellipse(hdc, wormX[0] * 20, wormY[0] * 20, (wormX[0] + 1) * 20, (wormY[0] + 1) * 20);
	//�Ӹ��κп� �ش��ϴ°� wormX[0]�� wormY[0]�� 
	//������ 20�� ���� ���������� �׸���.
	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(0, 0, 255)));
	//�Ķ����� ���

	for (i = 1; i < len; i++)
		Ellipse(hdc, wormX[i] * 20, wormY[i] * 20, (wormX[i] + 1) * 20, (wormY[i] + 1) * 20);
	//�����κп� �ش��ϴ°� wormX[i]�� wormY[i]�� 
	//������ 20�� ���� �Ķ������� �׸���.
}


void GameInit()
//board�迭�� ���� �ʱ�ȭ�� �ϴ� �Լ��̴�.
{
	int i;
	for (i = 0; i < 22; i++)
	{
		board[i][0] = -1;
		board[i][21] = -1;
		board[0][i] = -1;
		board[21][i] = -1;
		
		//���� �ش��ϴ� �κп� ���� �ʱ�ȭ�� ���ִ� 
		//�ݺ����� �����Ѵ�. -1�� �ʱ�ȭ
	}
	wormX[0] = 2; wormY[0] = 1;
	wormX[1] = 1; wormY[1] = 1;
	//�ֹ����� �Ӹ��� ������ ���ϴ� ��ǥ�� �ʱ�ȭ���ְ�
	board[wormY[0]][wormX[0]] = 3;
	board[wormY[1]][wormX[1]] = 3;
	//board�� �Ӹ��� ������ �κп� ���� ����
	//3���� �ʱ�ȭ ���ش�.

	ItemGenerator();
	//������ ���� �����ϴ� �Լ��� �������ش�.

	len = 2;
	//�ʱ��� ���̸� 2�� ���
	xDirect = 1; yDirect = 0;
	//���α׷��� �����ϸ� ������ ���������� ���Բ� �������ش�.
}


void DirectControl(int DirectKey)
//����Ű�� ������ ���� �Ű������� �޾� ó�����ִ� �Լ��̴�.
{
	switch (DirectKey) {
	case VK_LEFT:
		//����Ű�� �Է�������
		if (xDirect == 1)
			//������ Ű���� �ԷµǾ��ִ°��
	//�� ��츦 �����ϴ� ���� : �ֹ����� 180�� ȸ���� �ٷ����� ���Ѵ�.
			break;
		//�Ʒ��� case���� �����Ҽ� �����Ƿ� ����������.
		if (board[wormY[0]][wormX[0] - 1] != -1)
			//board���� �ֹ����� ���� ���� ���� �ʴٸ�
		{
			xDirect = -1;
			yDirect = 0;
			//x������ -1�� �������� �̵�
			//y�������� �̵��� ������ ǥ���Ѵ�.
		}
		break;
	case VK_RIGHT:
		//������ Ű�� �Է�������
		if (xDirect == -1)
			break;
		//����Ű�� �Էµ� ���¶��
		//�Ʒ��� case���� �����Ҽ� �����Ƿ� �������´�.
		if (board[wormY[0]][wormX[0] + 1] != -1)
			//���������� �̵��ϴ� �ֹ����� �Ӹ��� ��ǥ����
			//���� �ƴ϶��
		{
			xDirect = 1;
			yDirect = 0;
			//x������ +1�� ���������̵� 
			//y�������� �̵��� ������ �˷��ش�.
		}
		break;
	case VK_UP:
		//���� ����Ű�� �Է�������
		if (yDirect == 1)
			break;
		//�Ʒ��� �������� �̵��ϰ� �ִٸ�
		//�Ʒ��� case���� ������ �� �����Ƿ� �������´�.
		if (board[wormY[0] - 1][wormX[0]] != -1)
			//���� �̵��ϴ� �ֹ����� �Ӹ��� ���� �ƴ϶��
		{
			xDirect = 0;
			yDirect = -1;
			//x�� ���������� �̵��� ����
			//y�� �������� -1�� �������� �̵��ϰ��ִ�.
		}
		break;
	case VK_DOWN:
		//�Ʒ��� ����Ű�� ������ ���
		if (yDirect == -1)
			break;
		//������ �������� �̵��ϰ� �ִٸ�
		//�Ʒ��� case���� ������ �� �����Ƿ� case���� �������´�.
		if (board[wormY[0] + 1][wormX[0]] != -1)
			//�Ʒ��� �̵��ϴ� �ֹ����� �Ӹ��� ���� �ƴ϶��
		{
			xDirect = 0;
			yDirect = 1;
			//x�� �������� �̵��� ����
			//y�� �������� 1�� �������� �̵��Ѵ�.
		}
		break;
	}
}


void MovingWorm()
{
	int tmpx, tmpy, i;

	tmpx = wormX[0];
	tmpy = wormY[0];
	//�ֹ����� �Ӹ��� �ӽ÷� tmpx�� tmpy�� �����صд�.
	//���߿� ��ȭ�Ҽ� �ֱ⶧���� �ӽ÷� ����.
	//���� ���� �����صθ� ���� ����ִ� ���� ��������.
	wormX[0] += xDirect; wormY[0] += yDirect;
	//Ű �ٿ����� �Էµ� ����ŭ �ֹ����� �Ӹ����� �����ش�.

	if (board[wormY[0]][wormX[0]] == -1 || board[wormY[0]][wormX[0]] == 3)
	//board�� �ֹ����� ��ǥ���� ���� �ƴϰų� 3���� ����� ���
	{
		wormX[0] = tmpx;
		wormY[0] = tmpy;
		//�Ӹ��� ���� �ӽ÷� ����Ǿ��ִ� tmpx�� tmpy�� ���� ������� �����ش�.
	}
	else
		//���� ��찡 �ƴѰ��
	{
		if (board[wormY[0]][wormX[0]] == 2)
			//�ֹ����� �Ӹ��� ������ �κа� ��ġ�� �ȴٸ�
		{
			len = len + 1;
			board[wormY[0]][wormX[0]] = 0;
			//���̸� 1 �ÿ��ְ� �� ��ġ�� ���̸� �����ش�.
		}
		else
			board[wormY[len - 1]][wormX[len - 1]] = 0;
		//������ �κ��� ������ �ʴ� ���
		//�ֹ����� ������ �κ��� ������ 0���� �ʱ�ȭ ���ش�.

		for (i = len - 1; i > 1; i--)
		{
			wormX[i] = wormX[i - 1];
			wormY[i] = wormY[i - 1];
			//�ֹ����� �̵��� ��Ÿ���ش�.
		}
		wormX[1] = tmpx;
		wormY[1] = tmpy;
		//���� ����ִ� ���� worm[1]�� �־��ְ�
		board[wormY[0]][wormX[0]] = 3;
		//�ֹ����� �Ӹ��� ���� ��ǥ�� 3���� �������ش�.
		//�׷����� �Ӹ��� ������ ������ �Ķ����� 
		//���̰� �þ �ֹ����� ǥ���� �� �ִ�.
	}
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMsg) {
	case WM_CREATE:
		GameInit();  //������ ���� �ʱ�ȭ�� ���ִ� �Լ�.
		SetTimer(hwnd, 1, 100, NULL);  
		//timer�� �����ϴ� �Լ�.
		//WM_TIMER�� �޼����� 0.1�� �������� ������.
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//hdc�� ���� paict��ü�� �������ְ�
		DrawGameBoard(hdc);
		//������ ��ü�� DrawGameBoard�Լ��� �Ű������� ����
		//���Ӻ��忡 ���� �ð�ȭ�� �ϴ� �Լ��̴�.
		EndPaint(hwnd, &ps);
		//����Ʈ ��ü�� �����ϸ� �׻� ������� �ϱ� ������
		//EndPaint�� �����Ѵ�.
		break;
	case WM_KEYDOWN:
		DirectControl((int)wParam);
		//����Ű�� ������ ���� ���� �����Ͽ� ��ȯ���ִ� �Լ��̴�.
		break;
	case WM_TIMER:
		MovingWorm();
		//SetTimer�� ���� �۵��Ǵ� �Լ��̸� �ֹ����� ��������
		//ǥ�����ִ� �Լ��̴�.
		InvalidateRgn(hwnd, NULL, TRUE);
		//�׸��� ������ ��ȿȭ�ϴ� �Լ��̴�.
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		//Ÿ�̸Ӹ� ���ִ� �Լ��̴�.
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}