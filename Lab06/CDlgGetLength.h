#pragma once


// CDlgGetLength 对话框

class CDlgGetLength : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGetLength)

public:
	CDlgGetLength(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgGetLength();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GETLENGTH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int Length;
};
