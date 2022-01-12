/*******************************************************************
程序：CommDlg
文件：CommDlg.c
功能：通用对话框演示程序—选择不同的颜色显示文本
********************************************************************/
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ColorInputDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);



BOOL GetMyColor2(HWND hWnd);
//, COLORREF* pColor);

COLORREF gTextColor = RGB(0, 0, 255);


void DrawFigures(HDC hdc)
{
	POINT pts[11] = {
		{20,20},{50,100},{105,102},{140,120},
		{18,40},{100,30},{170.50},{200,40},
		{19,40},{170,100},{200,138}
	};
	int dwPtPerLine[4] = { 4,4,3 };
	//MyPPLines(hdc, pts, dwPtPerLine, 3);
	PolyPolygon(hdc, pts, dwPtPerLine, 3);
	//MyPPLines(hdc, pts, dwPtPerLine, 3);

};

BOOL GetMyColor2(HWND hWnd)// , COLORREF *pColor)
{

	if (DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		MAKEINTRESOURCE(IDD_DIALOG_COLOR),
		hWnd,
		ColorInputDlg)==IDOK)
	{
		return true;
	}
}

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
	static TCHAR szAppName[] = TEXT("CommDlg");
	HWND hwnd;
	WNDCLASS wc;

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH);
	//wc.lpszMenuName =(LPCWSTR) LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("注册窗口类失败！"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("通用对话框演示程序"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, 
		LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), 
		hInstance, 
		NULL);

	if (!hwnd) return FALSE;

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static CHOOSECOLOR  cc;
	static COLORREF     crCustomColors[16];//16个用户自定义颜色，
	static COLORREF     crText1 = RGB(0, 0, 0), crText2 = RGB(0, 0, 0);

	HDC                 hdc;
	PAINTSTRUCT         ps;
	RECT                rect;

	HPEN hPen, hPenOld;
	HBRUSH hBrush;

	switch (message)
	{
	case WM_CREATE:
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hWnd;
		cc.hInstance = NULL;
		cc.rgbResult = RGB(0, 0, 0);
		cc.lpCustColors = crCustomColors;
		cc.Flags = CC_RGBINIT | CC_FULLOPEN;
		cc.lCustData = 0;
		cc.lpfnHook = NULL;
		cc.lpTemplateName = NULL;


		return 0;

	case WM_COMMAND: 
	{
		switch (wParam)
		{
		     case ID_BackGroundColor:
				 //if (GetMyColor2(hWnd))//, &gTextColor))
				 if(					 
					 DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
					 MAKEINTRESOURCE(IDD_DIALOG_COLOR),
					 hWnd,
					 ColorInputDlg) == IDOK							 
					 )
				 {
					 InvalidateRect(hWnd, NULL, true);
				 }
				 break;
			 case ID_TEXTCOLOR:
				 //打开“颜色”通用对话框并选择颜色添加到自定义颜色中
				 if (ChooseColor(&cc))
				 {
					 crText1 = crCustomColors[0];
					 crText2 = cc.rgbResult;
					 InvalidateRect(hWnd, NULL, TRUE);
				 }
				 break;

			 default:
				 break;
		}
		return 0;
	}

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		hBrush = CreateSolidBrush(gTextColor);

		SelectObject(hdc, hBrush);//将 hBrush 放置于 hdc 中；
		SetBkColor(hdc, gTextColor);

		rect.left = 10;
		rect.right = 300;
		rect.top = 20;
		rect.bottom = 300;
		SetTextColor(hdc, crText1);
		DrawText(hdc, TEXT("This is Windows Lab4"),
			-1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		rect.left = 10;
		rect.right = 300;
		rect.top = 200;
		rect.bottom = 300;
		SetTextColor(hdc, crText2);
		DrawText(hdc, TEXT("This is Windows Lab5"),
			-1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
//		SelectObject(hdc, hPen);
//		DeleteObject(hPen);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

} //函数 WinProc 结束




BOOL CALLBACK ColorInputDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int  iColor, iFigure;
	BOOL b = false;

	//PAINTSTRUCT
	static UINT R, G, B;

	switch (message)
	{
	case WM_INITDIALOG:

		B = gTextColor / (256 * 256);
	    G = (gTextColor - B * (256 * 256) ) / 256;
		R = gTextColor - B * (256 * 256) - G * 256;

		SetDlgItemInt(hDlg, IDC_EDIT1, R , TRUE);
		SetDlgItemInt(hDlg, IDC_EDIT2, G, TRUE);
		SetDlgItemInt(hDlg, IDC_EDIT3, B, TRUE);

	
		return FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:

			R= GetDlgItemInt(hDlg, IDC_EDIT1, &b, false);
			G= GetDlgItemInt(hDlg, IDC_EDIT2, &b, false);
			B= GetDlgItemInt(hDlg, IDC_EDIT3, &b, false);

			gTextColor = RGB(R,G,B);

			EndDialog(hDlg, TRUE);
			return TRUE;

		case IDCANCEL:

			EndDialog(hDlg, FALSE);
			return TRUE;
		}
		break;

		//case WM_PAINT:
		   //return 0;
	}
	return FALSE;

}//结束 ColorDlgProc

