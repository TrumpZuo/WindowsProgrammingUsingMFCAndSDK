
// MFC05View.cpp: CMFC05View 类的实现
//

#include "pch.h"
#include "framework.h"
#include "draw.h"
#include "CDlgText.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC05.h"
#endif

#include "MFC05Doc.h"
#include "MFC05View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC05View

IMPLEMENT_DYNCREATE(CMFC05View, CView)

BEGIN_MESSAGE_MAP(CMFC05View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_SELECT_NULL, &CMFC05View::OnSelectNull)
	ON_COMMAND(ID_SELECT_LINE, &CMFC05View::OnSelectLine)
	ON_COMMAND(ID_SELECT_RECT, &CMFC05View::OnSelectRect)
	ON_COMMAND(ID_SELECT_ELLP, &CMFC05View::OnSelectEllp)
	ON_COMMAND(ID_SELECT_TEXT, &CMFC05View::OnSelectText)
	ON_UPDATE_COMMAND_UI(ID_SELECT_NULL, &CMFC05View::OnUpdateSelectNull)
	ON_UPDATE_COMMAND_UI(ID_SELECT_LINE, &CMFC05View::OnUpdateSelectLine)
	ON_UPDATE_COMMAND_UI(ID_SELECT_RECT, &CMFC05View::OnUpdateSelectRect)
	ON_UPDATE_COMMAND_UI(ID_SELECT_ELLP, &CMFC05View::OnUpdateSelectEllp)
	ON_UPDATE_COMMAND_UI(ID_SELECT_TEXT, &CMFC05View::OnUpdateSelectText)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_CHANGE_LINE_COLOR, &CMFC05View::OnChangeLineColor)
	ON_COMMAND(ID_CHANGE_TEXT_ALL, &CMFC05View::OnChangeTextAll)
END_MESSAGE_MAP()

// CMFC05View 构造/析构

CMFC05View::CMFC05View() noexcept
{
	// TODO: 在此处添加构造代码
	m_select_mode = SELECT_NULL;
	m_isDraw = false;
	m_penColor = RGB(255, 0, 0);
	m_brushColor = RGB(0, 255, 0);
	m_penStyle = PS_SOLID;
	GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT),
		(PTSTR)&m_logFont);


}

CMFC05View::~CMFC05View()
{
}

BOOL CMFC05View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFC05View 绘图

void CMFC05View::OnDraw(CDC* pDC)
{
	CMFC05Doc* pDoc = GetDocument();

	//从文件中读取，使用 pDoc 访问存储的文件
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	POSITION pos = pDoc->m_allFigure.GetHeadPosition();
	while (pos != NULL)
	{
		pDoc->m_allFigure.GetAt(pos)->Draw(pDC);
		pDoc->m_allFigure.GetNext(pos);
	}
	// TODO: 在此处为本机数据添加绘制代码
}



void CMFC05View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFC05View 诊断

#ifdef _DEBUG
void CMFC05View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC05View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC05Doc* CMFC05View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC05Doc)));
	return (CMFC05Doc*)m_pDocument;
}
#endif //_DEBUG
// CMFC05View 消息处理程序
void CMFC05View::OnSelectNull()
{
	m_select_mode = SELECT_NULL;
}
void CMFC05View::OnSelectLine()
{
	m_select_mode = SELECT_LINE;
}
void CMFC05View::OnSelectRect()
{
	m_select_mode = SELECT_RECT;
}
void CMFC05View::OnSelectEllp()
{
	m_select_mode = SELECT_ELLP;
}
void CMFC05View::OnSelectText()
{
	m_select_mode = SELECT_TEXT;
}
void CMFC05View::OnUpdateSelectNull(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_select_mode == SELECT_NULL);
}
void CMFC05View::OnUpdateSelectLine(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_select_mode == SELECT_LINE);
}
void CMFC05View::OnUpdateSelectRect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_select_mode == SELECT_RECT);
}
void CMFC05View::OnUpdateSelectEllp(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_select_mode == SELECT_ELLP);
}
void CMFC05View::OnUpdateSelectText(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_select_mode == SELECT_TEXT);
}


void CMFC05View::OnRButtonDown(UINT nFlags, CPoint point)
{
	CView::OnRButtonDown(nFlags, point);
}
void CMFC05View::OnRButtonUp(UINT  nFlags , CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFC05View::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_select_mode != SELECT_NULL)
	{
		m_startPoint = point;
		m_isDraw = true;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMFC05View::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_isDraw == true)
	{
		m_endPoint = point;
		m_isDraw = false;

		CFigure* newFigure = NULL;
		LOGPEN penLine = { m_penStyle , {1,1}, m_penColor };
		LOGBRUSH brushRect = { BS_SOLID, m_brushColor,HS_VERTICAL };
		switch (m_select_mode)
		{
		case SELECT_LINE:
			newFigure = new CMyLine(m_startPoint, m_endPoint, penLine);
			newFigure->m_type = SELECT_LINE;
			break;
		case SELECT_RECT:
			newFigure = new CMyRect(m_startPoint, m_endPoint, brushRect, penLine);
			newFigure->m_type = SELECT_RECT;
			break;
		case SELECT_ELLP:
			newFigure = new CMyEllp(m_startPoint, m_endPoint, brushRect, penLine);
			newFigure->m_type = SELECT_ELLP;
			break;
		case SELECT_TEXT:
		{
			CString str;
			CDlgText dt;
			if (dt.DoModal() == IDOK)
			{
				str = dt.m_textString;
			}
			newFigure = new CMyText(m_startPoint, str, m_logFont, m_brushColor);
			newFigure->m_type = SELECT_TEXT;
			break;
		}
		default:
			break;
		}
		if (newFigure != NULL)
		{
			GetDocument()->addNewFigure(newFigure);
			Invalidate();
		}

	}

	CView::OnLButtonUp(nFlags, point);
}


void CMFC05View::OnChangeLineColor()
{
	CColorDialog oc;
	if (oc.DoModal() == IDOK)
	{
		m_penColor = oc.m_cc.rgbResult;
	}
	//必须实时进行更新：
	Invalidate();
	
}


void CMFC05View::OnChangeTextAll()
{
	CFontDialog ob;
	if (ob.DoModal() == IDOK)
	{
		m_brushColor = ob.m_cf.rgbColors;
		m_logFont = *(ob.m_cf.lpLogFont);
	}
	
}
