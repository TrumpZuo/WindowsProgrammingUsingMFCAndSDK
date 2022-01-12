
// MFC03View.cpp: CMFC03View 类的实现
#include "pch.h"
#include "framework.h"
#include "CDlgChild.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC03.h"
#endif

#include "resource.h"
#include "MFC03Doc.h"
#include "MFC03View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFC03View

IMPLEMENT_DYNCREATE(CMFC03View, CView)

BEGIN_MESSAGE_MAP(CMFC03View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_CHANGE_CURSOR1, &CMFC03View::OnChangeCursor1)
	ON_COMMAND(ID_CHANGE_CURSOR2, &CMFC03View::OnChangeCursor2)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFC03View 构造/析构

CMFC03View::CMFC03View() noexcept
{
	// TODO: 在此处添加构造代码
	m_rect = { 10,10,200,30 };

}

CMFC03View::~CMFC03View()
{
}

BOOL CMFC03View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式


	return CView::PreCreateWindow(cs);
}

// CMFC03View 绘图

void CMFC03View::OnDraw(CDC* pDC)
{
	CMFC03Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	POINT pts[11] = {
	{20,20},{50,100},{105,102},{140,120},
	{18,40},{100,30},{170,50},{200,40},
	{19,40},{170,100},{200,138}
	};
	DWORD dwPtPerLine[4] = { 4,4,3 };


	//Polyline
	//  PolyPolygon(pts, dwPtPerLine,3);
	//Polygon
	pDC->PolyPolyline(pts, dwPtPerLine, 3);

	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->SetTextCharacterExtra(5);

	pDC->TextOutW(300, 300, m_szBuffer);
	pDC->TextOutW(250, 250, m_time);

}

void CMFC03View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFC03View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFC03View 诊断

#ifdef _DEBUG
void CMFC03View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC03View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC03Doc* CMFC03View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC03Doc)));
	return (CMFC03Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC03View 消息处理程序


int CMFC03View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

//this->m_hWnd  可以直接访问 当前 运行 函数的句柄，
//CWnd是MFC窗体类,CWnd中包含HWND句柄成员对象是m_hWnd
//HWND hWnd = GetActiveView()->m_hWnd;
//= AfxGetMainWnd()->m_hWnd;

	 //在View中 新建ON_CREATE 的消息，可以修改 窗口鼠标，背景；窗口的图标在 Frame 的preCreate 中进行修改
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);
	SetClassLong(m_hWnd, GCL_HCURSOR, (long)LoadCursor(hInstance, MAKEINTRESOURCE(IDC_MFC03_CURSOR1)));
	SetClassLong(m_hWnd, GCL_HBRBACKGROUND, (long)GetStockObject(GRAY_BRUSH));

	static int cxChar, cyChar;
	static HWND  hWndButton;
	for (int i = 0; i < 26; i++)
	{
		ButtonName[i][0] = i + 'a';
		ButtonName[i][1] =  '\0';
	}


	SetTimer(1, 1000, NULL);
	cxChar = LOWORD(GetDialogBaseUnits());
	cyChar = HIWORD(GetDialogBaseUnits());

	cxChar *= 5;
	cyChar *= (5 * 0.618);

	for (int cnt = 0; cnt < 26; cnt++)
	{
		int x, y;
		x = cxChar * (cnt % 13);
		y = cyChar * (cnt / 13);

		hWndButton = CreateWindow(TEXT("button"),			    //窗口类名		
			ButtonName[cnt],
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // 子窗口 类型：
			x, y, cxChar, cyChar,					//x,y 坐标； 宽度、高度；
			 this->m_hWnd,                       //父窗口句柄
			(HMENU)cnt,		                        //编辑控件子窗口标识
			(HINSTANCE)GetWindowLong(this->m_hWnd , GWL_HINSTANCE),
			NULL);
	}

}


BOOL CMFC03View::OnCommand(WPARAM wParam, LPARAM lParam)
{
		char key;
		key = LOWORD(wParam) + 'a';
		m_szBuffer += key;
		Invalidate();
	return CView::OnCommand(wParam, lParam);
}

//HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);
//
//wcChild.style = CS_VREDRAW | CS_HREDRAW;
//wcChild.lpfnWndProc = NULL;// = ChildWndProc;
//wcChild.cbClsExtra = 0;
//wcChild.cbWndExtra = sizeof(long);
//// 全局数据区域，存储子窗口的信息 set Window long;cb= count bytes
//wcChild.hInstance = hInstance;
//wcChild.hIcon = NULL;
//wcChild.hCursor = LoadCursor(NULL, IDC_ARROW);
//wcChild.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
////GetStockObject (HOLLOW_BRUSH);
//wcChild.lpszMenuName = NULL;
//wcChild.lpszClassName = TEXT("ChildWin_Child");    //子窗口类名称;
//
//if (!RegisterClass(&wcChild))
//{
//	MessageBox(TEXT("注册子窗口类失败！"));
//	return 0;
//}
//
//else {
//
//	//创建类似“画图”程序中绘图工具栏的各工具子窗口
//	for (int x = 0; x < COL_NUM; x++)
//		for (int y = 0; y < ROW_NUM; y++)
//		{
//			nChildWin_ID = x << 3 | y;             //子窗口标识值，x*16+y，y应该小于16
//			hChildWnd[x][y]
//				= CreateWindow(TEXT("button"),
//					NULL,
//					WS_CHILDWINDOW | WS_DLGFRAME | WS_VISIBLE,
//					0, 0, 0, 0,
//					this->m_hWnd,
//					(HMENU)(nChildWin_ID),//创建子窗口ID号
//					//0,
//					hInstance, NULL);
//		}
//
//	//令0号子窗口为当前命中的子窗口，全局变量
//	nChildWin_ID = 0;
//	nRow = 0;
//	nCol = 0;
//}


void CMFC03View::OnChangeCursor1()
{
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);
	SetClassLong(m_hWnd, GCL_HCURSOR, (long)LoadCursor(hInstance, MAKEINTRESOURCE(IDC_MFC03_CURSOR1)));

}


void CMFC03View::OnChangeCursor2()
{
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);
	SetClassLong(m_hWnd, GCL_HCURSOR, (long)LoadCursor(hInstance, MAKEINTRESOURCE(IDC_MFC03_CURSOR2)));

}


void CMFC03View::OnTimer(UINT_PTR nIDEvent)
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);

	m_time.Format(L"%d:%d:%d",sysTime.wHour,sysTime.wMinute,sysTime.wSecond);
	Invalidate();
	CView::OnTimer(nIDEvent);
	
}
