
// Lab06View.cpp: CLab06View 类的实现
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Lab06.h"
#endif
#include "CDlgGetLength.h"
#include "CDlgLocation.h"
#include "CDlgSize.h"
#include "CDlgText.h"
#include "Lab06Doc.h"
#include "Lab06View.h"
#include "MainFrm.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CLab06View
IMPLEMENT_DYNCREATE(CLab06View, CView)

BEGIN_MESSAGE_MAP(CLab06View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAW_SELECT, &CLab06View::OnDrawSelect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SELECT, &CLab06View::OnUpdateDrawSelect)
	ON_COMMAND(ID_DRAW_LINE, &CLab06View::OnDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CLab06View::OnUpdateDrawLine)
	ON_COMMAND(ID_DRAW_RECT, &CLab06View::OnDrawRect)
	ON_COMMAND(ID_DRAW_TEXT, &CLab06View::OnDrawText)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CLab06View::OnDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &CLab06View::OnUpdateDrawRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_TEXT, &CLab06View::OnUpdateDrawText)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, &CLab06View::OnUpdateDrawEllipse)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SETTINGS_BRUSHCOLOR, &CLab06View::OnSettingsBrushcolor)
	ON_COMMAND(ID_SETTINGS_LINECOLOR, &CLab06View::OnSettingsLinecolor)
	ON_COMMAND(ID_SETTINGS_TEXTCOLOR, &CLab06View::OnSettingsTextcolor)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_POPMENU_LINE_COLOR, &CLab06View::OnPopmenuLineColor)
	ON_COMMAND(ID_LINE_STYLE_1, &CLab06View::OnLineStyle1)
	ON_COMMAND(ID_POPMENU_RECT_COLOR, &CLab06View::OnPopmenuRectColor)
	ON_COMMAND(ID_POPMENU_TEXT_FONT, &CLab06View::OnPopmenuTextFont)
	ON_COMMAND(ID_POPMENU_LINE_DELETE, &CLab06View::OnPopmenuLineDelete)
	ON_COMMAND(ID_POPMENU_RECT_DELETE, &CLab06View::OnPopmenuRectDelete)
	ON_COMMAND(ID_POPMENU_TEXT_CONTENT, &CLab06View::OnPopmenuTextContent)
	ON_COMMAND(ID_POPMENU_RECT_SIZE, &CLab06View::OnPopmenuRectSize)
	ON_COMMAND(ID_POPMENU_ELLP_LOCATION, &CLab06View::OnPopmenuEllpLocation)
	ON_COMMAND(ID_POPMENU_LINE_CHANGESTART, &CLab06View::OnPopmenuLineChangestart)
	ON_COMMAND(ID_POPMENU_LINE_CHANGELENGTH, &CLab06View::OnPopmenuLineChangelength)
	ON_COMMAND(ID_POPMENU_RECT_LOCATION, &CLab06View::OnPopmenuRectLocation)
	ON_COMMAND(ID_LineStyle2, &CLab06View::OnLinestyle2)
	ON_COMMAND(ID_LineStyle3, &CLab06View::OnLinestyle3)
	ON_COMMAND(ID_RECTLINE_1, &CLab06View::OnRectline1)
	ON_COMMAND(ID_RECTLINE_2, &CLab06View::OnRectline2)
	ON_COMMAND(ID_RECTLINE_3, &CLab06View::OnRectline3)
	ON_COMMAND(ID_POPMENU_TEXT_DELETE, &CLab06View::OnPopmenuTextDelete)
	ON_COMMAND(ID_POPMENU_ELLP_DELETE, &CLab06View::OnPopmenuEllpDelete)
	ON_COMMAND(ID_POPMENU_ELLP_COLOR, &CLab06View::OnPopmenuEllpColor)
	ON_COMMAND(ID_POPMENU_ELLP_SIZE, &CLab06View::OnPopmenuEllpSize)
	ON_COMMAND(ID_ELLP_LINE1, &CLab06View::OnEllpLine1)
	ON_COMMAND(ID_ELLP_LINE2, &CLab06View::OnEllpLine2)
	ON_COMMAND(ID_ELLP_LINE3, &CLab06View::OnEllpLine3)
