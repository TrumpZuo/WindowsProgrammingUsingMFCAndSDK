
// MFC_practiceView.cpp: CMFCpracticeView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Resource.h"
#include "MainFrm.h"
#include "CgetPenColorDig.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC_practice.h"
#endif

#include "MFC_practiceDoc.h"
#include "MFC_practiceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCpracticeView

IMPLEMENT_DYNCREATE(CMFCpracticeView, CView)

BEGIN_MESSAGE_MAP(CMFCpracticeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_MBUTTONDOWN()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_POPMENU_POPMENU32780, &CMFCpracticeView::OnPopmenu_02_show)
ON_WM_CREATE()
ON_COMMAND(ID_TESTMYMENU_TEST01, &CMFCpracticeView::OnTestmymenuTest01)
ON_UPDATE_COMMAND_UI(ID_TESTMYMENU_TEST01, &CMFCpracticeView::OnUpdateTestmymenuTest01)
ON_COMMAND(ID_TESTMYMENU_TEST02, &CMFCpracticeView::OnTestmymenuTest02)
ON_UPDATE_COMMAND_UI(ID_TESTMYMENU_TEST02, &CMFCpracticeView::OnUpdateTestmymenuTest02)
ON_COMMAND(ID_TESTMYMENU_TESTDIG, &CMFCpracticeView::OnTestmymenuTestdig)
END_MESSAGE_MAP()

// CMFCpracticeView 构造/析构

CMFCpracticeView::CMFCpracticeView() noexcept
{
	// TODO: 在此处添加构造代码
	m_bDraw=false;
	
}

CMFCpracticeView::~CMFCpracticeView()
{
}

BOOL CMFCpracticeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCpracticeView 绘图

void CMFCpracticeView::OnDraw(CDC* pDC)
{
	CMFCpracticeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOut(120, 80, L"Hello, it's MFC Application");
	pDC->MoveTo(100, 100);	pDC->LineTo(300, 100);

	pDC->Rectangle(100,200,300,400); 
	pDC->Ellipse(100, 200, 300, 400);
	
}


// CMFCpracticeView 打印

BOOL CMFCpracticeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCpracticeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCpracticeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCpracticeView 诊断

#ifdef _DEBUG
void CMFCpracticeView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCpracticeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCpracticeDoc* CMFCpracticeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCpracticeDoc)));
	return (CMFCpracticeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCpracticeView 消息处理程序


//void CMFCpracticeView::OnMButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CView::OnMButtonDown(nFlags, point);
//}


void CMFCpracticeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_ptOrgin = point;
	m_bDraw = true;

	m_ptOld = m_ptOrgin;
   //  MessageBox(L"GetStart");

	CView::OnLButtonDown(nFlags, point);
}


void CMFCpracticeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//CDC* pDC = GetDC();
	//pDC->MoveTo(m_ptOrgin);
	//pDC->LineTo(point);
	//ReleaseDC(pDC);

	m_bDraw = false;

	CPen pen(PS_SOLID, 10/*宽度*/,RGB(255,0,0));
	CBrush brush(BS_SOLID, RGB(255, 0, 0));

	CClientDC dc( this );

	CPen* pOLdPen = dc.SelectObject(&pen);
	CBrush* pOLdBrush = dc.SelectObject(&brush);

	//可以将 线画到工具框 内，将无法更新 起始点的位置；

	dc.Rectangle(CRect(m_ptOrgin, point) );

	dc.SelectObject(pOLdPen);
	dc.SelectObject(pOLdBrush);

	CView::OnLButtonUp(nFlags, point);


}


void CMFCpracticeView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1/*宽度*/,m_penColor);
	CPen* pOLdPen = dc.SelectObject(&pen);
	if (m_bDraw == true)
	{
		//dc.SetROP2(R);
		dc.MoveTo(m_ptOrgin);
		dc.LineTo(point);
		dc.LineTo(m_ptOld);
		m_ptOld = point;
	}

	dc.SelectObject(pOLdPen);
	CString str;
	str.Format(L"x:%d,y:%d", point.x, point.y);

	( (CMainFrame*)GetParent() )->m_wndStatusBar.SetWindowTextW(str); 
	CView::OnMouseMove(nFlags, point);
}


void CMFCpracticeView::OnRButtonDown(UINT nFlags, CPoint point)
{
	//CString str;
	//str.Format(L"鼠标坐标为  x:%d, y:%d", point.x, point.y);
	//this->MessageBox(str);
	
	CMenu PopMenu;
	PopMenu.LoadMenuW(IDR_MENU1);

	CMenu* SubMenu;
	SubMenu = PopMenu.GetSubMenu(0);

	ClientToScreen(&point);
	SubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y,this);
	CView::OnRButtonDown(nFlags, point);
}


void CMFCpracticeView::OnPopmenu_02_show()
{
	MessageBox(L"PopMenu02 is Clicked");
}


int CMFCpracticeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;


 //在View中 新建ON_CREATE 的消息，可以修改 窗口鼠标，背景；窗口的图标在 Frame 的preCreate 中进行修改
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);
	SetClassLong(m_hWnd, GCL_HCURSOR, (long)LoadCursor(hInstance,MAKEINTRESOURCE( IDC_MYCURSOR) ));
	SetClassLong(m_hWnd, GCL_HBRBACKGROUND, (long)GetStockObject(GRAY_BRUSH));



	return 0;
}
void CMFCpracticeView::OnTestmymenuTest01()
{
	m_con = 1;
}
void CMFCpracticeView::OnUpdateTestmymenuTest01(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( m_con==1);
}
void CMFCpracticeView::OnTestmymenuTest02()
{
	m_con = 2;
}
void CMFCpracticeView::OnUpdateTestmymenuTest02(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_con == 2);
}


void CMFCpracticeView::OnTestmymenuTestdig()
{
	CgetPenColorDig dig;
	if (dig.DoModal() == IDOK)
	{
		m_penColor = RGB(dig.m_ColorR, dig.m_ColorG, dig.m_ColorB);
	}
}
