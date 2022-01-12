
// MFC03View.h: CMFC03View 类的接口
//

#pragma once
#define ROW_NUM 8    //行数
#define COL_NUM 3    //列数

class CMFC03View : public CView
{
protected: // 仅从序列化创建
	CMFC03View() noexcept;
	DECLARE_DYNCREATE(CMFC03View)

// 特性
public:
	CMFC03Doc* GetDocument() const;
	 TCHAR  ButtonName[27][2];
	 CString m_szBuffer;
	 CString m_time;
	 RECT m_rect;


	 WNDCLASS    wcChild;
	 WORD nChildWin_ID;                 //被命中的子窗口标识
	 int  nRow, nCol;                   //被命中的子窗口位置（即行列号）
	 HWND hChildWnd[COL_NUM][ROW_NUM];  //子窗口句柄

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFC03View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnChangeCursor1();
	afx_msg void OnChangeCursor2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MFC03View.cpp 中的调试版本
inline CMFC03Doc* CMFC03View::GetDocument() const
   { return reinterpret_cast<CMFC03Doc*>(m_pDocument); }
#endif

