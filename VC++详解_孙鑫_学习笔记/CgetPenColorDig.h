#pragma once


// CgetPenColorDig 对话框

class CgetPenColorDig : public CDialogEx
{
	DECLARE_DYNAMIC(CgetPenColorDig)

public:
	CgetPenColorDig(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CgetPenColorDig();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int m_ColorR;
	int m_ColorG;
	int m_ColorB;
};
