#pragma once

#include<Windows.h>

#define DRAW_MODE_SELECT 0
#define DRAW_MODE_LINE   1
#define DRAW_MODE_RECT   2
#define DRAW_MODE_ELLIPSE   3
#define DRAW_MODE_TEXT   4

#define MAX_FIG 32
class CFigure
{
public:
	UINT m_type;
	POINT m_ptS;
	POINT m_ptE;
public:
	virtual void Draw(CDC* pDC) = 0;//子类必须实现
//	virtual ~CFigure();

	virtual void Save(CArchive &)=0;
	virtual BOOL Load(CArchive &)=0;
	virtual BOOL isContain(POINT&) = 0;
};



class CMyLine : public CFigure
{
public:
	LOGPEN m_logPen;
	COLORREF m_color;
public:
	CMyLine();
	CMyLine(POINT& ptS, POINT&  ptE, LOGPEN& logPen, COLORREF& color);
	virtual void Draw(CDC* pDC);
//	virtual ~CMyLine();
	virtual void Save(CArchive & ar);
	virtual BOOL Load(CArchive & ar);
	virtual BOOL isContain(POINT& point);


};


class CMyRect : public CFigure
{
public:
	LOGBRUSH m_logBrush;
	LOGPEN m_logPen;

public:
	CMyRect();
	CMyRect(POINT& ptS, POINT& ptE, LOGBRUSH& logBrush, LOGPEN& m_logPen);
	virtual void Draw(CDC* pDC);
//	virtual ~CMyRect();
	virtual void Save(CArchive& ar);
	virtual BOOL Load(CArchive& ar);
	virtual BOOL isContain(POINT& point);
};

class CMyEllp : public CFigure
{
public:
	LOGBRUSH  m_logBrush;
	LOGPEN m_logPen;
public:
	CMyEllp();
	CMyEllp(POINT& ptS, POINT& ptE, LOGBRUSH& logBrush ,LOGPEN& m_logPen);
	virtual void Draw(CDC* pDC);
//	virtual ~CMyEllp();
	virtual void Save(CArchive& ar);
	virtual BOOL Load(CArchive& ar);
	virtual BOOL isContain(POINT& point);
};

class CMyText :public CFigure
{
public:
	LOGFONT m_logFont;
	COLORREF m_color;
	CString m_str;
	int m_size;

public:
	CMyText();
	CMyText(POINT &pt, CString& str,LOGFONT &logFont ,COLORREF &color);
	virtual void Draw(CDC* pDC);
	virtual void Save(CArchive& ar);
	virtual BOOL Load(CArchive& ar);
	virtual BOOL isContain(POINT& point);
};
