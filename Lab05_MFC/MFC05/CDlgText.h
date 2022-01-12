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
	enum { IDD = IDD_DIALOG_TEXT_INPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_textString;
};
