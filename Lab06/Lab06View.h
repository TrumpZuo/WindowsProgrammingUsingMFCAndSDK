
// Lab06View.h: CLab06View 类的接口
//

#pragma once


class CLab06View : public CView
{
protected: // 仅从序列化创建
	CLab06View() noexcept;
	DECLARE_DYNCREATE(CLab06View)

// 特性
public:
	CLab06Doc* GetDocument() const;

private:
	UINT m_DrawMode;	//设置绘图状态：

	COLORREF m_ColorLine;
	COLORREF m_ColorBrush;
	COLORREF m_ColorText;  //在屏幕上 选择出的类；

	LOGPEN m_logPen;//绘制线使用
	LOGFONT m_logFont;
	LOGBRUSH m_logBrush;//绘制矩形使用

	POINT m_ptDown;
	POINT m_ptUp;
	BOOL  m_bDrawing;

	CFigure* m_searchFig ;
	POSITION m_searchPos;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CLab06View();
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
	afx_msg void OnDrawSelect();
	afx_msg void OnUpdateDrawSelect(CCmdUI* pCmdUI);
	afx_msg void OnDrawLine();
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnDrawRect();
	afx_msg void OnDrawText();
	afx_msg void OnDrawEllipse();
	afx_msg void OnUpdateDrawRect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawText(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawEllipse(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSettingsBrushcolor();
	afx_msg void OnSettingsLinecolor();
	afx_msg void OnSettingsTextcolor();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPopmenuLineColor();
	afx_msg void OnLineStyle1();
	afx_msg void OnPopmenuRectColor();
	afx_msg void OnPopmenuTextFont();
	afx_msg void OnPopmenuLineDelete();
	afx_msg void OnPopmenuRectDelete();
	afx_msg void OnPopmenuTextContent();
	afx_msg void OnPopmenuRectSize();
	afx_msg void OnPopmenuEllpLocation();
	afx_msg void OnPopmenuLineChangestart();
	afx_msg void OnPopmenuLineChangelength();
	afx_msg void OnPopmenuRectLocation();
	afx_msg void OnLinestyle2();
	afx_msg void OnLinestyle3();
	afx_msg void OnRectline1();
	afx_msg void OnRectline2();
	afx_msg void OnRectline3();
	afx_msg void OnPopmenuTextDelete();
	afx_msg void OnPopmenuEllpDelete();
	afx_msg void OnPopmenuEllpColor();
	afx_msg void OnPopmenuEllpSize();
	afx_msg void OnEllpLine1();
	afx_msg void OnEllpLine2();
	afx_msg void OnEllpLine3();
};

#ifndef _DEBUG  // Lab06View.cpp 中的调试版本
inline CLab06Doc* CLab06View::GetDocument() const
   { return reinterpret_cast<CLab06Doc*>(m_pDocument); }
#endif

