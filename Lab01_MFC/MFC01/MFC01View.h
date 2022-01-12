
// MFC01View.h: CMFC01View 类的接口
//

#pragma once


class CMFC01View : public CView
{
protected: // 仅从序列化创建
	CMFC01View() noexcept;
	DECLARE_DYNCREATE(CMFC01View)

// 特性
public:
	CMFC01Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFC01View();
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
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	CString m_randString;
	CRect m_rect;
	bool m_isStart;
	LOGFONT m_logFont;



	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFC01View.cpp 中的调试版本
inline CMFC01Doc* CMFC01View::GetDocument() const
   { return reinterpret_cast<CMFC01Doc*>(m_pDocument); }
#endif

