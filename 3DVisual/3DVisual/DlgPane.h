#pragma once
#include "DlgMC.h"
#include "DlgVR.h"
#include "afxcmn.h"


// CDlgPane 对话框

class CDlgPane : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPane)

public:
	CDlgPane(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPane();

// 对话框数据
	enum { IDD = IDD_DLG_PANE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持



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
