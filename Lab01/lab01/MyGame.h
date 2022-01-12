#pragma once
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <iostream>
#include <time.h>
#include "resource.h"
using namespace std;

#define str_length  12
#define Score_aChar 10
#define Score_aString 100
#define Rect_wildth 20

TCHAR  Traget_str[str_length+1];
UINT   GameScore = 0;
bool gStart = false;


void InitLetter()
{
	int  i;
	SYSTEMTIME systime;
	GetSystemTime(&systime);
	//为rand()得到随机数作准备;
	srand(systime.wMilliseconds);
	for (i = 0; i < str_length; i++)
	{
		Traget_str[i]= 'A'+rand() % 26;
	}
	return;
}
int  EraseChar(TCHAR* Traget_str, TCHAR* pos)
{
	pos++;
	while (*pos != '\0')
	{		
		*(pos - 1) = *pos;
		pos++;
	}
	*(pos-1) = '\0';
	int isEmpty=0;
	if (*Traget_str == '\0') isEmpty = 1;
	return isEmpty;
 }



//函数声明
/******************************************************************
函数：WinProc ()
功能：处理主窗口消息
*******************************************************************/
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;
	TCHAR gcInput;
	static POINT pt;

	switch (message)
	{
	case WM_CREATE:         //创建消息	   
		//PlaySound(TEXT("sound_lab.wav"), NULL, SND_FILENAME | SND_ASYNC);
		InitLetter();
		gStart = true;
		InvalidateRect(hWnd, NULL, true);
		return 0;	  
	case  WM_LBUTTONDBLCLK:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		InvalidateRect(hWnd, NULL, true);
	case WM_CHAR:
		//游戏开始界面；
		if (gStart == true)
		{
			if (wParam == 'F'|| wParam == 'f') {
				gStart = false;
			}
		}
//		else if (wcschr(Traget_str, wParam) != NULL)
		else if ( Traget_str[0]== wParam)
		{
			TCHAR* pos = wcschr(Traget_str, wParam);
			GameScore += Score_aChar;
			EraseChar(Traget_str, pos);
			if (*Traget_str == '\0')
			{
				InitLetter();
				GameScore += Score_aString;
			}
		}

		//游戏终止
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(-1);
			return 0;
		}
		
		InvalidateRect(hWnd, NULL, true);
		return 0;

	case WM_PAINT:              //客户区重绘消息
	{
		//取得设备环境句柄

		TCHAR szBuf[32];
		hdc = BeginPaint(hWnd, &ps);

		rect.left = 0;
		rect.top = 0;
		rect.right = 200;
		rect.bottom = 60;


		SetTextColor(hdc, RGB(255, 10, 255));
		wsprintf(szBuf, L"score :%d", GameScore);
		DrawText(hdc, szBuf, wcslen(szBuf), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		
		rect.top += Rect_wildth;
		rect.bottom += Rect_wildth;
		wsprintf(szBuf, L"按下ESC键可以结束游戏");
		DrawText(hdc, szBuf, wcslen(szBuf), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	
		rect.top += Rect_wildth;
		rect.bottom += Rect_wildth;
	
		wsprintf(szBuf, L"当前鼠标坐标：x:%d y:%d",pt.x,pt.y);
		DrawText(hdc, szBuf, wcslen(szBuf), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);


		//取得窗口客户区矩形,   rect 将重新初始化
		GetClientRect(hWnd, &rect);
		//设置文字颜色
		SetTextColor(hdc, RGB(0, 10, 255));

		if(gStart==false)
		    DrawText(hdc, Traget_str,-1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		else
		{
			wsprintf(szBuf, L"按下F键开始游戏");
			DrawText(hdc, szBuf, wcslen(szBuf), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		}

		//释放资源
		EndPaint(hWnd, &ps);
		return 0;
	}


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	//调用缺省消息处理过程,   处理未定义操作
	return DefWindowProc(hWnd, message, wParam, lParam);

} //函数 WinProc 结束



/******************************************************************
函数：InitWindow ()
功能：创建窗口。
*******************************************************************/
static BOOL InitWindow(HINSTANCE hInstance, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("MyGame");  //应用程序名称
	HWND hwnd;                                    //窗口句柄
	WNDCLASS wcMainWnd;                           //窗口类结构
	ATOM a;

	//填充窗口类结构
	wcMainWnd.style = CS_VREDRAW | CS_HREDRAW|CS_DBLCLKS;
	wcMainWnd.lpfnWndProc = WinProc;
	wcMainWnd.cbClsExtra = 0;
	wcMainWnd.cbWndExtra = 0;
	wcMainWnd.hInstance = hInstance;
	wcMainWnd.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcMainWnd.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wcMainWnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcMainWnd.lpszMenuName = NULL;
	wcMainWnd.lpszClassName = szAppName;

	//注册窗口类
	a = RegisterClass(&wcMainWnd);

	if (!a)
	{
		MessageBox(NULL, TEXT("注册窗口类失败！"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	//创建主窗口
	hwnd = CreateWindow(szAppName, 						//窗口类名称
		TEXT("The first Game"),  //窗口标题
		WS_OVERLAPPEDWINDOW,				//窗口风格
		100,								//窗口位置的x坐标
		100,								//窗口位置的y坐标
		800,								//窗口的宽度
		700*0.618-100,						//窗口的高度
		NULL,								//父窗口句柄
		NULL,								//菜单句柄
		hInstance,							//应用程序实例句柄
		NULL);								//窗口创建数据指针

	if (!hwnd) return FALSE;

	//显示并更新窗口
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}







