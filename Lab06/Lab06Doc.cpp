
// Lab06Doc.cpp: CLab06Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Lab06.h"
#endif

#include "Lab06Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLab06Doc

IMPLEMENT_DYNCREATE(CLab06Doc, CDocument)

BEGIN_MESSAGE_MAP(CLab06Doc, CDocument)
END_MESSAGE_MAP()


// CLab06Doc 构造/析构

CLab06Doc::CLab06Doc() noexcept
{

}

CLab06Doc::~CLab06Doc()
{
	POSITION pos = m_FIGS.GetHeadPosition();
		while (pos != NULL)
		{
			delete  m_FIGS.GetNext(pos);
		}
		m_FIGS.RemoveAll();
}

//新建文档时，将原有的图元信息全部清空
BOOL CLab06Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	POSITION pos = m_FIGS.GetHeadPosition();
	while (pos != NULL)
	{
		delete  m_FIGS.GetNext(pos);
	}
	m_FIGS.RemoveAll();
	return TRUE;
}
// CLab06Doc 序列化, 保存文件
void CLab06Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	
		//存储图像 代码：
		UINT uCount = m_FIGS.GetCount();//CList 类型
		ar << uCount;
		POSITION pos = m_FIGS.GetHeadPosition();
		while(  pos!= NULL)
		{
			CFigure* pFig = m_FIGS.GetNext(pos);
			ar << pFig->m_type;
			pFig->Save(ar);
		}
	}
	else
	{
		//加载新图像之前，应该首先清除目前显示的 图像；
		POSITION pos = m_FIGS.GetHeadPosition();
		while (pos != NULL)
		{
			delete  m_FIGS.GetNext(pos);
		}
		m_FIGS.RemoveAll();

		//加载 图像 代码
		UINT uCount = 0;
		ar >> uCount;
		for (int i = 0; i < uCount; i++)
		{
			UINT uType = 0;
			ar >> uType;
			CFigure* pFig = NULL;

			switch (uType)
			{
			case DRAW_MODE_LINE:pFig = new CMyLine();
				break;
			case DRAW_MODE_RECT:pFig = new CMyRect();
				break;
			case DRAW_MODE_ELLIPSE:pFig = new CMyEllp();
				break;
			case DRAW_MODE_TEXT:pFig = new CMyText();
				break;
			}
			if (pFig)
			{
				pFig->Load(ar);
				AddOneFigure(pFig);
				//m_FIGS.AddTail(pFig);
			}

		}
		
	}
}



#ifdef SHARED_HANDLERS

// 缩略图的支持
void CLab06Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CLab06Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CLab06Doc::SetSearchContent(const CString& value)
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
// CLab06Doc 诊断
#ifdef _DEBUG
void CLab06Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLab06Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

//缓冲区建设：
BOOL CLab06Doc::AddOneFigure(CFigure* pFlg)
{
	m_FIGS.AddTail(pFlg);
	SetModifiedFlag();//此函数用来表明用户是否修改了属性页面,确认弹窗
	return true;

}
// CLab06Doc 命令
