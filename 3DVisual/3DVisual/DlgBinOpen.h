#pragma once
#include "afxcmn.h"


// CDlgBinOpen �Ի���

class CDlgBinOpen : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBinOpen)

public:
	CDlgBinOpen(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBinOpen();

// �Ի�������
	enum { IDD = IDD_BINIMPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	CListCtrl m_BinStackList;
	CString m_BinFolderName;
	int m_BinWidth;
	int m_BinHeight;
	int m_binStartNum;
	int m_binEndNum;
	float m_fBinsample;
	float m_fbinSpaceX;
	float m_fbinSpaceY;
	float m_fbinSpaceZ;


	afx_msg void OnBnClickedBtnbinopen();
};
