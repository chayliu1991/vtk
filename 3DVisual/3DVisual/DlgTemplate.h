#pragma once


// CDlgTemplate 对话框

class CDlgTemplate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTemplate)

public:
	CDlgTemplate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTemplate();

// 对话框数据
	enum { IDD = IDD_DLG_TEMPLATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_GaussTemplate;
	float m_GaussSd;
	virtual BOOL OnInitDialog();
	int m_InteraNum;
	double m_DiffThread;
	int m_BinaryValue;
};