END_MESSAGE_MAP()

// CLab06View 构造/析构

CLab06View::CLab06View() noexcept
{
	// TODO: 在此处添加构造代码
	m_DrawMode = DRAW_MODE_SELECT;

	 m_ColorLine= RGB(0,0,255);
	 m_ColorBrush = RGB(255, 0, 0);
	 m_ColorText = RGB(0, 255, 0);
	 m_bDrawing = false;

	 m_logPen = { PS_SOLID,{1,1}, m_ColorLine };
	 //LOGFONT m_logFont的初始化：
	GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT),
		(PTSTR)&m_logFont);

	m_logBrush = { BS_SOLID,m_ColorBrush,HS_HORIZONTAL };
	m_searchFig = NULL;
	m_searchPos = NULL;
}
CLab06View::~CLab06View()
{
}
BOOL CLab06View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLab06View 绘图

void CLab06View::OnDraw(CDC* pDC)
{
	CLab06Doc* pDoc = GetDocument();
	//新建Doc 类，开始 使用缓冲区管理；
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//将绘制所有的图形；
	//pDC->SetTextColor(RGB(255, 0, 0));
	//for (int i = 0; i < pDoc->m_count; i++)
	//{
	//	pDoc->m_Figs[i]->Draw(pDC);
	//}
	POSITION pos = pDoc-> m_FIGS.GetHeadPosition();
	while (pos != NULL)
	{
		pDoc->m_FIGS.GetNext(pos)->Draw(pDC);	
	}
	pDC->TextOut(120, 80, "Hello, it's MFC Application");

}
void CLab06View::OnRButtonUp(UINT  nFlags , CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);

	POSITION pos = GetDocument()->m_FIGS.GetHeadPosition();
	CMenu PopMenu;PopMenu.LoadMenu(IDR_POPMENU);CMenu* SubMenu;
	for(   ;pos!=  NULL ;  GetDocument()->m_FIGS.GetNext(pos) )
	{
		CFigure* pFig = GetDocument()->m_FIGS.GetAt(pos);
		if (pFig->isContain(point))
		{
			m_searchPos = pos;
			m_searchFig = pFig;
			ClientToScreen(&point);
			switch (m_searchFig->m_type)
			{
			case DRAW_MODE_LINE:
				SubMenu = PopMenu.GetSubMenu(0);
				SubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);
				break;
			case DRAW_MODE_RECT:
				SubMenu = PopMenu.GetSubMenu(1);
				SubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);
				break;
			case DRAW_MODE_TEXT:
				SubMenu = PopMenu.GetSubMenu(2);
				SubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);
				break;
			case DRAW_MODE_ELLIPSE:
				SubMenu = PopMenu.GetSubMenu(3);
				SubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);
				break;
			default:
				break;
			}
			break;
		}
	}
}
void CLab06View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}
// CLab06View 诊断

#ifdef _DEBUG
void CLab06View::AssertValid() const
{
	CView::AssertValid();
}

