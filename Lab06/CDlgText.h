#pragma once


// CDlgText 对话框

class CDlgText : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgText)

public:
	CDlgText(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgText();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEXT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CString m_strInput;


	UINT length;
	UINT wildth;
};
