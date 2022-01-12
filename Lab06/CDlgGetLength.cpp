// CDlgGetLength.cpp: 实现文件
//

#include "pch.h"
#include "Lab06.h"
#include "CDlgGetLength.h"
#include "afxdialogex.h"


// CDlgGetLength 对话框

IMPLEMENT_DYNAMIC(CDlgGetLength, CDialogEx)

CDlgGetLength::CDlgGetLength(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GETLENGTH, pParent)
	, Length(0)
{

}

CDlgGetLength::~CDlgGetLength()
{
}

void CDlgGetLength::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GETLEN, Length);
}


BEGIN_MESSAGE_MAP(CDlgGetLength, CDialogEx)
END_MESSAGE_MAP()


// CDlgGetLength 消息处理程序
