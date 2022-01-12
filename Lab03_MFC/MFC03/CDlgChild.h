#pragma once


// CDlgChild 对话框

class CDlgChild : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChild)

public:
	CDlgChild(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgChild();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHILDWIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton OnClick;
};