void CLab06View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab06Doc* CLab06View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab06Doc)));
	return (CLab06Doc*)m_pDocument;
}
#endif //_DEBUG
// CLab06View 消息处理程序
void CLab06View::OnDrawSelect()
{
	m_DrawMode = DRAW_MODE_SELECT;
}
void CLab06View::OnUpdateDrawSelect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_SELECT);
}
void CLab06View::OnDrawLine()
{	
	m_DrawMode = DRAW_MODE_LINE;
}
void CLab06View::OnUpdateDrawLine(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_LINE);//在屏幕上 实际显示选中；
}
void CLab06View::OnDrawRect()
{
	m_DrawMode = DRAW_MODE_RECT;
}
void CLab06View::OnDrawText()
{
	m_DrawMode = DRAW_MODE_TEXT;
}
void CLab06View::OnDrawEllipse()
{
	m_DrawMode = DRAW_MODE_ELLIPSE;
}
void CLab06View::OnUpdateDrawRect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_RECT);
}
void CLab06View::OnUpdateDrawText(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_TEXT);
}
void CLab06View::OnUpdateDrawEllipse(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_ELLIPSE);
}
void CLab06View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	str.Format(_T("%4d,%4d"), point.x, point.y);

	(  (CMainFrame*)AfxGetMainWnd()  )->SetSSMousePos(str);
   //主函数指针
	CView::OnMouseMove(nFlags, point);
}
void CLab06View::OnSettingsBrushcolor()
{
	CColorDialog ob;
	if (ob.DoModal() == IDOK)
	{
		m_ColorBrush= ob.m_cc.rgbResult;		
	}
}
void CLab06View::OnSettingsLinecolor()
{
	CColorDialog ob;
	if (ob.DoModal() == IDOK)
	{		
		this->m_ColorLine = ob.m_cc.rgbResult;
	}
}
void CLab06View::OnSettingsTextcolor()
{
	CFontDialog ob;
	if (ob.DoModal() == IDOK)
	{
		m_ColorText = ob.m_cf.rgbColors;
		m_logFont =  *(ob.m_cf.lpLogFont);
	}
}

void CLab06View::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_DrawMode != DRAW_MODE_SELECT)
	{
		m_ptDown = point;
		m_bDrawing = true;
		SetCapture();//
	}
	CView::OnLButtonDown(nFlags, point);
}
void CLab06View::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_bDrawing)
	{
		m_ptUp = point;
		ReleaseCapture();
		m_bDrawing = false;
		CFigure* pFig = NULL;
		switch (m_DrawMode)
		{
			case  DRAW_MODE_TEXT:
			{
				CDlgText ob;//调出对话框，输入文本信息
				if (ob.DoModal() == IDOK)
				{
					//m_logFont = {  };
					//创建有效的文本框；保持到文档中
					pFig = new CMyText(m_ptDown, ob.m_strInput, m_logFont, m_ColorText);//参数m_point ,m_str				
				}
				break;
			}
			case  DRAW_MODE_LINE:
			{
				m_logPen = { PS_SOLID,{1,1}, m_ColorLine };
				pFig = new CMyLine(m_ptDown, m_ptUp, m_logPen, m_ColorLine);
				break;
			}
			case  DRAW_MODE_RECT:
			{
				LOGPEN  logPen = { PS_SOLID,{1,1}, m_ColorLine };
				m_logBrush = { BS_SOLID,m_ColorBrush,HS_HORIZONTAL };
				pFig = new CMyRect(m_ptDown, m_ptUp, m_logBrush, logPen);
				break;
			}
			case  DRAW_MODE_ELLIPSE:
			{
				LOGPEN  logPen = { PS_SOLID,{1,1}, m_ColorLine };
				m_logBrush = { BS_SOLID,m_ColorBrush,HS_HORIZONTAL };
				pFig = new CMyEllp(m_ptDown, m_ptUp, m_logBrush, logPen);
				break;
			}
		}
		if (pFig != NULL)
		{
//所有的绘图
			GetDocument()->AddOneFigure(pFig);//放入文档中，

			InvalidateRect(NULL);//立即进行重绘	
		}
	}
	CView::OnLButtonUp(nFlags, point);
}
void CLab06View::OnRButtonDown(UINT nFlags, CPoint point)
{
	CView::OnRButtonDown(nFlags, point);
}
void CLab06View::OnPopmenuLineColor()
{
	CColorDialog ob;
	COLORREF change = m_ColorLine ; 

	if (ob.DoModal() == IDOK)
	{
		 change = ob.m_cc.rgbResult;
	}
	((CMyLine*)m_searchFig)->m_logPen.lopnColor = change;
	
	InvalidateRect(NULL);//立即进行重绘	
}
void CLab06View::OnPopmenuEllpColor()
{
	CColorDialog ob;
	COLORREF change = m_ColorBrush;
	if (ob.DoModal() == IDOK)
	{
		change = ob.m_cc.rgbResult;
	}
	((CMyEllp*)m_searchFig)->m_logBrush.lbColor = change;
	InvalidateRect(NULL);//立即进行重绘	
}
void CLab06View::OnPopmenuRectColor()
{
	CColorDialog ob;
	COLORREF change = m_ColorBrush;
	if (ob.DoModal() == IDOK)
	{
		change = ob.m_cc.rgbResult;
	}
	((CMyRect*)m_searchFig)->m_logBrush.lbColor = change;
	InvalidateRect(NULL);//立即进行重绘	
}

