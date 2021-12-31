#pragma once
#include "afxwin.h"
#include "BtnST.h"

// CDlgCaptureSet �Ի���

class CDlgCaptureSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCaptureSet)

public:
	CDlgCaptureSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCaptureSet();

// �Ի�������
	enum { IDD = IDD_CAPTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCapturebtn();
	CString m_strCaptureFolderPath;
	CString m_CaptureName;
	CButtonST m_CapturePathBtn,m_CaptureOKBtn,m_CaptureCancelBtn;	
	virtual BOOL OnInitDialog();
};
