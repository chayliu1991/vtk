#pragma once


// CDlgTemplate �Ի���

class CDlgTemplate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTemplate)

public:
	CDlgTemplate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTemplate();

// �Ի�������
	enum { IDD = IDD_DLG_TEMPLATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_GaussTemplate;
	float m_GaussSd;
	virtual BOOL OnInitDialog();
	int m_InteraNum;
	double m_DiffThread;
	int m_BinaryValue;
};
