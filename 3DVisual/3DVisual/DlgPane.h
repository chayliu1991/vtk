#pragma once
#include "DlgMC.h"
#include "DlgVR.h"
#include "afxcmn.h"


// CDlgPane �Ի���

class CDlgPane : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPane)

public:
	CDlgPane(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPane();

// �Ի�������
	enum { IDD = IDD_DLG_PANE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��



	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangePanetab(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_paneTab;
	CDlgVR   m_dlgvr;
	CDlgMC   m_dlgmc;
	CRect tabRect;  
	void InitSliceSlider();
};
