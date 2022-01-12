
// E201900800413Doc.cpp: CE201900800413Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "E201900800413.h"
#endif

#include "E201900800413Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CE201900800413Doc

IMPLEMENT_DYNCREATE(CE201900800413Doc, CDocument)

BEGIN_MESSAGE_MAP(CE201900800413Doc, CDocument)
END_MESSAGE_MAP()


// CE201900800413Doc 构造/析构

CE201900800413Doc::CE201900800413Doc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CE201900800413Doc::~CE201900800413Doc()
{
}

BOOL CE201900800413Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}
BOOL  CE201900800413Doc::AddOneGood(Goods* newGood)
{
	m_goods.AddTail(newGood);
	return true;
}
void CE201900800413Doc::clearBuffer()
{
	POSITION pos = m_goods.GetHeadPosition();
	while (pos != NULL)
	{
		delete  m_goods.GetNext(pos);
	}
	m_goods.RemoveAll();

}


// CE201900800413Doc 序列化

void CE201900800413Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		POSITION pos = m_goods.GetHeadPosition();
		UINT cntFigure = m_goods.GetCount();
		ar << cntFigure;


		while (pos != NULL)
		{
			Goods* saveGood = m_goods.GetAt(pos);//  Next(pos);
			//ar << saveGood->m_type;
			saveGood->Save(ar);
			m_goods.GetNext(pos);
		}
	}
	else
	{
		clearBuffer();
		UINT cntFigure;
		ar >> cntFigure;//保存 图形的总数；	
		for (int i = 0; i < cntFigure; i++)
		{		
			CString m_name; double m_price; int m_count; double m_money;
			ar >> m_name >> m_price >> m_count>> m_money;
			Goods* Figure = new Goods(m_name,  m_price,  m_count);
			m_goods.AddTail(Figure);
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CE201900800413Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CE201900800413Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CE201900800413Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CE201900800413Doc 诊断

#ifdef _DEBUG
void CE201900800413Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CE201900800413Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CE201900800413Doc 命令
