/*******************************************************************
程序：EasyEdit
文件：EasyEdit.c
功能：标准控件演示程序—文本编辑器
********************************************************************/
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

//#define ID_LIST 1
//#define ID_TEXT 2

BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


static TCHAR szBuffer[100], szBuffer2[100];


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
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
	static TCHAR szAppName[] = TEXT("EasyEdit");
	HWND hwnd;
	WNDCLASS wc;

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("注册窗口类失败！"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("软键盘控件"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd) return FALSE;

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND  hWndEdit;
	static HWND  hWndButton,hWndRect,hWndScroll,hWndList,hWndText;
	static int cxChar, cyChar;
	static TCHAR ButtonName[27][2];
	static RECT rect1,rect2;



	HDC hdc;

	for (int i = 0; i < 26; i++)
	{
		ButtonName[i][0] = i + 'a';
	}


	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

	    cxChar *= 5;
		cyChar *= (5 * 0.618);

		for (int cnt = 0; cnt < 26; cnt++)
		{
			int x, y;
			x = cxChar * (cnt % 13);
			y = cyChar * (cnt / 13);
			hWndButton = CreateWindow(TEXT("button"),			        //窗口类名		
				ButtonName[cnt],
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				x, y, cxChar, cyChar,					//x,y 坐标； 宽度、高度；
				hWnd,		                        //父窗口句柄
				(HMENU)cnt,		                        //编辑控件子窗口标识
				(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
				NULL);
		}

		 hWndRect = CreateWindow(TEXT("static"),			        //窗口类名		
			NULL,
			WS_CHILD | WS_VISIBLE |  SS_BLACKFRAME| SS_BLACKRECT,
			0, 300, 1000, 50,					//x,y 坐标； 宽度、高度；
			hWnd,		                        //父窗口句柄
			(HMENU)27,		                        //编辑控件子窗口标识
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);
	
		 hWndScroll = CreateWindow(TEXT("scrollbar"),			        //窗口类名		
			 NULL,
			 WS_CHILD | WS_VISIBLE | WS_TABSTOP| SBS_VERT,
			 30, 120, 50, 100,					//x,y 坐标； 宽度、高度；
			 hWnd,		                        //父窗口句柄
			 (HMENU)28,		                        //编辑控件子窗口标识
			 (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			 NULL);
		 //hWndList = CreateWindow(TEXT("combobox"),			        //窗口类名		
			// NULL,
			// WS_CHILD | WS_VISIBLE | LBS_STANDARD,
			// 0, 200, 20, 100,					//x,y 坐标； 宽度、高度；
			// hWnd,		                        //父窗口句柄
			// (HMENU)28,		                        //编辑控件子窗口标识
			// (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			// NULL);
		 //FillListBox(hWndList);
		return 0;
	case WM_VSCROLL:
	{
		int i = GetWindowLong((HWND)lParam, GWL_ID);
		wsprintf(szBuffer2, L"滚动条的ID为%d", i);

		hdc = GetDC(hWnd);

		DrawText(hdc, szBuffer2, -1, &rect2, DT_CENTER | DT_NOCLIP);
		return 0;
	}
	case WM_SETFOCUS:
		SetFocus(hWndRect);
		return 0;

	case WM_SIZE:
		rect1.left = 26 * cxChar;
		rect1.right = 50 * cyChar;
		rect1.top = 30;
		rect1.bottom = 35;

		rect2.left = 300;
		rect2.right = 400;
		rect2.top = 350;
		rect2.bottom = 450;
		return 0;

	case WM_COMMAND:        	// 响应编辑控件通知消息
	{

		WORD key;
		key = LOWORD(wParam) + 'a';
		int index = lstrlen(szBuffer);
		szBuffer[index] = key;
		szBuffer[index + 1] = '\0';

		ValidateRect(hWnd, &rect1);

		return 0;
	}
	case WM_PAINT:
	{
		ScrollWindow(hWnd, 0, -cyChar, &rect1, &rect1);

		hdc = GetDC(hWnd);


		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		TextOutW(hdc, 10, 100, szBuffer, lstrlen(szBuffer));
		ReleaseDC(hWnd, hdc);

		return 0;

	}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

} //函数 MainWndProc 结束

