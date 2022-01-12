
// MFC05Doc.cpp: CMFC05Doc 类的实现
//

#include "pch.h"
#include"draw.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC05.h"
#endif

#include "MFC05Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFC05Doc

IMPLEMENT_DYNCREATE(CMFC05Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFC05Doc, CDocument)
END_MESSAGE_MAP()


// CMFC05Doc 构造/析构

CMFC05Doc::CMFC05Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	CList <CFigure*>  m_allFigure ;

}

CMFC05Doc::~CMFC05Doc()
{
	POSITION pos = m_allFigure.GetHeadPosition();
	while (pos != NULL)
	{
		delete  m_allFigure.GetNext(pos);
	}
	m_allFigure.RemoveAll();
}

BOOL CMFC05Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	clearBuffer();

	return TRUE;
}

// CMFC05Doc 序列化
void CMFC05Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		POSITION pos = m_allFigure.GetHeadPosition();

		UINT cntFigure = m_allFigure.GetCount();
		ar << cntFigure;//保存 图形的总数；

		while (pos != NULL)
		{
			CFigure* saveFigure = m_allFigure.GetAt(pos);//  Next(pos);
			ar << saveFigure->m_type;
			saveFigure->Save(ar);
			m_allFigure.GetNext(pos);
		}	
	}
	else
	{
		clearBuffer();
		UINT cntFigure ;
		ar >> cntFigure;//保存 图形的总数；	
		for(int i=0;i<cntFigure ;i++)
		{
			CFigure* loadFigure = NULL;
			UINT  type;ar >> type;
			switch (type)
			{
			case SELECT_LINE:
				loadFigure = new CMyLine();
				break;
			case SELECT_RECT:
				loadFigure = new CMyRect();
				break;
			case SELECT_ELLP:
				loadFigure = new CMyEllp();
				break;
			case SELECT_TEXT:
				loadFigure = new CMyText();
				break;
			default:
				break;
			}
			if (loadFigure != NULL)
			{
				loadFigure->Load(ar);
				m_allFigure.AddTail(loadFigure);
			}

		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMFC05Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMFC05Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMFC05Doc::SetSearchContent(const CString& value)
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
// CMFC05Doc 诊断
#ifdef _DEBUG
void CMFC05Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFC05Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
// CMFC05Doc 命令

BOOL CMFC05Doc::addNewFigure(CFigure *newFigure)
{
	m_allFigure.AddTail(newFigure);
	return true;
}

void CMFC05Doc::clearBuffer()
{
	POSITION pos = m_allFigure.GetHeadPosition();
	while (pos != NULL)
	{
		delete  m_allFigure.GetNext(pos);
	}
	m_allFigure.RemoveAll();

}