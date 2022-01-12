
#pragma once
#include"pch.h"
#include "draw.h"
#include "framework.h"


CFigure:: ~CFigure()
{
}


CMyLine::CMyLine(POINT& ptS, POINT& ptE, LOGPEN& logPen)
{
	m_type = SELECT_LINE;
	m_ptS = ptS;
	m_ptE = ptE;
	m_logPen = logPen;

}
CMyLine::CMyLine()
{
	m_type = SELECT_LINE;
}
CMyLine::~CMyLine()
{


}

//ʹ�������������ʵ���Ĵ�����
void CMyLine::Draw(CDC* pDC)
{
	CPen pen;
	CPen* pPenOld;
	pen.CreatePenIndirect(&m_logPen);
	pPenOld = pDC->SelectObject(&pen);
	pDC->MoveTo(m_ptS);
	pDC->LineTo(m_ptE);
	pDC->SelectObject(pPenOld);
}

//�� δ ��������� m_type,����������� �ж�����
void CMyLine::Save(CArchive& ar)
{
	ar << m_ptS << m_ptE;
	ar.Write(&m_logPen, sizeof(LOGPEN));
}
BOOL CMyLine::Load(CArchive& ar)
{
	ar >> m_ptS >> m_ptE;
	ar.Read(&m_logPen, sizeof(LOGPEN));
	return true;
}
BOOL CMyLine::isContain(POINT& point)
{
	BOOL isIn = false;
	double k1 = ((double)m_ptS.y - (double)m_ptE.y) / ((double)m_ptS.x - (double)m_ptE.x);
	double k2 = ((double)m_ptS.y - (double)point.y) / ((double)m_ptS.x - (double)point.x);

	double ans1 = fabs(k1 - k2);
	if (ans1 < 0.05)
	{
		isIn = true;
	}
	return isIn;

}

CMyRect::CMyRect(POINT& ptS, POINT& ptE, LOGBRUSH& logBrush, LOGPEN& logPen)
{
	m_type =SELECT_RECT;
	m_ptS = ptS;
	m_ptE = ptE;
	m_logBrush = logBrush;
	m_logPen = logPen;
}
CMyRect::CMyRect()
{
	m_type = SELECT_RECT;
}
CMyRect::~CMyRect()
{



}

void CMyRect::Draw(CDC* pDC)
{

	CPen pen; CPen* pPenOld;
	pen.CreatePenIndirect(&m_logPen);
	pPenOld = pDC->SelectObject(&pen);

	CBrush hBr; CBrush* hBrOld;
	hBr.CreateBrushIndirect(&m_logBrush);
	hBrOld = pDC->SelectObject(&hBr);

	pDC->Rectangle(m_ptS.x, m_ptS.y, m_ptE.x, m_ptE.y);

	pDC->SelectObject(hBrOld);
	pDC->SelectObject(pPenOld);
}
void CMyRect::Save(CArchive& ar)
{
	ar << m_ptS << m_ptE;
	ar.Write(&m_logBrush, sizeof(LOGBRUSH));
	ar.Write(&m_logPen, sizeof(LOGPEN));
}
BOOL CMyRect::Load(CArchive& ar)
{
	ar >> m_ptS >> m_ptE;
	ar.Read(&m_logBrush, sizeof(LOGBRUSH));
	ar.Read(&m_logPen, sizeof(LOGPEN));

	return true;
}
BOOL CMyRect::isContain(POINT& point)
{
	BOOL isIn = false;
	if (m_ptS.x < point.x && point.x < m_ptE.x
		&& m_ptS.y < point.y && point.y < m_ptE.y)
	{
		isIn = true;
	}
	return isIn;
}




CMyEllp::CMyEllp(POINT& ptS, POINT& ptE, LOGBRUSH& logBrush, LOGPEN& logPen)
{
	m_type = SELECT_ELLP;
	m_ptS = ptS;
	m_ptE = ptE;
	m_logBrush = logBrush;
	m_logPen = logPen;
}
CMyEllp::CMyEllp()
{
	m_type = SELECT_ELLP;
}
CMyEllp::~CMyEllp()
{



}
void CMyEllp::Draw(CDC* pDC)
{
	CPen pen; CPen* pPenOld;
	pen.CreatePenIndirect(&m_logPen);
	pPenOld = pDC->SelectObject(&pen);

	CBrush hBr; CBrush* hBrOld;
	hBr.CreateBrushIndirect(&m_logBrush);
	hBrOld = pDC->SelectObject(&hBr);

	pDC->Ellipse(m_ptS.x, m_ptS.y, m_ptE.x, m_ptE.y);
	pDC->SelectObject(hBrOld);
	pDC->SelectObject(pPenOld);
}

void CMyEllp::Save(CArchive& ar)
{
	ar << m_ptS << m_ptE;
	ar.Write(&m_logBrush, sizeof(LOGBRUSH));
}
BOOL CMyEllp::Load(CArchive& ar)
{
	ar >> m_ptS >> m_ptE;
	ar.Read(&m_logBrush, sizeof(LOGBRUSH));
	return true;
}
BOOL CMyEllp::isContain(POINT& point)
{
	BOOL isIn = false;
	if (m_ptS.x < point.x && point.x < m_ptE.x
		&& m_ptS.y < point.y && point.y < m_ptE.y)
	{
		isIn = true;
	}
	return isIn;
}



//���캯��

//CMyText::CMyText(POINT &pt, CString &str, LOGFONT &logFont, COLORREF color)
CMyText::CMyText(POINT& pt, CString& str, LOGFONT& logFont, COLORREF& color)
{
	m_type = SELECT_TEXT;
	m_ptS = pt;
	m_str = str;
	m_logFont = logFont;
	m_color = color;
	m_ptE = { m_ptS.x + 20 * str.GetLength(), m_ptS.y + 25 };
}
CMyText::CMyText()
{
	m_type = SELECT_TEXT;
}

CMyText::~CMyText()
{



}
void CMyText::Draw(CDC* pDC)
{
	//���������� CDC��ʹ��CDC�ķ�������ǰ������� ��������ͬ��ɻ��ƣ�
	CFont font;
	//font.CreateFont(100, _T("����ϸ��"), RGB(255, 0, 0)); //��������1�������С��2�������ͣ�3������ɫ
	font.CreateFontIndirect(&m_logFont);
	pDC->SelectObject(&font);
	pDC->SetTextColor(m_color);
	pDC->TextOut(m_ptS.x, m_ptS.y, m_str);
	//ѡ�����壺
}
void CMyText::Save(CArchive& ar)
{
	ar << m_ptS << m_ptE << m_str;
	ar.Write(&m_logFont, sizeof(LOGFONT));
	ar.Write(&m_color, sizeof(COLORREF));
}
BOOL CMyText::Load(CArchive& ar)
{
	ar >> m_ptS >> m_ptE >> m_str;
	ar.Read(&m_logFont, sizeof(LOGFONT));
	ar.Read(&m_color, sizeof(COLORREF));

	return true;
}
BOOL CMyText::isContain(POINT& point)
{
	BOOL isIn = false;
	if (m_ptS.x < point.x && point.x < m_ptE.x
		&& m_ptS.y < point.y && point.y < m_ptE.y)
	{
		isIn = true;
	}
	return isIn;
}