// CDlgText.cpp: 实现文件
//

#include "pch.h"
#include "MFC05.h"
#include "CDlgText.h"
#include "afxdialogex.h"


// CDlgText 对话框

IMPLEMENT_DYNAMIC(CDlgText, CDialogEx)

CDlgText::CDlgText(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEXT_INPUT, pParent)
	, m_textString(_T(""))
{

}

CDlgText::~CDlgText()
{
}

void CDlgText::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_textString);
}


BEGIN_MESSAGE_MAP(CDlgText, CDialogEx)
END_MESSAGE_MAP()


// CDlgText 消息处理程序
