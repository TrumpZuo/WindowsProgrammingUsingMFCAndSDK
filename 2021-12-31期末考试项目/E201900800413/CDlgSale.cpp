// CDlgSale.cpp: 实现文件
//

#include "pch.h"
#include "E201900800413.h"
#include "CDlgSale.h"
#include "afxdialogex.h"


// CDlgSale 对话框

IMPLEMENT_DYNAMIC(CDlgSale, CDialogEx)

CDlgSale::CDlgSale(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SALE, pParent)
	, m_name(_T(""))
	, m_price(0)
	, m_count(0)
{

}

CDlgSale::~CDlgSale()
{
}

void CDlgSale::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_price);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_count);
}


BEGIN_MESSAGE_MAP(CDlgSale, CDialogEx)
END_MESSAGE_MAP()


// CDlgSale 消息处理程序
