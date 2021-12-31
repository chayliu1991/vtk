#pragma once
#include "afxwin.h"
#include "BtnST.h"


// CDlgSaveSet 对话框

class CDlgSaveSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSaveSet)

public:
	CDlgSaveSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSaveSet();

// 对话框数据
	enum { IDD = IDD_DLG_SAVEBMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
