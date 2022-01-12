 
// MFC_practiceView.h: CMFCpracticeView 类的接口
//

#pragma once


class CMFCpracticeView : public CView
{
protected: // 仅从序列化创建
	CMFCpracticeView() noexcept;
	DECLARE_DYNCREATE(CMFCpracticeView)

// 特性
public:
	CMFCpracticeDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCpracticeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	// 右键点击
	CPoint m_ptOld;
	CPoint m_ptOrgin;
	BOOL m_bDraw ;
	UINT m_con;

	COLORREF   m_penColor ;

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPopmenu_02_show();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTestmymenuTest01();
	afx_msg void OnUpdateTestmymenuTest01(CCmdUI* pCmdUI);
	afx_msg void OnTestmymenuTest02();
	afx_msg void OnUpdateTestmymenuTest02(CCmdUI* pCmdUI);
	afx_msg void OnTestmymenuTestdig();
};

#ifndef _DEBUG  // MFC_practiceView.cpp 中的调试版本
inline CMFCpracticeDoc* CMFCpracticeView::GetDocument() const
   { return reinterpret_cast<CMFCpracticeDoc*>(m_pDocument); }
#endif

