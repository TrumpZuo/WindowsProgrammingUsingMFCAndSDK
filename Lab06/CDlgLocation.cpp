// CDlgLocation.cpp: 实现文件
//

#include "pch.h"
#include "Lab06.h"
#include "CDlgLocation.h"
#include "afxdialogex.h"


// CDlgLocation 对话框

IMPLEMENT_DYNAMIC(CDlgLocation, CDialogEx)

CDlgLocation::CDlgLocation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOCATION, pParent)
	, m_locationX(0)
	, m_locationY(0)
{

}

CDlgLocation::~CDlgLocation()
{
}

void CDlgLocation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOC_X, m_locationX);
	DDX_Text(pDX, IDC_EDIT_LOC_Y, m_locationY);
}
BEGIN_MESSAGE_MAP(CDlgLocation, CDialogEx)
END_MESSAGE_MAP()


// CDlgLocation 消息处理程序
