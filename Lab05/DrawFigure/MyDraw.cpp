#pragma once
#include "MyDraw.h"


POINT gPtBegin, gPtEnd;//鼠标所在的 划线 所在的点
POINT gPtChange;
int giDrawState = DRAWM_SELECT;  //绘画 时选择的图形状态；
UINT Ellp_Length;
UINT Ellp_Wildth;
int Change_index;//查询坐标
BOOL gbDrawing = FALSE;//正在绘制图形标志
TCHAR   gszFileName[MAX_PATH], gszFileTitle[MAX_PATH];
TCHAR   szWndCaption[MAX_PATH];
UINT gCountText = 0;
MYTEXT gTexts[BUF_MAX];
COLORREF gColorText = RGB(0, 0, 255);
TCHAR gBuffer[TEXT_LEN_MAX - 1] = "输入";
UINT gCountEllp = 0;
MYELLP gEllps[BUF_MAX];
UINT gCountRect = 0;
MYRECT gRects[BUF_MAX];
// 图形数据缓冲区
UINT gCountLine = 0;
//MYLINE gLine;
MYLINE gLines[BUF_MAX];
LOGPEN glogPen = { PS_SOLID,{1,1},RGB(255,0,255) }; //  实心笔 宽度为1 颜色 设置
LOGBRUSH glogBr = { BS_SOLID,RGB(255,0,0),HS_HORIZONTAL };
LOGFONT glogFont;




BOOL CALLBACK TextColorInputDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int  iColor, iFigure;
	switch (message)
	{
	case WM_INITDIALOG://初始化
		SetDlgItemText(hDlg, IDC_EDIT1, gBuffer);
		return FALSE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT1, gBuffer, TEXT_LEN_MAX - 1);
			EndDialog(hDlg, TRUE);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return TRUE;
		}
		break;
	}
	return FALSE;
}//结束 ColorDlgProc

BOOL CALLBACK EllpGetIntDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int  iColor, iFigure;
	BOOL b;
	switch (message)
	{
	case WM_INITDIALOG://初始化
		SetDlgItemInt(hDlg, IDC_EDIT_LENGTH, 100, true);
		SetDlgItemInt(hDlg, IDC_EDIT_WILDTH, 100, true);
		return FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			Ellp_Length = GetDlgItemInt(hDlg, IDC_EDIT_LENGTH, &b, false);
			Ellp_Wildth = GetDlgItemInt(hDlg, IDC_EDIT_WILDTH, &b, false);
			EndDialog(hDlg, TRUE);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return TRUE;
		}
		break;
	}
	return FALSE;
}//结束 ColorDlgProc


void ChooseColorInit(HWND* hWnd, CHOOSECOLOR* cc, COLORREF* crCustomColors)
{
	(*cc).lStructSize = sizeof(CHOOSECOLOR);
	(*cc).hwndOwner = *hWnd;
	(*cc).hInstance = NULL;

	(*cc).rgbResult = RGB(255, 0, 0);
	(*cc).lpCustColors = crCustomColors;

	(*cc).Flags = CC_RGBINIT | CC_FULLOPEN;
	(*cc).lCustData = 0;
	(*cc).lpfnHook = NULL;
	(*cc).lpTemplateName = NULL;

}
int SearchInLines(POINT gPtChange, MYLINE* gLines, UINT gCountLine)
{
	for (int index = 0; index < gCountLine; index++)
	{
		double k1 = ((double)gLines[index].ptE.y - (double)gLines[index].ptS.y) / ((double)gLines[index].ptE.x - (double)gLines[index].ptS.x);
		double k2 = ((double)gPtChange.y - (double)gLines[index].ptS.y) / ((double)gPtChange.x - (double)gLines[index].ptS.x);

		double ans1 = fabs(k1 - k2);
		if (ans1 < 0.05)
		{
			return index;
		}
	}
	return -1;
}
void DrawAllLines(HDC hdc)
{
	HPEN hPen, hPenOld;
	for (UINT i = 0; i <= gCountLine; i++)
	{

		hPen = CreatePenIndirect(&gLines[i].lgPen);

		hPenOld = (HPEN)SelectObject(hdc, hPen);

		MoveToEx(hdc, gLines[i].ptS.x, gLines[i].ptS.y, NULL);
		LineTo(hdc, gLines[i].ptE.x, gLines[i].ptE.y);

		SelectObject(hdc, hPenOld); // 恢复原有笔
		DeleteObject(hPen);
	}

}

