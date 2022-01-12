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
	//Ϊrand()�õ��������׼��;
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



//��������
/******************************************************************
������WinProc ()
���ܣ�������������Ϣ
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
	case WM_CREATE:         //������Ϣ	   
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
		//��Ϸ��ʼ���棻
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

		//��Ϸ��ֹ
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(-1);
			return 0;
		}
		
		InvalidateRect(hWnd, NULL, true);
		return 0;

	case WM_PAINT:              //�ͻ����ػ���Ϣ
	{
		//ȡ���豸�������

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
		wsprintf(szBuf, L"����ESC�����Խ�����Ϸ");
		DrawText(hdc, szBuf, wcslen(szBuf), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	
		rect.top += Rect_wildth;
		rect.bottom += Rect_wildth;
	
		wsprintf(szBuf, L"��ǰ������꣺x:%d y:%d",pt.x,pt.y);
		DrawText(hdc, szBuf, wcslen(szBuf), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);


		//ȡ�ô��ڿͻ�������,   rect �����³�ʼ��
		GetClientRect(hWnd, &rect);
		//����������ɫ
		SetTextColor(hdc, RGB(0, 10, 255));

		if(gStart==false)
		    DrawText(hdc, Traget_str,-1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		else
		{
			wsprintf(szBuf, L"����F����ʼ��Ϸ");
			DrawText(hdc, szBuf, wcslen(szBuf), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		}

		//�ͷ���Դ
		EndPaint(hWnd, &ps);
		return 0;
	}


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	//����ȱʡ��Ϣ�������,   ����δ�������
	return DefWindowProc(hWnd, message, wParam, lParam);

} //���� WinProc ����



/******************************************************************
������InitWindow ()
���ܣ��������ڡ�
*******************************************************************/
static BOOL InitWindow(HINSTANCE hInstance, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("MyGame");  //Ӧ�ó�������
	HWND hwnd;                                    //���ھ��
	WNDCLASS wcMainWnd;                           //������ṹ
	ATOM a;

	//��䴰����ṹ
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

	//ע�ᴰ����
	a = RegisterClass(&wcMainWnd);

	if (!a)
	{
		MessageBox(NULL, TEXT("ע�ᴰ����ʧ�ܣ�"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	//����������
	hwnd = CreateWindow(szAppName, 						//����������
		TEXT("The first Game"),  //���ڱ���
		WS_OVERLAPPEDWINDOW,				//���ڷ��
		100,								//����λ�õ�x����
		100,								//����λ�õ�y����
		800,								//���ڵĿ��
		700*0.618-100,						//���ڵĸ߶�
		NULL,								//�����ھ��
		NULL,								//�˵����
		hInstance,							//Ӧ�ó���ʵ�����
		NULL);								//���ڴ�������ָ��

	if (!hwnd) return FALSE;

	//��ʾ�����´���
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}







