
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "MySplitWnd.h"
#include "ToosDockAblePane.h"


//�Զ�����Ϣ
#define WM_USER_CHECKALGORITHM   WM_USER + 1



class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
////////////////////////////////////////////////////////////////////
public:
	CToosDockAblePane m_toolpane;  
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	CMySplitWnd m_splitWnd;
	afx_msg void On3dcapture();
	void Capture(int ntype);
	int CaptureType;
	CString m_captureFolder;
	CString m_CaptureName;	
	afx_msg void OnZoxcapture();
	afx_msg void OnYozcapture();
	afx_msg void OnXoycapture();
	int ColorSetType;
	afx_msg void On3dbkcolorset();	
	afx_msg void OnZoxbkcolorset();
	afx_msg void OnYozbkcolorset();
	afx_msg void OnXoybkcolorset();
	void ColorSet(int type);
	afx_msg void OnMc();
	afx_msg void OnRc();
	afx_msg void OnMip();
	afx_msg void OnIso();
};


