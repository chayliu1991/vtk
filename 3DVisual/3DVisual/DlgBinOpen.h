#pragma once
#include "afxcmn.h"


// CDlgBinOpen 对话框

class CDlgBinOpen : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBinOpen)

public:
	CDlgBinOpen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBinOpen();

// 对话框数据
	enum { IDD = IDD_BINIMPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
