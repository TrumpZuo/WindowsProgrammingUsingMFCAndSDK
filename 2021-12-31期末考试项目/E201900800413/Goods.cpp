#include "pch.h"
#include "Goods.h"

Goods::Goods()
{
	//this->m_name = NULL;
	this->m_price = 0;
	this->m_count = 0;
	this->m_money = 0 ;


}

Goods::Goods(CString m_name, double m_price, int m_count)
{
	this->m_name = m_name;
	this->m_price = m_price;
	this->m_count = m_count;
	this->m_money = m_price * m_count;

}
 void Goods::Save(CArchive& ar)
{
	 ar << m_name << m_price << m_count <<m_money;
}

 BOOL Goods::Load(CArchive& ar)
 {
	 ar >> m_name >> m_price >> m_count>> m_money;
	 return true;
 }
