#pragma once
#include <windows.h>
#include <windowsx.h>
#include <math.h>
#include"resource.h"

#define BUF_MAX       32
#define TEXT_LEN_MAX    64 

#define DRAWM_SELECT  0  //draw-mode-select
#define DRAWM_LINE    1
#define DRAWM_RECT    2
#define DRAWM_ELLP    3
#define DRAWM_TEXT    4



typedef struct tagMyLine {  //�ߵĽṹ
	POINT ptS;
	POINT ptE;
	LOGPEN lgPen;//ѡ��ʽ��л��ߣ�
}MYLINE;
typedef struct tagMyRect
{
	//CHAR  szContent[TEXT_LEN_MAX];//�����ַ���
	POINT ptS;
	POINT ptE;

	LOGPEN lgPen;
	LOGBRUSH lgBr;
} MYRECT;
typedef struct tagMyEllP
{
	POINT ptS;
	POINT ptE;
	LOGPEN lgPen;
	LOGBRUSH lgBr;
} MYELLP;
typedef struct tagMyText
{
	TCHAR szContent[TEXT_LEN_MAX];
	POINT ptS;
	POINT ptE;
	LOGFONT lgFont;
	COLORREF crText;
} MYTEXT;

//������ڵ� ���� ���ڵĵ�
extern POINT gPtBegin, gPtEnd, gPtChange;

extern UINT Ellp_Length, Ellp_Wildth;
extern UINT gCountText, gCountEllp, gCountLine, gCountRect;


extern  int giDrawState, Change_index;//��ѯ����
extern BOOL gbDrawing;//���ڻ���ͼ�α�־
extern TCHAR   gszFileName[MAX_PATH], gszFileTitle[MAX_PATH];
extern TCHAR   szWndCaption[MAX_PATH];

extern MYTEXT gTexts[BUF_MAX];
extern COLORREF gColorText;
extern TCHAR gBuffer[TEXT_LEN_MAX - 1];

extern MYELLP gEllps[BUF_MAX];
extern MYRECT gRects[BUF_MAX];
// ͼ�����ݻ�����

//MYLINE gLine;
extern MYLINE gLines[BUF_MAX];
extern LOGPEN glogPen; //  ʵ�ı� ���Ϊ1 ��ɫ ����
extern LOGBRUSH glogBr;
extern LOGFONT glogFont;



BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL GetMyColor(HWND hWnd, COLORREF* pColor);
BOOL CALLBACK TextColorInputDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void  ReadFigureData_FileName(LPSTR gszFileName);
void ChooseColorInit(HWND* hWnd, CHOOSECOLOR* cc, COLORREF* crCustomColors);


int SearchInLines(POINT gPtChange, MYLINE* gLines, UINT gCountLine);
void DrawAllLines(HDC hdc);
void DrawAllRects(HDC hdc);
int  SearchInRect(POINT gPtChange, MYRECT* gRects, UINT gCountRect);
void ChangeMyRectColor(HWND hWnd, MYRECT* gRects);
int  SearchInEllp(POINT gPtChange, MYELLP* gEllps, UINT gCountEllp);
void DrawAllEllps(HDC hdc);
//ͨ���Ի��������ı���Ϣ��
void DrawAllText(HDC hdc);
int  SearchInText(POINT gPtChange, MYTEXT* gTexts, UINT gCountText);
void  ChangeMyLineColor(HWND hWnd, MYLINE* gLines);
void  DeleteMyLine(HWND hWnd, MYLINE* gLines);
BOOL CALLBACK TextColorInputDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EllpGetIntDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL GetMyFont(HWND hWnd, LOGFONT* glogFont, COLORREF* pColor);
void  ChangeMyTextFont(HWND hWnd, MYTEXT* gTexts);
BOOL GetOpenFigFileName(HWND hWnd, LPSTR lpFileName);
void  ReadFigureData_FileName(LPSTR gszFileName);
void  SaveFigureData_FileName(LPCTSTR lpFileName);
BOOL GetSaveFigFileName(HWND hWnd, LPSTR lpFileName);