void CLab06View::OnLineStyle1()
{
	((CMyLine*)m_searchFig)->m_logPen.lopnStyle = PS_DOT;
	InvalidateRect(NULL);//立即进行重绘		
}
void CLab06View::OnLinestyle2()
{
	((CMyLine*)m_searchFig)->m_logPen.lopnStyle = PS_DASHDOT;
	InvalidateRect(NULL);//立即进行重绘	
}
void CLab06View::OnLinestyle3()
{
	((CMyLine*)m_searchFig)->m_logPen.lopnStyle = PS_SOLID;
	InvalidateRect(NULL);//立即进行重绘	
}
void CLab06View::OnRectline1()
{
	((CMyRect*)m_searchFig)->m_logPen.lopnStyle = PS_DOT;
	InvalidateRect(NULL);//立即进行重绘	
}
void CLab06View::OnRectline2()
{
	((CMyRect*)m_searchFig)->m_logPen.lopnStyle = PS_DASHDOT;
	InvalidateRect(NULL);//立即进行重绘	
	
}
void CLab06View::OnRectline3()
{
	((CMyRect*)m_searchFig)->m_logPen.lopnStyle = PS_SOLID;
	InvalidateRect(NULL);//立即进行重绘	
}
void CLab06View::OnEllpLine1()
{
	((CMyEllp*)m_searchFig)->m_logPen.lopnStyle = PS_DOT;
	InvalidateRect(NULL);//立即进行重绘	
}
void CLab06View::OnEllpLine2()
{
	((CMyEllp*)m_searchFig)->m_logPen.lopnStyle = PS_DASHDOT;
	InvalidateRect(NULL);//立即进行重绘
}
void CLab06View::OnEllpLine3()
{	
	((CMyEllp*)m_searchFig)->m_logPen.lopnStyle = PS_SOLID;
	InvalidateRect(NULL);//立即进行重绘
}


void CLab06View::OnPopmenuTextFont()
{	
	CFontDialog fd;
	if (fd.DoModal() == IDOK)
	{
		m_ColorText = fd.m_cf.rgbColors;
		m_logFont = *(fd.m_cf.lpLogFont);
	}

	((CMyText*)m_searchFig)->m_logFont = m_logFont;
	((CMyText*)m_searchFig)->m_color = m_ColorText;

	InvalidateRect(NULL);//立即进行重绘	
}
void CLab06View::OnPopmenuLineDelete()
{
	 GetDocument()->m_FIGS.RemoveAt(m_searchPos);
	 m_searchPos = NULL;
	 InvalidateRect(NULL);
}
void CLab06View::OnPopmenuRectDelete()
{
	GetDocument()->m_FIGS.RemoveAt(m_searchPos);
	m_searchPos = NULL;
	InvalidateRect(NULL);
}
void CLab06View::OnPopmenuEllpDelete()
{
	GetDocument()->m_FIGS.RemoveAt(m_searchPos);
	m_searchPos = NULL;
	InvalidateRect(NULL);
}
void CLab06View::OnPopmenuTextContent()
{
	CDlgText ob;//调出对话框，输入文本信息
	if (ob.DoModal() == IDOK)
	{
		((CMyText*)m_searchFig)->m_str = ob.m_strInput;
	}
	InvalidateRect(NULL);	
}
void CLab06View::OnPopmenuEllpSize()
{
	CDlgSize ob;//调出对话框，输入文本信息
	if (ob.DoModal() == IDOK)
	{
		POINT ptS = m_searchFig->m_ptS;

		((CMyEllp*)m_searchFig)->m_ptE = { ptS.x + ob.m_wildth,ptS.y + ob.m_len };
	}
	InvalidateRect(NULL);
}