void DrawAllRects(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBr, hBrOld;

	for (UINT i = 0; i < gCountRect; i++)
	{
		hPen = CreatePenIndirect(&gRects[i].lgPen);
		hPenOld = (HPEN)SelectObject(hdc, hPen);

		hBr = CreateBrushIndirect(&gRects[i].lgBr);
		hBrOld = (HBRUSH)SelectObject(hdc, hBr);

		Rectangle(hdc, gRects[i].ptS.x, gRects[i].ptS.y,
			gRects[i].ptE.x, gRects[i].ptE.y);

		SelectObject(hdc, hPenOld);//将原有的笔恢复；
		DeleteObject(hPen);

		SelectObject(hdc, hBrOld);//将原有的刷恢复；
		DeleteObject(hBr);
	}

}
int  SearchInRect(POINT gPtChange, MYRECT* gRects, UINT gCountRect)
{
	for (int index = 0; index < gCountRect; index++)
	{
		if (gRects[index].ptS.x < gPtChange.x && gPtChange.x < gRects[index].ptE.x
			&& gRects[index].ptS.y < gPtChange.y && gPtChange.y < gRects[index].ptE.y)
		{
			return index;
		}
	}
	return -1;
}
void ChangeMyRectColor(HWND hWnd, MYRECT* gRects)
{
	static CHOOSECOLOR  cc;
	static COLORREF     crCustomColors[16];
	static COLORREF     crText = RGB(0, 255, 0);
	//初始化结构 cc
	ChooseColorInit(&hWnd, &cc, crCustomColors);
	cc.rgbResult = crText;
	if (ChooseColor(&cc)) {
		//(*gRects).lgPen.lopnColor = cc.rgbResult;
		(*gRects).lgBr.lbColor = cc.rgbResult;
	}
}

int  SearchInEllp(POINT gPtChange, MYELLP* gEllps, UINT gCountEllp)
{
	for (int index = 0; index < gCountEllp; index++)
	{
		if (gEllps[index].ptS.x < gPtChange.x && gPtChange.x < gEllps[index].ptE.x
			&& gEllps[index].ptS.y < gPtChange.y && gPtChange.y < gEllps[index].ptE.y)
		{
			return index;
		}
	}
	return -1;
}

void DrawAllEllps(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBr, hBrOld;

	for (UINT i = 0; i < gCountEllp; i++)
	{
		hPen = CreatePenIndirect(&gEllps[i].lgPen);
		hPenOld = (HPEN)SelectObject(hdc, hPen);

		hBr = CreateBrushIndirect(&gEllps[i].lgBr);
		hBrOld = (HBRUSH)SelectObject(hdc, hBr);

		Ellipse(hdc, gEllps[i].ptS.x, gEllps[i].ptS.y,
			gEllps[i].ptE.x, gEllps[i].ptE.y);

		SelectObject(hdc, hPenOld);//将原有的笔恢复；
		DeleteObject(hPen);

		SelectObject(hdc, hBrOld);//将原有的刷恢复；
		DeleteObject(hBr);
	}
}

void DrawAllText(HDC hdc)
{
	HFONT hFont, hFontOld;

	for (UINT i = 0; i < gCountText; i++)
	{
		hFont = CreateFontIndirect(&gTexts[i].lgFont);
		hFontOld = (HFONT)SelectObject(hdc, hFont);
		SetTextColor(hdc, gTexts[i].crText);

		TextOut(hdc, gTexts[i].ptS.x,
			gTexts[i].ptS.y, gTexts[i].szContent,
			strlen(gTexts[i].szContent));

		SelectObject(hdc, hFontOld);//将原有的笔恢复；
		DeleteObject(hFont);
	}
}


