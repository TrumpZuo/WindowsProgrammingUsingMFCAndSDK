
// Lab06Doc.h: CLab06Doc 类的接口
//数据区，数组存储；
#pragma once
class CLab06Doc : public CDocument
{
protected: // 仅从序列化创建
	CLab06Doc() noexcept;
	DECLARE_DYNCREATE(CLab06Doc)
// 特性
public:
	UINT m_count;
	//CFigure *m_Figs[MAX_FIG];

	CList < CFigure*, CFigure* &>  m_FIGS;
// 操作
public:
	BOOL AddOneFigure(CFigure * );
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
	virtual ~CLab06Doc();//没有virtual  可能使用父类的析构函数
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
