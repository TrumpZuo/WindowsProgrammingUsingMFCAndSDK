
// MFCextraView.h: CMFCextraView 类的接口
//

#pragma once


class CMFCextraView : public CView
{
protected: // 仅从序列化创建
	CMFCextraView() noexcept;
	DECLARE_DYNCREATE(CMFCextraView)

// 特性
public:
	CMFCextraDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFCextraView();
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
};

#ifndef _DEBUG  // MFCextraView.cpp 中的调试版本
inline CMFCextraDoc* CMFCextraView::GetDocument() const
   { return reinterpret_cast<CMFCextraDoc*>(m_pDocument); }
#endif

