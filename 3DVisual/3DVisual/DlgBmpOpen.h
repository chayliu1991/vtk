#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "btnst.h"

// CDlgBmpOpen �Ի���

class CDlgBmpOpen : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBmpOpen)

public:
	CDlgBmpOpen(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBmpOpen();

// �Ի�������
	enum { IDD = IDD_BMPIMPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnbmpopen();
	CListCtrl m_BmpStackList;
	CString m_BmpFolderName;	
	int m_BmpWidth;
	int m_BmpHeight;
	int m_bmpStartNum;
	int m_bmpEndNum;
	float m_fsample;
	float m_fbmpSpaceX;
	float m_fbmpSpaceY;
	float m_fbmpSpaceZ;
	CButtonST m_BmpOpenBtn,m_DocYesBtn,m_DocNoBtn;

};
