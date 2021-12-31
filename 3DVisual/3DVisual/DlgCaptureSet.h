#pragma once
#include "afxwin.h"
#include "BtnST.h"

// CDlgCaptureSet 对话框

class CDlgCaptureSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCaptureSet)

public:
	CDlgCaptureSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCaptureSet();

// 对话框数据
	enum { IDD = IDD_CAPTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCapturebtn();
	CString m_strCaptureFolderPath;
	CString m_CaptureName;
	CButtonST m_CapturePathBtn,m_CaptureOKBtn,m_CaptureCancelBtn;	
	virtual BOOL OnInitDialog();
};
