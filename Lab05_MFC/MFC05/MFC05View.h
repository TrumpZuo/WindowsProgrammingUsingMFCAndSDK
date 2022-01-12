
// MFC05View.h: CMFC05View 类的接口
//

#pragma once


class CMFC05View : public CView
{
protected: // 仅从序列化创建
	CMFC05View() noexcept;
	DECLARE_DYNCREATE(CMFC05View)

// 特性
public:
	CMFC05Doc* GetDocument() const;
	int m_select_mode;

	bool m_isDraw;
	POINT m_startPoint;
	POINT m_endPoint;


	COLORREF m_penColor;
	COLORREF m_brushColor;
	UINT m_penStyle;
	LOGFONT  m_logFont;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFC05View();
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
	afx_msg void OnSelectNull();
	afx_msg void OnSelectLine();
	afx_msg void OnSelectRect();
	afx_msg void OnSelectEllp();
	afx_msg void OnSelectText();
	afx_msg void OnUpdateSelectNull(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectRect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectEllp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectText(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChangeLineColor();
	afx_msg void OnChangeTextAll();
};

#ifndef _DEBUG  // MFC05View.cpp 中的调试版本
inline CMFC05Doc* CMFC05View::GetDocument() const
   { return reinterpret_cast<CMFC05Doc*>(m_pDocument); }
#endif

