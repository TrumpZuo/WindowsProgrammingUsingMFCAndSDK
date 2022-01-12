#pragma once
class Goods
{

public:
	CString m_name;
	double m_price;
	int m_count;
	double m_money;
public:

	Goods();
	Goods(CString m_name, double m_price, int m_count);
   // CString	 Draw()
	//virtual void Draw(CDC* pDC) = 0;

    void Save(CArchive&) ;
	BOOL Load(CArchive& ar);
	//virtual BOOL Load(CArchive&) = 0;
	//virtual BOOL isContain(POINT&) = 0;
};