int  SearchInText(POINT gPtChange, MYTEXT* gTexts, UINT gCountText)
{
	for (int index = 0; index < gCountText; index++)
	{
		if (gTexts[index].ptS.x < gPtChange.x && gPtChange.x < gTexts[index].ptE.x
			&& gTexts[index].ptS.y < gPtChange.y && gPtChange.y < gTexts[index].ptE.y)
		{
			return index;
		}
	}
	return -1;
}



BOOL GetMyColor(HWND hWnd, COLORREF* pColor) {

	static CHOOSECOLOR  cc;
	static COLORREF     crCustomColors[16];
	//初始化结构 cc
	ChooseColorInit(&hWnd, &cc, crCustomColors);
	cc.rgbResult = *pColor;
	if (ChooseColor(&cc)) {
		*pColor = cc.rgbResult;
		return TRUE;
	}
	return FALSE;
}
VOID  ChangeMyLineColor(HWND hWnd, MYLINE* gLines) {
	static CHOOSECOLOR  cc;
	static COLORREF     crCustomColors[16];
	static COLORREF     crText = RGB(0, 255, 0);
	//初始化结构 cc
	ChooseColorInit(&hWnd, &cc, crCustomColors);
	//cc.rgbResult = crText;

	int test = ChooseColor(&cc);
	DWORD A = CommDlgExtendedError();
	if (test) {
		(*gLines).lgPen.lopnColor = cc.rgbResult;
	}

}
void  DeleteMyLine(HWND hWnd, MYLINE* gLines)
{
	(*gLines).ptE = (*gLines).ptS;
}



BOOL GetMyFont(HWND hWnd, LOGFONT* glogFont, COLORREF* pColor)
{
	CHOOSEFONT   cf;
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = hWnd;
	cf.hDC = NULL;
	cf.lpLogFont = glogFont;
	cf.iPointSize = 0;
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	cf.rgbColors = 0;
	cf.lCustData = 0;
	cf.lpfnHook = NULL;
	cf.lpTemplateName = NULL;
	cf.hInstance = NULL;
	cf.lpszStyle = NULL;
	cf.nFontType = 0;
	cf.nSizeMin = 0;
	cf.nSizeMax = 0;
	if (ChooseFont(&cf))
	{
		*pColor = cf.rgbColors;
		return true;
	}
	return false;
};

void  ChangeMyTextFont(HWND hWnd, MYTEXT* gTexts)
{
	CHOOSEFONT   cf;
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = hWnd;
	cf.hDC = NULL;
	cf.lpLogFont = &((*gTexts).lgFont);
	cf.iPointSize = 0;
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	cf.rgbColors = 0;
	cf.lCustData = 0;
	cf.lpfnHook = NULL;
	cf.lpTemplateName = NULL;
	cf.hInstance = NULL;
	cf.lpszStyle = NULL;
	cf.nFontType = 0;
	cf.nSizeMin = 0;
	cf.nSizeMax = 0;
	if (ChooseFont(&cf))
	{
		(*gTexts).crText = cf.rgbColors;
		(*gTexts).lgFont = *(cf.lpLogFont);
	}
}


