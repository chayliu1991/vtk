#pragma once
#include "afxwin.h"
#include "BtnST.h"

// CDlgSaveStlSet �Ի���

class CDlgSaveStlSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSaveStlSet)

public:
	CDlgSaveStlSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSaveStlSet();

// �Ի�������
	enum { IDD = IDD_DLGSAVESTLSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStlsave();
	CString m_strFolder;
	CString m_strName;
	virtual BOOL OnInitDialog();
	CButtonST m_SaveStlBtn,m_StlSaveOK,m_StlSaveCancel;
	;
};
