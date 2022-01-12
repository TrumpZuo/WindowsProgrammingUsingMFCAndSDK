
// MFCextraView.cpp: CMFCextraView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCextra.h"
#endif

#include "MFCextraDoc.h"
#include "MFCextraView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCextraView

IMPLEMENT_DYNCREATE(CMFCextraView, CView)

BEGIN_MESSAGE_MAP(CMFCextraView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCextraView 构造/析构

CMFCextraView::CMFCextraView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCextraView::~CMFCextraView()
{
}

BOOL CMFCextraView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCextraView 绘图

void CMFCextraView::OnDraw(CDC* /*pDC*/)
{
	CMFCextraDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CMFCextraView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCextraView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCextraView 诊断

#ifdef _DEBUG
void CMFCextraView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCextraView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCextraDoc* CMFCextraView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCextraDoc)));
	return (CMFCextraDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCextraView 消息处理程序
