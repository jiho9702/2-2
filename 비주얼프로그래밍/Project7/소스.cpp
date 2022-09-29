#include <windows.h>
#include <TCHAR.h>
#include "resource.h"

#define LINE 1
#define ELLIPSE 2
#define RECTANGLE 3

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND     hwnd;
    MSG       msg;
    WNDCLASS WndClass;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);     // 커서 지정

    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = _T("Window Class Name");
    WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
    RegisterClass(&WndClass);
    hwnd = CreateWindow(
        _T("Window Class Name"),
        _T("Window Class Name"),
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        1000,
        1000,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

class Object
{ // 부모 클래스
public:
    int startX, startY, endX, endY;
    virtual void Draw(HDC hdc) = 0; // 도형 그리는 함수
    Object() { startX = startY = endX = endY = 0; }

    ~Object() {};
};

Object* inform[200];

class Line :public Object
{
public:
    void Draw(HDC hdc)
    {
        MoveToEx(hdc, startX, startY, NULL);
        LineTo(hdc, endX, endY);
    }
};

class Ellipse1 :public Object
{
public:
    void Draw(HDC hdc) { Ellipse(hdc, startX, startY, endX, endY); }
};

class Rectangle1 :public Object
{
public:
    void Draw(HDC hdc) { Rectangle(hdc, startX, startY, endX, endY); }
};


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;
    HPEN hPen;
    HBRUSH hBrush;
    CHOOSECOLOR COLOR;
    static int object_mode = 0;
    static int a;
    static COLORREF temp[16], PenColor = RGB(0, 0, 0), FaceColor = RGB(255, 255, 255);

    static bool isClick;
    static int sX, sY;
    static int ex, ey;
    static int FigureCount;



    switch (iMsg)
    {
    case WM_CREATE:
        sX = sY = 0;
        isClick = false;
        FigureCount = 0;
        ex = ey = 0;
        a = LINE;
        break;
    case  WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_LINE:
            a = LINE;
            break;
        case  ID_ELLIPSE:
            a = ELLIPSE;
            break;
        case ID_RECTANGLE:
            a = RECTANGLE;
            break;
        default:
            break;
        }
        break;

    case WM_LBUTTONDOWN:
        isClick = true;

        sX = LOWORD(lParam);
        sY = HIWORD(lParam);
        switch (a) {

        case 1:
            inform[FigureCount] = new Line();
            inform[FigureCount]->startX = sX;
            inform[FigureCount]->startY = sY;
            ex = sX;
            ey = sY;
            break;
        case 2:
            inform[FigureCount] = new Ellipse1();
            inform[FigureCount]->startX = sX;
            inform[FigureCount]->startY = sY;
            ex = sX;
            ey = sY;
            break;
        case 3:
            inform[FigureCount] = new Rectangle1();
            inform[FigureCount]->startX = sX;
            inform[FigureCount]->startY = sY;
            ex = sX;
            ey = sY;
            break;

        }
        break;

    case WM_MOUSEMOVE:
        hdc = GetDC(hwnd);

        if (isClick) {
            SetROP2(hdc, R2_NOTXORPEN);
            SelectObject(hdc, (HPEN)GetStockObject(BLACK_PEN));
            SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            sX = LOWORD(lParam);
            sY = HIWORD(lParam);
            switch (a) {
            case 1:
                MoveToEx(hdc, inform[FigureCount]->startX, inform[FigureCount]->startY, NULL);
                LineTo(hdc, ex, ey);
                MoveToEx(hdc, inform[FigureCount]->startX, inform[FigureCount]->startY, NULL);
                LineTo(hdc, sX, sY);
                break;
            case 2:
                Ellipse(hdc, inform[FigureCount]->startX, inform[FigureCount]->startY, ex, ey);
                Ellipse(hdc, inform[FigureCount]->startX, inform[FigureCount]->startY, sX, sY);
                break;
            case 3:
                Rectangle(hdc, inform[FigureCount]->startX, inform[FigureCount]->startY, ex, ey);
                Rectangle(hdc, inform[FigureCount]->startX, inform[FigureCount]->startY, sX, sY);
                break;
            default:
                break;
            }
            ex = sX;
            ey = sY;
        }
        ReleaseDC(hwnd, hdc);
        break;

    case WM_LBUTTONUP:
        if (isClick) {
            isClick = FALSE;
            sX = LOWORD(lParam);
            sY = HIWORD(lParam);
            inform[FigureCount]->endX = sX;
            inform[FigureCount]->endY = sY;
            FigureCount++;
        }
        break;


    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        if (!isClick && FigureCount > 0) {
            for (int i = 0; i < FigureCount; i++)
                inform[i]->Draw(hdc);
        }

        EndPaint(hwnd, &ps);
        break;

    case WM_DESTROY:
        for (int i = 0; i < FigureCount; i++) {
            delete inform[i];
        }
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}