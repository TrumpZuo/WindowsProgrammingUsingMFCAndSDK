
// Lab04View.cpp: CLab04View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Lab04.h"
#endif

#include "Lab04Doc.h"
#include "Lab04View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab04View

IMPLEMENT_DYNCREATE(CLab04View, CView)

BEGIN_MESSAGE_MAP(CLab04View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CHANGE_TEXT_COLOR, &CLab04View::OnChangeTextColor)
	ON_COMMAND(ID_CHANGE_BACK_COLOR, &CLab04View::OnChangeBackColor)
	ON_WM_CREATE()
	ON_COMMAND(ID_CHANGE_TEXT, &CLab04View::OnChangeText)
	ON_COMMAND(ID_CHANGE_BACK, &CLab04View::OnChangeBack)
END_MESSAGE_MAP()

// CLab04View 构造/析构

CLab04View::CLab04View() noexcept
{
	// TODO: 在此处添加构造代码

	m_rect = { 100,200,300,400 };
	m_str = "zcs201900800413";
	m_color = RGB(255, 0, 0);
	m_bk =  RGB(0,0,255);
}

CLab04View::~CLab04View()
{
}

BOOL CLab04View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLab04View 绘图

void CLab04View::OnDraw(CDC* pDC)
{
	CLab04Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int B = m_color >> 16;
	int G = (m_color >> 8) % 256;
	int R = m_color % 256;

	CString str; 
	str.Format(L"R:%d  G:%d  B:%d", R, G, B);
	pDC->TextOutW(200, 300, str);


	pDC->SetTextColor(m_color);
	pDC->SetBkColor(m_bk);
	pDC->TextOutW(200, 300, str);
	pDC->DrawText(m_str, m_rect, DT_SINGLELINE);

	

}

void CLab04View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLab04View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLab04View 诊断

#ifdef _DEBUG
void CLab04View::AssertValid() const
{
	CView::AssertValid();
}

void CLab04View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab04Doc* CLab04View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab04Doc)));
	return (CLab04Doc*)m_pDocument;
}
#endif //_DEBUG


// CLab04View 消息处理程序



















void CLab04View::OnChangeTextColor()
{
}


void CLab04View::OnChangeBackColor()
{
	// TODO: 在此添加命令处理程序代码
}


int CLab04View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


void CLab04View::OnChangeText()
{
	CColorDialog oc;
	if (oc.DoModal() == IDOK)
	{
		m_color = oc.m_cc.rgbResult;
	}

	//使用 setTextColor 
	Invalidate();
}


void CLab04View::OnChangeBack()
{
	CColorDialog oc;
	if (oc.DoModal() == IDOK)
	{
		m_bk = oc.m_cc.rgbResult;
	}

	//使用 setTextColor 
	Invalidate();
}
