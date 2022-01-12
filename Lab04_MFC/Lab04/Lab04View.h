
// Lab04View.h: CLab04View 类的接口
//

#pragma once


class CLab04View : public CView
{
protected: // 仅从序列化创建
	CLab04View() noexcept;
	DECLARE_DYNCREATE(CLab04View)

// 特性
public:
	CLab04Doc* GetDocument() const;

	COLORREF m_bk;
	COLORREF m_color;
	CRect m_rect;
	CString m_str;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CLab04View();
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
	afx_msg void OnChangeTextColor();
	afx_msg void OnChangeBackColor();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLab0432773();
	afx_msg void OnChangeText();
	afx_msg void OnChangeBack();
};

#ifndef _DEBUG  // Lab04View.cpp 中的调试版本
inline CLab04Doc* CLab04View::GetDocument() const
   { return reinterpret_cast<CLab04Doc*>(m_pDocument); }
#endif

