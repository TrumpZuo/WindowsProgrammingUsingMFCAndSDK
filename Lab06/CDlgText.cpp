// CDlgText.cpp: 实现文件
//

#include "pch.h"
#include "Lab06.h"
#include "CDlgText.h"
#include "afxdialogex.h"


// CDlgText 对话框

IMPLEMENT_DYNAMIC(CDlgText, CDialogEx)

CDlgText::CDlgText(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEXT, pParent)
	, m_strInput(_T(""))
	, length(0)
	, wildth(0)
{

}

CDlgText::~CDlgText()
{
}

void CDlgText::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strInput);

}


BEGIN_MESSAGE_MAP(CDlgText, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgText::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDlgText 消息处理程序


void CDlgText::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
