// CgetPenColorDig.cpp: 实现文件
//

#include "pch.h"
#include "MFC_practice.h"
#include "CgetPenColorDig.h"
#include "afxdialogex.h"
#include"resource.h"

// CgetPenColorDig 对话框

IMPLEMENT_DYNAMIC(CgetPenColorDig, CDialogEx)

CgetPenColorDig::CgetPenColorDig(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_ColorR(0)
	, m_ColorG(0)
	, m_ColorB(0)
{

}

CgetPenColorDig::~CgetPenColorDig()
{
}

void CgetPenColorDig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_R, m_ColorR);
	DDX_Text(pDX, IDC_EDIT_G, m_ColorG);
	DDX_Text(pDX, IDC_EDIT_B, m_ColorB);
}


BEGIN_MESSAGE_MAP(CgetPenColorDig, CDialogEx)
	ON_BN_CLICKED(IDOK, &CgetPenColorDig::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CgetPenColorDig::OnBnClickedCancel)
END_MESSAGE_MAP()


// CgetPenColorDig 消息处理程序


void CgetPenColorDig::OnBnClickedOk()
{
	UpdateData();
	CString str;
	str.Format(L"Change the color of pen to R:%d,G:%d,B:%d", m_ColorR, m_ColorG, m_ColorB);
	MessageBox(str);

	UpdateData(false);
	CDialogEx::OnOK();
}


void CgetPenColorDig::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
