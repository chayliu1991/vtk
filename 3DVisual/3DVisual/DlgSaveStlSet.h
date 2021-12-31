#pragma once
#include "afxwin.h"
#include "BtnST.h"

// CDlgSaveStlSet 对话框

class CDlgSaveStlSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSaveStlSet)

public:
	CDlgSaveStlSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSaveStlSet();

// 对话框数据
	enum { IDD = IDD_DLGSAVESTLSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStlsave();
	CString m_strFolder;
	CString m_strName;
	virtual BOOL OnInitDialog();
	CButtonST m_SaveStlBtn,m_StlSaveOK,m_StlSaveCancel;
	;
};
