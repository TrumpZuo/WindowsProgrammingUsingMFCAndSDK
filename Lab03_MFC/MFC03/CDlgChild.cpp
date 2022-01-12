// CDlgChild.cpp: 实现文件
//

#include "pch.h"
#include "MFC03.h"
#include "CDlgChild.h"
#include "afxdialogex.h"


// CDlgChild 对话框

IMPLEMENT_DYNAMIC(CDlgChild, CDialogEx)

CDlgChild::CDlgChild(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHILDWIN, pParent)
{

}

CDlgChild::~CDlgChild()
{
}

void CDlgChild::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, OnClick);
}


BEGIN_MESSAGE_MAP(CDlgChild, CDialogEx)
END_MESSAGE_MAP()


// CDlgChild 消息处理程序
