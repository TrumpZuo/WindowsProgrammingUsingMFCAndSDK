#pragma once


// CDlgLocation 对话框

class CDlgLocation : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLocation)

public:
	CDlgLocation(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgLocation();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOCATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_locationX;
	int m_locationY;
};