BOOL GetOpenFigFileName(HWND hWnd, LPSTR lpFileName)
{
	static OPENFILENAME  ofn;
	TCHAR gszFileFilter[] = TEXT("Figure Files (*.drw)\0*.drw\0")  \
		TEXT("All Files (*.*)\0*.*\0\0");
	//初始化结构变量 ofn
	ofn.lStructSize = sizeof(OPENFILENAME);
	//	ofn.hwndOwner = hWnd;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = gszFileFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	//	ofn.lpstrFile = NULL;     //调用 GetOpenFileName 函数前设置        
	ofn.nMaxFile = MAX_PATH;
	//	ofn.lpstrFileTitle = NULL;     //调用 GetOpenFileName 函数前设置
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = NULL;
	//	ofn.Flags = 0;        //调用 GetOpenFileName 函数前设置
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = TEXT("drw");//缺省后缀
	ofn.lCustData = 0L;
	ofn.lpfnHook = NULL;
	ofn.hwndOwner = hWnd;


	ofn.lpstrFile = lpFileName;
	ofn.lpstrFileTitle = gszFileFilter;
	ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;
	if (GetOpenFileName(&ofn))
	{
		return true;
	}
	return false;
}
void  ReadFigureData_FileName(LPSTR gszFileName)
{
	HANDLE   hFile;
	hFile = CreateFile(gszFileName, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD  dwBytes;//返回成功写入的字节数；
		//存储线
		ReadFile(hFile, &gCountLine, sizeof(UINT),
			&dwBytes, NULL);
		ReadFile(hFile, gLines, gCountLine * sizeof(MYLINE),
			&dwBytes, NULL);
		//存储矩形
		ReadFile(hFile, &gCountRect, sizeof(UINT),
			&dwBytes, NULL);
		ReadFile(hFile, gRects, gCountRect * sizeof(MYRECT),
			&dwBytes, NULL);
		//椭圆
		ReadFile(hFile, &gCountEllp, sizeof(UINT),
			&dwBytes, NULL);
		ReadFile(hFile, gEllps, gCountEllp * sizeof(MYELLP),
			&dwBytes, NULL);
		//文本
		ReadFile(hFile, &gCountText, sizeof(UINT),
			&dwBytes, NULL);
		ReadFile(hFile, gTexts, gCountText * sizeof(MYTEXT),
			&dwBytes, NULL);
		CloseHandle(hFile);
		//WriteFile()
	}
}


void  SaveFigureData_FileName(LPCTSTR lpFileName)
{
	HANDLE   hFile;
	hFile = CreateFile(lpFileName, GENERIC_WRITE, 0,
		NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{

		DWORD  dwBytes;//返回成功写入的字节数；
		//存储线
		WriteFile(hFile, &gCountLine, sizeof(UINT),
			&dwBytes, NULL);
		WriteFile(hFile, gLines, gCountLine * sizeof(MYLINE),
			&dwBytes, NULL);

		//存储矩形
		WriteFile(hFile, &gCountRect, sizeof(UINT),
			&dwBytes, NULL);
		WriteFile(hFile, gRects, gCountRect * sizeof(MYRECT),
			&dwBytes, NULL);

		//椭圆
		WriteFile(hFile, &gCountEllp, sizeof(UINT),
			&dwBytes, NULL);
		WriteFile(hFile, gEllps, gCountEllp * sizeof(MYELLP),
			&dwBytes, NULL);

		//文本
		WriteFile(hFile, &gCountText, sizeof(UINT),
			&dwBytes, NULL);
		WriteFile(hFile, gTexts, gCountText * sizeof(MYTEXT),
			&dwBytes, NULL);

		CloseHandle(hFile);
	}
}
BOOL GetSaveFigFileName(HWND hWnd, LPSTR lpFileName)
{
	static OPENFILENAME  ofn;
	BOOL bRet = FALSE;

	TCHAR gszFileFilter[] = TEXT("Figure Files (*.drw)\0*.drw\0")  \
		TEXT("All Files (*.*)\0*.*\0\0");

	//初始化结构变量 ofn
	ofn.lStructSize = sizeof(OPENFILENAME);
	//	ofn.hwndOwner = hWnd;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = gszFileFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	//	ofn.lpstrFile = NULL;     //调用 GetOpenFileName 函数前设置        
	ofn.nMaxFile = MAX_PATH;
	//	ofn.lpstrFileTitle = NULL;     //调用 GetOpenFileName 函数前设置
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = NULL;
	//	ofn.Flags = 0;        //调用 GetOpenFileName 函数前设置
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = TEXT("drw");//缺省后缀
	ofn.lCustData = 0L;
	ofn.lpfnHook = NULL;

	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = gszFileName;
	ofn.lpstrFileTitle = gszFileTitle;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn))
	{
		return true;
	}
	return false;
}