
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "3DVisual.h"
#include "MainFrm.h"
#include "3DVisualDoc.h"
#include "3DVisualView.h"
#include "BttmView.h"
#include "DlgCaptureSet.h"
#include "BttmOneView.h"
#include "BttmTwoView.h"
#include "BttmThreeView.h"
#include "BttmView.h"
#include "SplashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


////////////////////////////////////////
extern UINT data_fg;
extern bool McFinish_fg;
extern bool VrFinish_fg;
extern int m_VRAlgorithmType;



// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_3DCAPTURE, &CMainFrame::On3dcapture)
	ON_COMMAND(ID_ZOXCAPTURE, &CMainFrame::OnZoxcapture)
	ON_COMMAND(ID_YOZCAPTURE, &CMainFrame::OnYozcapture)
	ON_COMMAND(ID_XOYCAPTURE, &CMainFrame::OnXoycapture)
	ON_COMMAND(IDC_3DBKCOLORSET, &CMainFrame::On3dbkcolorset)
	ON_COMMAND(IDC_ZOXBKCOLORSET, &CMainFrame::OnZoxbkcolorset)
	ON_COMMAND(IDC_YOZBKCOLORSET, &CMainFrame::OnYozbkcolorset)
	ON_COMMAND(IDC_XOYBKCOLORSET, &CMainFrame::OnXoybkcolorset)
	ON_COMMAND(ID_MC, &CMainFrame::OnMc)
	ON_COMMAND(ID_RC, &CMainFrame::OnRc)
	ON_COMMAND(ID_MIP, &CMainFrame::OnMip)
	ON_COMMAND(ID_ISO, &CMainFrame::OnIso)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLACK);
	CaptureType = 0;
	ColorSetType = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SplashWnd  splash;
	splash.ShowSplashWnd(this);
	Sleep(2000);


	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);
	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}
		
	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
	
	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}	

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// �����û�����Ĺ���������:
	//InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);
	m_wndToolBar.ShowWindow(SW_HIDE);


	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);
	CMFCToolBar::SetBasicCommands(lstBasicCommands);
	////////////////////////////////////////////////
	if (!m_toolpane.Create(_T(""), this, CRect(0, 0, 320, 1000), TRUE, IDD_DLG_PANE, WS_CHILD | 
		WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT ))
	{
		TRACE0("Failed to create LeftPane\n");
		return -1;
	}
	AddPane(&m_toolpane);//��ֹResize������AddPane
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// ��������ͼ
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ���������ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// �����ļ���ͼ
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������ļ���ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// �����������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	// �������Դ���
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ��������ԡ�����\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// ���ཫִ�������Ĺ���

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	CRect rect;
	GetClientRect(&rect);

	if(!m_splitWnd.CreateStatic(this,2,1))
		return FALSE;
	m_splitWnd.CreateView(0,0,RUNTIME_CLASS(CMy3DVisualView),CSize(rect.Width(),rect.Height()),pContext);	
	m_splitWnd.CreateView(1,0,RUNTIME_CLASS(CBttmView),CSize(rect.Width(),rect.Height()*0),pContext);	
	return true;	
}


void CMainFrame::On3dcapture()
{
	// TODO: �ڴ���������������
	CaptureType=0;
	Capture(CaptureType);
}

void CMainFrame::Capture(int ntype)
{
	CDlgCaptureSet dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_captureFolder = dlg.m_strCaptureFolderPath;
		m_CaptureName = dlg.m_CaptureName;		
	}
	else
		return;	
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   	
	CMy3DVisualView* pTtmview = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));

	switch(ntype)
	{
	case 0:
		pTtmview->Capture(m_captureFolder,m_CaptureName);
		break;
	case 1:
		pSliceView1->Capture(m_captureFolder,m_CaptureName);
		break;
	case 2:
		pSliceView2->Capture(m_captureFolder,m_CaptureName);
		break;
	case 3:
		pSliceView3->Capture(m_captureFolder,m_CaptureName);
		break;
	}
}

void CMainFrame::OnZoxcapture()
{
	// TODO: �ڴ���������������
	CaptureType=1;
	Capture(CaptureType);
}


void CMainFrame::OnYozcapture()
{
	// TODO: �ڴ���������������
	CaptureType=2;
	Capture(CaptureType);
}


void CMainFrame::OnXoycapture()
{
	// TODO: �ڴ���������������
	CaptureType=3;
	Capture(CaptureType);
}


void CMainFrame::On3dbkcolorset()
{
	// TODO: �ڴ���������������
	ColorSetType = 0;
	ColorSet(ColorSetType);
}


void CMainFrame::OnZoxbkcolorset()
{
	// TODO: �ڴ���������������
	ColorSetType = 1;
	ColorSet(ColorSetType);
}


void CMainFrame::OnYozbkcolorset()
{
	// TODO: �ڴ���������������
	ColorSetType = 2;
	ColorSet(ColorSetType);
}


void CMainFrame::OnXoybkcolorset()
{
	// TODO: �ڴ���������������
	ColorSetType = 3; 
	ColorSet(ColorSetType);
}


void CMainFrame::ColorSet(int type)
{
	CColorDialog dlg;
	COLORREF clr;
	if(dlg.DoModal() ==IDOK)
	{
		clr = dlg.GetColor();
	}
	else
		return;

	if(data_fg==0)
		return;
	BYTE rr = GetRValue(clr);
	BYTE gg = GetGValue(clr);
	BYTE bb = GetBValue(clr);
	float R = (float)rr / 255.0;
	float G  = (float)gg / 255.0;
	float B  = (float)bb / 255.0;
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   	
	CMy3DVisualView* pTtmview = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	
	if(type==0)
	{
		if(McFinish_fg)
			pTtmview->ChangeMCBkColor(R,G,B);
		if(VrFinish_fg)
			pTtmview->ChangeVRBkColor(R,G,B);
	}
	else if(type==1)
	{
		pSliceView1->ChangeXBkColor(R,G,B);
	}
	else if(type==2)
	{
		pSliceView2->ChangeYBkColor(R,G,B);
	}
	else
	{
		pSliceView3->ChangeZBkColor(R,G,B);
	}	
}


void CMainFrame::OnMc()
{
	// TODO: �ڴ���������������
	m_toolpane.m_paneDlg.m_dlgmc.PostMessageA(WM_COMMAND,IDC_STARTMC);	
}


void CMainFrame::OnRc()
{
	// TODO: �ڴ���������������
	m_VRAlgorithmType = 0;
	m_toolpane.m_paneDlg.m_dlgmc.PostMessageA(WM_USER_CHECKALGORITHM);
	m_toolpane.m_paneDlg.m_dlgmc.PostMessageA(WM_COMMAND,IDC_STARTVR);
}


void CMainFrame::OnMip()
{
	// TODO: �ڴ���������������
	m_VRAlgorithmType = 1;
	m_toolpane.m_paneDlg.m_dlgmc.PostMessageA(WM_USER_CHECKALGORITHM);
	m_toolpane.m_paneDlg.m_dlgmc.PostMessageA(WM_COMMAND,IDC_STARTVR);
}


void CMainFrame::OnIso()
{
	// TODO: �ڴ���������������
	m_VRAlgorithmType = 2;
	m_toolpane.m_paneDlg.m_dlgmc.PostMessageA(WM_USER_CHECKALGORITHM);
	m_toolpane.m_paneDlg.m_dlgmc.PostMessageA(WM_COMMAND,IDC_STARTVR);
}