void CLab06View::OnPopmenuRectSize()
{
	CDlgSize ob;//调出对话框，输入文本信息
	if (ob.DoModal() == IDOK)
	{
		POINT ptS = m_searchFig->m_ptS;

		((CMyRect*)m_searchFig)->m_ptE = { ptS.x + ob.m_wildth,ptS.y + ob.m_len };
	}
	InvalidateRect(NULL);
}
void CLab06View::OnPopmenuEllpLocation()
{
	CDlgLocation ob;//调出对话框，输入文本信息
	if (ob.DoModal() == IDOK)
	{
		POINT ptS = ((CMyEllp*)m_searchFig)->m_ptS;
		POINT ptE = ((CMyEllp*)m_searchFig)->m_ptE;
		//计算原来的大小：
		int dx = ptE.x - ptS.x;
		int dy = ptE.y - ptS.y;

		((CMyEllp*)m_searchFig)->m_ptS = { ob.m_locationX,ob.m_locationY };
		((CMyEllp*)m_searchFig)->m_ptE = { ob.m_locationX+dx,ob.m_locationY+dy };

	}
	InvalidateRect(NULL);
}
void CLab06View::OnPopmenuLineChangestart()
{
	CDlgLocation ob;//调出对话框，输入文本信息
	if (ob.DoModal() == IDOK)
	{
		POINT ptS = ((CMyRect*)m_searchFig)->m_ptS;
		POINT ptE = ((CMyRect*)m_searchFig)->m_ptE;
		//计算原来的大小：
		int dx = ptE.x - ptS.x;
		int dy = ptE.y - ptS.y;

		((CMyRect*)m_searchFig)->m_ptS = { ob.m_locationX,ob.m_locationY };
		((CMyRect*)m_searchFig)->m_ptE = { ob.m_locationX + dx,ob.m_locationY + dy };
	}
	InvalidateRect(NULL);	
}
void CLab06View::OnPopmenuLineChangelength()
{
	CDlgGetLength ob;//调出对话框，输入文本信息
	if (ob.DoModal() == IDOK)
	{
		POINT ptS = m_searchFig->m_ptS;
		POINT ptE = m_searchFig->m_ptE;
		double tan,cos, sin;
		if (ptE.x != ptS.x)
		{
			tan = ( (double)ptE.y - ptS.y) / ((double)ptE.x - ptS.x);
			 double te = (1 + tan *tan);
			 cos = 1 / te;
			 sin = tan / te;
		}
		else
		{
			cos = 0;
			sin = 1;
		}
		((CMyRect*)m_searchFig)->m_ptE = { (int)(ptS.x + ob.Length*cos) ,(int)(ptS.y + ob.Length *sin) };
	}
	InvalidateRect(NULL);
}
void CLab06View::OnPopmenuRectLocation()
{
	CDlgLocation ob;//调出对话框，输入文本信息
	if (ob.DoModal() == IDOK)
	{
		POINT ptS = ((CMyRect*)m_searchFig)->m_ptS;
		POINT ptE = ((CMyRect*)m_searchFig)->m_ptE;
		//计算原来的大小：
		int dx = ptE.x - ptS.x;
		int dy = ptE.y - ptS.y;
		((CMyRect*)m_searchFig)->m_ptS = { ob.m_locationX,ob.m_locationY };
		((CMyRect*)m_searchFig)->m_ptE = { ob.m_locationX + dx,ob.m_locationY + dy };

	}
	InvalidateRect(NULL);
}
void CLab06View::OnPopmenuTextDelete()
{
	GetDocument()->m_FIGS.RemoveAt(m_searchPos);
	m_searchPos = NULL;
	InvalidateRect(NULL);
}






