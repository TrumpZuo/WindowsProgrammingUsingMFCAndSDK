
// E201900800413View.cpp: CE201900800413View 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CDlgSale.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "E201900800413.h"
#endif

#include "E201900800413Doc.h"
#include "E201900800413View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CE201900800413View

IMPLEMENT_DYNCREATE(CE201900800413View, CView)

BEGIN_MESSAGE_MAP(CE201900800413View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DATA_INPUT, &CE201900800413View::OnDataInput)
	ON_COMMAND(ID_LAST, &CE201900800413View::OnLast)
END_MESSAGE_MAP()

// CE201900800413View 构造/析构

CE201900800413View::CE201900800413View() noexcept
{
	// TODO: 在此处添加构造代码
	row = 60;

}

CE201900800413View::~CE201900800413View()
{
}

BOOL CE201900800413View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CE201900800413View 绘图

void CE201900800413View::OnDraw(CDC* pDC)
{
	CE201900800413Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	double allMoney = 0;

	pDC->TextOut(20, 10, "左长盛201900800413");
	pDC->TextOut(200, 30, "名称");								
	pDC->TextOut(400, 30, "单价");
	pDC->TextOut(600, 30, "销售件数");
	pDC->TextOut(800, 30, "金额");

	POSITION pos = pDoc->m_goods.GetHeadPosition();
	

	row = 60;
	while (pos != NULL)
	{
		Goods* good = pDoc->m_goods.GetAt(pos);

		pDC->TextOut(200, row, good->m_name );
		CString price;
		price.Format("%f", good->m_price);
		pDC->TextOut(400, row, price);
		CString count;
		count.Format("%d",good->m_count);
		pDC->TextOut(600, row, count);
		CString money;
		money.Format("%f", good->m_money);
		pDC->TextOut(800, row, money);

		row += 30;
		allMoney += good->m_money;
		pDoc->m_goods.GetNext(pos);
	}

	CString all;
	all.Format("销售的总金额为： %f", allMoney);
	pDC->TextOut(800, row, all);




	// TODO: 在此处为本机数据添加绘制代码
}

void CE201900800413View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CE201900800413View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CE201900800413View 诊断

#ifdef _DEBUG
void CE201900800413View::AssertValid() const
{
	CView::AssertValid();
}

void CE201900800413View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CE201900800413Doc* CE201900800413View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CE201900800413Doc)));
	return (CE201900800413Doc*)m_pDocument;
}
#endif //_DEBUG


// CE201900800413View 消息处理程序


void CE201900800413View::OnDataInput()
{
	CDlgSale oc;
	if (oc.DoModal() == IDOK)
	{
		Goods* newGood = new  Goods(oc.m_name, oc.m_price, oc.m_count);
		GetDocument()->AddOneGood(newGood);
	}

	//必须实时进行更新：
	Invalidate();
}

//使用柱状图进行显示：
void CE201900800413View::OnLast()
{
	int col = 200;
	row += 30;
	CClientDC dc(this);

	dc.TextOut(col, row,"销售件数");


	POSITION pos = GetDocument()->m_goods.GetHeadPosition();
//柱状标头
	while (pos != NULL)
	{

		Goods* good = GetDocument()->m_goods.GetAt(pos);
		dc.TextOut(col, row, good->m_name);

		col += 200;
		GetDocument()->m_goods.GetNext(pos);
	}




//柱状：


	row += 30;
	 pos = GetDocument()->m_goods.GetHeadPosition();
	//柱状标头





	while (pos != NULL)
	{

		Goods* good = GetDocument()->m_goods.GetAt(pos);
		int count = good->m_count;
		POINT	start = { row,col };
		POINT   end = { row + count , col + 100 };

		CRect  rect;
		rect = new CRect(start, end);


		CBrush brush(BS_SOLID, RGB(255, 0, 0));
		CBrush* pOLdBrush = dc.SelectObject(&brush);

		dc.Rectangle(row, col, row + count, col + 100);
		col += 200;
		GetDocument()->m_goods.GetNext(pos);
	}
		//pDC->TextOut(200, row, good->m_name);
		//CString price;
		//price.Format("%f", good->m_price);
		//pDC->TextOut(400, row, price);
		//CString count;
	



}
