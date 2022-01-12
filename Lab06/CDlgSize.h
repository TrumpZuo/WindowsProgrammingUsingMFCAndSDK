#pragma once


// CDlgSize 对话框

class CDlgSize : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSize)

public:
	CDlgSize(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgSize();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_len;
	int  m_wildth;
};
