#pragma once
#include "resource.h"
#include "MyDraw.h"
#include <winuser.h>

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
	static TCHAR szAppName[] = TEXT("Draw_Figure_Programme");
	HWND hwnd;
	WNDCLASS wc;

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 	LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = szAppName;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("注册窗口类失败！"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("矢量图形编辑器"),
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
	HDC hdc;
	PAINTSTRUCT ps;

	static CHOOSEFONT   cf;
	static HFONT        hFont;

	static HMENU hMenuLine;
	static HMENU hMenuRect;
	static HMENU hMenuText;
	static HMENU hMenuEllp;
	static HINSTANCE hInstance = (HINSTANCE)GetWindowLongA(hWnd, GWLP_HINSTANCE);

	switch (message)
	{
	case WM_CREATE:
     //初始化字体
		GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT),
			(PTSTR)&glogFont);        //初始化结构 logfont
	
		hMenuLine = LoadMenu((HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDR_MENU2));	
		hMenuRect = LoadMenu((HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDR_MENU3));
		hMenuText = LoadMenu((HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDR_MENU4));
		hMenuEllp = LoadMenu((HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDR_MENU5));
	
		return 0;

	case WM_SIZE:
		//调整窗口大小；
		return 0;

	case WM_PAINT:
		//使用begin paint 获得 wm-paint中的hdc
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 200, "Made By 0413左长盛", 18);
		DrawAllLines(hdc);//绘制所有直线；
		DrawAllRects(hdc);
		DrawAllEllps(hdc);
		DrawAllText(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_INITMENUPOPUP:
		if (lParam == 1)
		{

			CheckMenuItem((HMENU)wParam, ID_DRAW_SELECT,
				(giDrawState == DRAWM_SELECT) ? MF_CHECKED : MF_UNCHECKED);
			CheckMenuItem((HMENU)wParam, ID_DRAW_LINE,
				(giDrawState == DRAWM_LINE) ? MF_CHECKED : MF_UNCHECKED);
			CheckMenuItem((HMENU)wParam, ID_DRAW_RECT,
				(giDrawState == DRAWM_RECT) ? MF_CHECKED : MF_UNCHECKED);
			CheckMenuItem((HMENU)wParam, ID_DRAW_ECLIPSE,
				(giDrawState == DRAWM_ELLP) ? MF_CHECKED : MF_UNCHECKED);
			CheckMenuItem((HMENU)wParam, ID_DRAW_TEXT,
				(giDrawState == DRAWM_TEXT) ? MF_CHECKED : MF_UNCHECKED);
		}

	case WM_COMMAND:        	// 响应编辑控件通知消息
		if (lParam == NULL)
		{
			switch (wParam)
			{
			case ID_FILE_OPEN:
				if (GetOpenFigFileName(hWnd, gszFileName))
				{
					ReadFigureData_FileName(gszFileName);
					InvalidateRect(hWnd, NULL, false);
				}
				break;
			case ID_FILE_EXIT:
				PostQuitMessage(0);
				return 0;break;
			case ID_FILE_SAVE://save
				//SaveFigureData(hWnd);
				if (GetSaveFigFileName(hWnd, gszFileName))
				{
					SaveFigureData_FileName(gszFileName);
				}
				break;
			case ID_DRAW_SELECT:   giDrawState = DRAWM_SELECT; break;
			case ID_DRAW_LINE:     giDrawState = DRAWM_LINE; break;
			case ID_DRAW_RECT:     giDrawState = DRAWM_RECT; break;
			case ID_DRAW_ECLIPSE:  giDrawState = DRAWM_ELLP; break;
			case ID_DRAW_TEXT:     giDrawState = DRAWM_TEXT; break;
			case ID_SETTINGS_PENCOLOR:
				GetMyColor(hWnd, &glogPen.lopnColor);//设置笔的颜色；

				break;
			case ID_SETTINGS_FONT:
				GetMyFont(hWnd, &glogFont, &gColorText);
				break;
			case ID_SETTINGS_TEXTCOLOR:
	
					;

				break;

			case ID_SETTINGS_BRUSHCOLOR:
				GetMyColor(hWnd, &glogBr.lbColor);
				break;
				//对线进行修改：
			case ID_LINE_CHANGE_COLOR:			
				if (Change_index != -1)
				{
					ChangeMyLineColor(hWnd, &gLines[Change_index]);
					Change_index = -1;
					InvalidateRect(hWnd, NULL, true);
				}
				break;
			
			case ID_LINE_CHANGE_PEN_SOLID:
				if (Change_index != -1)
				{
					gLines[Change_index].lgPen.lopnStyle = PS_SOLID;
					Change_index = -1;
					InvalidateRect(hWnd, NULL, true);
				}
				break;
			case ID_LINE_CHANGE_PEN_DOT:
				if (Change_index != -1)
				{
					gLines[Change_index].lgPen.lopnStyle = PS_DOT;
					Change_index = -1;
					InvalidateRect(hWnd, NULL, true);
				}
				break;
			case ID_LINE_CHANGE_PEN_DASHDOT:
				if (Change_index != -1)
				{
					gLines[Change_index].lgPen.lopnStyle = PS_DASHDOT;
					Change_index = -1;
					InvalidateRect(hWnd, NULL, true);
				}
				break;
			case ID_CHANGE_LINE_DELETE:
				if (Change_index != -1)
				{
					DeleteMyLine(hWnd, &gLines[Change_index]);
					InvalidateRect(hWnd, NULL, true);
				}
				break;

				//对矩形进行修改
			case ID_RECT_CHANGE_COLOR:
				if (Change_index != -1)
				{
					ChangeMyRectColor(hWnd, &gRects[Change_index]);
					Change_index = -1;
					InvalidateRect(hWnd, NULL, true);
				}
				break;
			case ID_RECT_CHANGE_DELETE:
				if (Change_index != -1)
				{
					gRects[Change_index].ptS = gRects[Change_index].ptE;
					Change_index = -1;
					InvalidateRect(hWnd, NULL, true);
				}
				break;
				//对文本框进行修改
			case ID_TEXT_CHANGE_FONT:
				if (Change_index != -1)
				{
					ChangeMyTextFont(hWnd, &gTexts[Change_index]);
					Change_index = -1;
					InvalidateRect(hWnd, NULL, true);
				}
				break;
			case ID_TEXT_CHANGE_CONTENT:
				if (Change_index != -1)
				{
					if (	
						DialogBox(
							hInstance,
							MAKEINTRESOURCE(IDD_DIALOG1),
							hWnd,
							(DLGPROC)EllpGetIntDlg)									
						)

					{
						strcpy_s(gTexts[Change_index].szContent, gBuffer);
						InvalidateRect(hWnd, NULL, true);
					}
					Change_index = -1;
				}
				break;
				//对椭圆进行修改
			case ID_ELLP_CHANGE_SIZE:
				if (Change_index != -1)
				{
					if (
						DialogBox(
							hInstance,
							MAKEINTRESOURCE(IDD_DIALOG2),
							hWnd,
							(DLGPROC)EllpGetIntDlg)
						)
					{
						gEllps[Change_index].ptE.x = gEllps[Change_index].ptS.x + Ellp_Length;
						gEllps[Change_index].ptE.y = gEllps[Change_index].ptS.y + Ellp_Wildth;
						InvalidateRect(hWnd, NULL, true);
					}
					Change_index = -1;
				}

				break;
			case ID_ELLP_CHANGE_POSITION:
				if (Change_index != -1)
				{
					if (
						   DialogBox(
							hInstance,
							MAKEINTRESOURCE(IDD_DIALOG2),
							hWnd,
							(DLGPROC)EllpGetIntDlg)
						)
					{
						gEllps[Change_index].ptE.x = gEllps[Change_index].ptE.x - gEllps[Change_index].ptS.x + Ellp_Length;
						gEllps[Change_index].ptE.y = gEllps[Change_index].ptE.y - gEllps[Change_index].ptS.y + Ellp_Wildth;
						gEllps[Change_index].ptS.x =  Ellp_Length;
						gEllps[Change_index].ptS.y =  Ellp_Wildth;

						InvalidateRect(hWnd, NULL, true);
					}
					Change_index = -1;
				}

				break;

			}
		}
		return 0;
		//划线 获得起点与 终点；
	case WM_LBUTTONDOWN:
		gPtBegin.x = GET_X_LPARAM(lParam);
		gPtBegin.y = GET_Y_LPARAM(lParam);
		if (giDrawState != DRAWM_SELECT)
		{
			gbDrawing = TRUE;    //正在绘制图形
			SetCapture(hWnd);
		}
		return 0;
	case WM_LBUTTONUP:
		gPtEnd.x = GET_X_LPARAM(lParam);
		gPtEnd.y = GET_Y_LPARAM(lParam);
		if (giDrawState != 0)
		{
			gbDrawing = FALSE;
			ReleaseCapture();
			switch (giDrawState)
			{
			case DRAWM_LINE:
				if (gCountLine < BUF_MAX)
				{
					gLines[gCountLine].ptS = gPtBegin;
					gLines[gCountLine].ptE = gPtEnd;//连线

					gLines[gCountLine].lgPen = glogPen;

					gCountLine++;
				}
				break;
			case DRAWM_RECT:
					if (gCountRect < BUF_MAX)
					{
						gRects[gCountRect].ptS = gPtBegin;
						gRects[gCountRect].ptE = gPtEnd;
						gRects[gCountRect].lgPen = glogPen;
						gRects[gCountRect].lgBr = glogBr;
						gCountRect++;

					}
					break;
			case DRAWM_ELLP:
					if (gCountEllp < BUF_MAX)
					{
						gEllps[gCountEllp].ptS = gPtBegin;
						gEllps[gCountEllp].ptE = gPtEnd;
						gEllps[gCountEllp].lgPen = glogPen;
						gEllps[gCountEllp].lgBr = glogBr;
						gCountEllp++;
					}
					break;
			case DRAWM_TEXT:
				if (gCountText < BUF_MAX)
				{
					if (
						   1
						
						
						)
					{
						gTexts[gCountText].ptS = gPtBegin;
						gTexts[gCountText].ptE = { gPtBegin.x+50 ,gPtBegin.y+25};
						strcpy_s(gTexts[gCountText].szContent, gBuffer);
						gTexts[gCountText].lgFont = glogFont;
						gTexts[gCountText].crText = gColorText;
						gCountText++;

						InvalidateRect(hWnd, NULL, true);
					}
				}
				break;
			default:
				break;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	case WM_RBUTTONDOWN:
	{
		gPtChange.x = GET_X_LPARAM(lParam);
		gPtChange.y = GET_Y_LPARAM(lParam);
		int index1 = SearchInLines(gPtChange, gLines, gCountLine);
		if (index1 != -1)
		{
			Change_index = index1;
			ClientToScreen(hWnd, &gPtChange);
			TrackPopupMenu(hMenuLine, TPM_RIGHTBUTTON, gPtChange.x, gPtChange.y, 0, hWnd, NULL);
			return 0;
		}
		
		int  index2 = SearchInRect(gPtChange, gRects, gCountRect);
		if (index2 != -1)
		{
			Change_index = index2;
			ClientToScreen(hWnd, &gPtChange);
			TrackPopupMenu(hMenuRect, TPM_RIGHTBUTTON, gPtChange.x, gPtChange.y, 0, hWnd, NULL);
			return 0;
		}

		int  index3 = SearchInText(gPtChange, gTexts, gCountText);
		if (index3 != -1)
		{
			Change_index = index3;
			ClientToScreen(hWnd, &gPtChange);
			TrackPopupMenu(hMenuText, TPM_RIGHTBUTTON, gPtChange.x, gPtChange.y, 0, hWnd, NULL);
			return 0;
		}

		int  index4 = SearchInEllp(gPtChange, gEllps, gCountEllp);
		if (index4 != -1)
		{
			Change_index = index4;
			ClientToScreen(hWnd, &gPtChange);
			TrackPopupMenu(hMenuEllp, TPM_RIGHTBUTTON, gPtChange.x, gPtChange.y, 0, hWnd, NULL);
			return 0;
		}	
	}
		return 0;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}



