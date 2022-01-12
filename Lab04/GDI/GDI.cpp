/*******************************************************************
����EasyGDI
�ļ���EasyGDI.c
���ܣ�������ͼ���������ʡ���ˢ��Ӧ��
********************************************************************/
#include <windows.h>
#include <windowsx.h>
#include "GDI.h"


#define ID_TIMER 1

BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


void MyPolyline(HDC hdc, CONST POINT* apt, int cpt)
{
	// apt �д洢��Ҫ���ӵĵ�����꣬cpt Ϊ �����ӵ�ĸ����� 
	for (int index = 0; index < cpt - 1; index++)
	{
		MoveToEx(hdc, (*(apt + index)).x, (*(apt + index)).y, NULL);
		LineTo(hdc, (*(apt + index + 1)).x, (*(apt + index + 1)).y);
	}

};


void MyPolygon(HDC hdc, CONST POINT* apt, int cpt)
{
	// apt �д洢��Ҫ���ӵĵ�����꣬cpt Ϊ �����ӵ�ĸ����� 
	for (int index = 0; index < cpt - 1; index++)
	{
		MoveToEx(hdc, (*(apt + index)).x, (*(apt + index)).y, NULL);
		LineTo(hdc, (*(apt + index + 1)).x, (*(apt + index + 1)).y);
	}

	MoveToEx(hdc, (*(apt + cpt - 1)).x, (*(apt + cpt - 1)).y, NULL);
	LineTo(hdc, (*apt).x, (*apt).y);
};

void MyPPgon(HDC hdc, POINT* apt, CONST INT* asz, int csz)
{
	for (DWORD Lines = 0; Lines < csz; Lines++)
	{
		MyPolygon(hdc, apt, asz[Lines]);
		//�������ߣ�������ߣ�asz[d]�����ĸ�����
		apt += asz[Lines];
	}

};

void MyPPLines(HDC hdc, POINT* apt, CONST DWORD* asz, DWORD csz)
{
	//Lines Ϊ�� ���±ꣻ

	for (DWORD Lines = 0; Lines < csz; Lines++)
	{
		MyPolyline(hdc, apt, asz[Lines]);
		//�������ߣ�������ߣ�asz[d]�����ĸ�����
		apt += asz[Lines];
	}

};

void DrawFigures(HDC hdc)
{
	POINT pts[11] = {
		{20,20},{50,100},{105,102},{140,120},
		{18,40},{100,30},{170.50},{200,40},
		{19,40},{170,100},{200,138}
	};
	int dwPtPerLine[4] = { 4,4,3 };
	//MyPPLines(hdc, pts, dwPtPerLine, 3);
	MyPPgon(hdc, pts, dwPtPerLine, 3);
	//MyPPLines(hdc, pts, dwPtPerLine, 3);

};

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow)
{
	MSG msg;

	if (!InitWindow(hInstance, iCmdShow))
		return FALSE;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

static BOOL InitWindow(HINSTANCE hInstance, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("EasyGDI");
	HWND hwnd;
	WNDCLASS wc;

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = szAppName;
	wc.lpszClassName = szAppName;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("ע�ᴰ����ʧ�ܣ�"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("����GDI����"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if (!hwnd) return FALSE;

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC           hdc;
	PAINTSTRUCT   ps;
	RECT          rect;
	HMENU         hMenu;

	static TCHAR szBuffer[100];
	static SYSTEMTIME SystemTime;

	int hour;

	POINT pts[] = {
						{20,20},{50,100},{105,102},{140,120},
						{18,40},{100,30},{170.50},{200,40},
						{19,40},{170,100},{200,138}
					 };

	switch (message)
	{
	case WM_CREATE:

		SetTimer(hWnd, ID_TIMER, 1000, NULL);
		//ÿ�� ���� WM_TIMER
		return 0;


	case WM_TIMER:
			GetLocalTime(&SystemTime);
			wsprintf(szBuffer, L"��ݣ�%02d�·ݣ�%02d���ڣ�%02d  Сʱ��%02d:���ӣ�%02d:������%02d",
				SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay,
				SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);
				
			InvalidateRect(hWnd, NULL, true);
		return 0;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		Rectangle(hdc, 20, 10, 200, 200);
		Ellipse(hdc, 200, 200, 300, 400);
		DrawFigures(hdc);
		EndPaint(hWnd, &ps);

		hdc = GetDC(hWnd);
		DrawText(hdc, szBuffer,
			-1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hWnd, hdc);

		return 0;
	}
	case WM_DESTROY:

		PostQuitMessage(0);
		KillTimer(hWnd, ID_TIMER);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

