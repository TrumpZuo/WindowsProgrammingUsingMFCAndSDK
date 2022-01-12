
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "MFC_practice.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_TESTMYMENU_TEST01, &CMainFrame::OnTestmymenuTest01)
	ON_COMMAND(ID_TESTMYMENU_TEST02, &CMainFrame::OnTestmymenuTest02)
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()



//状态栏 指示器：
static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	IDS_TIMER,
	IDS_PROGRESS,
	//ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	   //创建工具栏 对象
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		//加载工具栏资源
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)
		)
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}


	if (!m_MyToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		//加载工具栏资源
		!m_MyToolBar.LoadToolBar(IDR_MYTOOLBAR)
		)
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_MyToolBar.EnableDocking(CBRS_ALIGN_ANY);//停靠于任何位置；


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);


	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_MyToolBar);

	
	//(*m_topMenu).LoadMenuW(IDR_MAINFRAME);
	m_topMenu = GetMenu();
	m_topMenu->GetSubMenu(4)->CheckMenuItem(1, MF_BYPOSITION |MF_CHECKED);
	m_topMenu->GetSubMenu(4)->CheckMenuItem(0, MF_BYPOSITION |MF_UNCHECKED);


	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);
	SetClassLong(m_hWnd, GCL_HICON, (long)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON)) );


	/*CString str;
	str.Format(L"x=%d y=%d", GetSystemMetrics(SM_CXMENUCHECK), GetSystemMetrics(SM_CYMENUCHECK));
	MessageBox(str);*/
	//CBitmap bitmap_zuo;
	//bitmap_zuo.LoadBitmap(IDB_BITMAP1);
	//m_topMenu->GetSubMenu(4)->SetMenuItemBitmaps(0, MF_BYPOSITION, &bitmap_zuo, &bitmap_zuo);
	
	SetTimer(1, 1000, NULL);//1为定时器的ID
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.cx = 800;
	cs.cy = 900;

	cs.style = WS_OVERLAPPEDWINDOW;//修改窗口 标题，首先修改窗口类型；
	cs.lpszName = L"201900800413_左长盛";
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnTestmymenuTest01()
{
	
	//m_topMenu = GetMenu();
	//m_topMenu->GetSubMenu(4)->CheckMenuItem(0, MF_BYPOSITION | MF_CHECKED);
	//m_topMenu->GetSubMenu(4)->CheckMenuItem(1, MF_BYPOSITION | MF_UNCHECKED);
}


void CMainFrame::OnTestmymenuTest02()
{
	//m_topMenu = GetMenu();
	//m_topMenu->GetSubMenu(4)->CheckMenuItem(0, MF_BYPOSITION | MF_UNCHECKED);
	//m_topMenu->GetSubMenu(4)->CheckMenuItem(1, MF_BYPOSITION | MF_CHECKED);
}


void CMainFrame::OnRButtonDown(UINT nFlags, CPoint point)
{


}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	CTime t = CTime::GetCurrentTime();
	CString str = t.Format("%H:%M:%S");


	CClientDC dc(this);
	CSize sz = dc.GetTextExtent(str);
	m_wndStatusBar.SetPaneInfo(1, IDS_TIMER, SBPS_NORMAL, sz.cx+8);

	m_wndStatusBar.SetPaneText(1, str);


	CFrameWnd::OnTimer(nIDEvent);
}
