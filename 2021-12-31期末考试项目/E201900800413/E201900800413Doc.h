
// E201900800413Doc.h: CE201900800413Doc 类的接口
//


#pragma once
#include "Goods.h"


class CE201900800413Doc : public CDocument
{
protected: // 仅从序列化创建
	CE201900800413Doc() noexcept;
	DECLARE_DYNCREATE(CE201900800413Doc)

// 特性
public:
	CList < Goods*, Goods*&>  m_goods;
	BOOL  AddOneGood(Goods * newGood);
	 void clearBuffer();
// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CE201900800413Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
