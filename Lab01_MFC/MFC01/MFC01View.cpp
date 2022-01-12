
// MFC01View.cpp: CMFC01View 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Key.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC01.h"
#endif

#include "MFC01Doc.h"
#include "MFC01View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MainFrm.h"


// CMFC01View

IMPLEMENT_DYNCREATE(CMFC01View, CView)

BEGIN_MESSAGE_MAP(CMFC01View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CHAR()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFC01View 构造/析构

CMFC01View::CMFC01View() noexcept
{
	// TODO: 在此处添加构造代码
	

}

CMFC01View::~CMFC01View()
{
}

BOOL CMFC01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	InitLetter(m_randString);
	m_rect = new CRect(10 , 10, 300, 300);
	m_isStart = true;
		//  CREATESTRUCT cs 来修改窗口类或样式
	cs.cx = 100;
	cs.cy = 100;
	//cs.lpszName = "左长盛";

	return CView::PreCreateWindow(cs);
}

// CMFC01View 绘图

void CMFC01View::OnDraw(CDC* pDC)
{
	CMFC01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFont font; CFont* pFontOld;
	GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT),
		(PTSTR)&m_logFont);
	m_logFont.lfHeight = 10;
	m_logFont.lfWidth =10;
	font.CreateFontIndirect(&m_logFont); //参数含义1，字体大小，2字体类型，3字体颜色	
	pFontOld  = pDC->SelectObject(&font);


	pDC->TextOut(10, 20, "按下ESC退出游戏");
	
	CString temp;
	temp.Format("当前游戏得分：%d", GameScore);
	pDC->TextOut(10, 60, temp);
	
	pDC->SetBkColor(RGB(255, 0, 0));
	pDC->SetTextColor(RGB(0, 0,255));

	if (m_isStart == true)
	pDC->TextOut(10, 40, "按下F键开始游戏");
	else
	{
		pDC->TextOut(10, 40, m_randString);
		CRect rect(100, 200, 300, 400);
		//pDC->DrawText(m_randString, rect , DT_SINGLELINE);
		//显示的结果完全 一致:

	}
	pDC->SelectObject(pFontOld);

}

void CMFC01View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFC01View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFC01View 诊断

#ifdef _DEBUG
void CMFC01View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC01Doc* CMFC01View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC01Doc)));
	return (CMFC01Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC01View 消息处理程序


void CMFC01View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_isStart == true)
	{
		if (nChar == 'F')	
			m_isStart = false;
	}
	else
	{
		if (nChar == VK_ESCAPE)		
			PostQuitMessage(-1);	
		else
		{
			int pos = m_randString.Find(nChar);
			if (pos != -1)
			{
				m_randString.Delete(pos, 1);
				GameScore += Score_aChar;
			}
			if (m_randString.IsEmpty() == true)
			{
				InitLetter(m_randString);
				GameScore += Score_aString;
			}
		}
	}

	Invalidate();
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMFC01View::OnMouseMove(UINT nFlags, CPoint point)
{
	
	CString str;
	str.Format("x:%d,y:%d", point.x, point.y);
	CClientDC dc(this);
	dc.TextOutA(300, 400, str);

	//((CMainFrame*)AfxGetMainWnd())->SetSSMousePos(str);

	CView::OnMouseMove(nFlags, point);
}
