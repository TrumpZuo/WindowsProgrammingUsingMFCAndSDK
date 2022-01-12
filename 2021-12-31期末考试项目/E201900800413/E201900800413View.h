
// E201900800413View.h: CE201900800413View 类的接口
//

#pragma once


class CE201900800413View : public CView
{
protected: // 仅从序列化创建
	CE201900800413View() noexcept;
	DECLARE_DYNCREATE(CE201900800413View)

// 特性
public:
	CE201900800413Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	int row;


protected:

// 实现
public:
	virtual ~CE201900800413View();
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
	afx_msg void OnDataInput();
	afx_msg void OnLast();
};

#ifndef _DEBUG  // E201900800413View.cpp 中的调试版本
inline CE201900800413Doc* CE201900800413View::GetDocument() const
   { return reinterpret_cast<CE201900800413Doc*>(m_pDocument); }
#endif

