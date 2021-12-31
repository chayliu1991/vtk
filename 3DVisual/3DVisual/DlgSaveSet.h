#pragma once
#include "afxwin.h"
#include "BtnST.h"


// CDlgSaveSet �Ի���

class CDlgSaveSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSaveSet)

public:
	CDlgSaveSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSaveSet();

// �Ի�������
	enum { IDD = IDD_DLG_SAVEBMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_SaveName;
	int m_SaveRangeMin;
	int m_SaveRangeMax;
	afx_msg void OnBnClickedSavefolderselect();
	CString m_strFolderPath;
	CButtonST m_SAveBmpBtn,m_SAveBmpOKBtn,m_SAveBmpCancelBtn;
	virtual BOOL OnInitDialog();	
};
