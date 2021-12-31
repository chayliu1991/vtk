#pragma once
#include "DlgPane.h"

// CToosDockAblePane

class CToosDockAblePane : public CDockablePane
{
	DECLARE_DYNAMIC(CToosDockAblePane)

public:
	CToosDockAblePane();
	virtual ~CToosDockAblePane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL IsResizable() const { return FALSE; }//��ֹResize
	virtual BOOL CanFloat() const { return FALSE; }   //��ֹ����
	virtual BOOL CanBeClosed() const  { return FALSE; }//��ֹ�ر�	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	CDlgPane m_paneDlg;
};


