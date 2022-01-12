// CDlgSize.cpp: 实现文件
//

#include "pch.h"
#include "Lab06.h"
#include "CDlgSize.h"
#include "afxdialogex.h"


// CDlgSize 对话框

IMPLEMENT_DYNAMIC(CDlgSize, CDialogEx)

CDlgSize::CDlgSize(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SIZE, pParent)
	, m_len(0)
	, m_wildth(0)
{

}
CDlgSize::~CDlgSize()
{
}
void CDlgSize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITY, m_len);
	DDX_Text(pDX, IDC_EDITX, m_wildth);
}
BEGIN_MESSAGE_MAP(CDlgSize, CDialogEx)
END_MESSAGE_MAP()


// CDlgSize 消息处理程序
