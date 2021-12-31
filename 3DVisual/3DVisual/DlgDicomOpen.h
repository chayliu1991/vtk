#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "btnst.h"

// CDlgDicomOpen �Ի���

class CDlgDicomOpen : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDicomOpen)

public:
	CDlgDicomOpen(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDicomOpen();

// �Ի�������
	enum { IDD = IDD_DICOMIMPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_DicomStackList;
	CString m_DicomFolderName;	
	afx_msg void OnBnClickedBtndicomopen();
	CButtonST m_DocOpenBtn,m_DocYesBtn,m_DocNoBtn;	
};
