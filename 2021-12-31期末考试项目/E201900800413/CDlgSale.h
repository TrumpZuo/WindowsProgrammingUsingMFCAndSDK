#pragma once


// CDlgSale 对话框

class CDlgSale : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSale)

public:
	CDlgSale(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgSale();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SALE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	double m_price;
	int m_count;
};
