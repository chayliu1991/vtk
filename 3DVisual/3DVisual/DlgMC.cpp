// DlgMC.cpp : 实现文件
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgMC.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "3DVisualDoc.h"
#include "3DVisualView.h"
#include "DlgSaveStlSet.h"

/////////////////////////////
extern UINT data_fg;
int m_VRAlgorithmType = 0;
bool McFinish_fg = false;
bool VrFinish_fg = false;
// CDlgMC 对话框

IMPLEMENT_DYNAMIC(CDlgMC, CDialogEx)

CDlgMC::CDlgMC(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMC::IDD, pParent)
	, m_McSkinValue(50)
	,m_McOpacity(100)
	,m_McSpecular(30)
	,m_IsoValue(50)
	, m_fOpacityValue1(0)
	, m_fOpacityValue2(0.2)
	, m_fOpacityValue3(0.8)
	, m_nOpacity1(30)
	, m_nOpacity2(100)
	, m_nOpacity3(220)
	, m_nGray1(0)
	, m_nGray2(60)
	, m_nGray3(150)
	, m_nGray4(200)
	, m_McDiffuse(60)
	, m_McAmbient(20)
{
	MCBkRGB = RGB(0,0,0);		
	MCSKinRGB = RGB(0,255,0);
	MCAmbientRGB = RGB(0,255,0);
	MCSpecularRGB = RGB(0,255,0);
	m_colorValue1 = RGB(127.5,127.5,127.5);
	m_colorValue2 = RGB(0,255,0);
	m_colorValue3 = RGB(0,0,255);
	m_colorValue4 = RGB(204,204,204);
	m_MCBkColor.SetColor(MCBkRGB);
	m_MCSkinColor.SetColor(MCSKinRGB);
	m_MCSpecularColor.SetColor(MCSpecularRGB);
	m_MCAmbientColor.SetColor(MCAmbientRGB);
	m_VrColorCtr1.SetColor(m_colorValue1);
	m_VrColorCtr2.SetColor(m_colorValue2);
	m_VrColorCtr3.SetColor(m_colorValue3);
	m_VrColorCtr4.SetColor(m_colorValue4);	
}

CDlgMC::~CDlgMC()
{
}

void CDlgMC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MCBKCOLOR, m_MCBkColor);
	DDX_Text(pDX, IDC_SKINVALUE, m_McSkinValue);
	DDV_MinMaxUInt(pDX, m_McSkinValue, 0, 65535);
	DDX_Control(pDX, IDC_MCSKINCOLOR, m_MCSkinColor);
	DDX_Control(pDX, IDC_SLID_MCOPACITY, m_MCOpacity);
	DDX_Control(pDX, IDC_SLID_MCSPECULAR, m_MCSpecular);	
	DDX_Control(pDX, IDC_STARTMC, m_McStartBtn);
	DDX_Control(pDX, IDC_BTNSETSKINVALUE, m_ResetSurfaceBtn);
	DDX_Control(pDX, IDC_STARTVR, m_VrBtn);	
	DDX_Control(pDX, IDC_VRALGORITHMCOM, m_VrAlgorithm);
	DDX_Text(pDX, IDC_MCOPACITY, m_McOpacity);
	DDX_Text(pDX, IDC_MCSPECULAR, m_McSpecular);	
	DDX_Control(pDX, IDC_RESETVRISOVALUE, m_VRIsoValueBtn);
	DDX_Text(pDX, IDC_EDIT_ISOVALUE, m_IsoValue);
	DDX_Control(pDX, IDC_OPACITYSLIDER1, m_OpcitySlider1);
	DDX_Control(pDX, IDC_OPACITYSLIDER2, m_OpcitySlider2);
	DDX_Control(pDX, IDC_OPACITYSLIDER3, m_OpcitySlider3);
	DDX_Text(pDX, IDC_OPACITYEDIT1, m_fOpacityValue1);
	DDX_Text(pDX, IDC_OPACITYEDIT2, m_fOpacityValue2);
	DDX_Text(pDX, IDC_OPACITYEDIT3, m_fOpacityValue3);
	DDX_Text(pDX, IDC_OPACITYTEXT1, m_nOpacity1);
	DDX_Text(pDX, IDC_OPACITYTEXT2, m_nOpacity2);
	DDX_Text(pDX, IDC_OPACITYTEXT3, m_nOpacity3);
	DDX_Text(pDX, IDC_COLORTEXT1, m_nGray1);
	DDV_MinMaxInt(pDX, m_nGray1, 0, 255);
	DDX_Text(pDX, IDC_COLORTEXT2, m_nGray2);
	DDV_MinMaxInt(pDX, m_nGray2, 0, 255);
	DDX_Text(pDX, IDC_COLORTEXT3, m_nGray3);
	DDV_MinMaxInt(pDX, m_nGray3, 0, 255);
	DDX_Text(pDX, IDC_COLORTEXT4, m_nGray4);
	DDV_MinMaxInt(pDX, m_nGray4, 0, 255);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_VrColorCtr1);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, m_VrColorCtr2);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, m_VrColorCtr3);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON4, m_VrColorCtr4);
	DDX_Control(pDX, IDC_SETVRCOLOR, m_SetColorBtn);
	DDX_Control(pDX, IDC_SETVROPACITY, m_VrOpacitySetBtn);
	DDX_Control(pDX, IDC_3DCUT, m_3DCutBtn);
	DDX_Control(pDX, IDC_BUTTON4, m_3DCutCancelBtn);
	DDX_Control(pDX, IDC_SAVESTL, m_SaveStlBtn);
	DDX_Control(pDX, IDC_SLID_MCDIFFUSE, m_MCDiffuse);
	DDX_Text(pDX, IDC_MCDIFFUSE, m_McDiffuse);
	DDX_Control(pDX, IDC_MCDIFFUSESET, m_McdiffuseSet);
	DDX_Control(pDX, IDC_MCAMBIENTCOLOR, m_MCAmbientColor);
	DDX_Control(pDX, IDC_SLID_AMBIENT, m_MCAmbient);
	DDX_Text(pDX, IDC_MCAMBIENT, m_McAmbient);
	DDX_Control(pDX, IDC_MCSPECULARCOLOR, m_MCSpecularColor);
	DDX_Control(pDX, IDC_MCAMBIENTSET, m_AmbientSetBtn);
	DDX_Control(pDX, IDC_MCSPECULARSET, m_DiffuseSetBtn);
	DDX_Control(pDX, IDC_MCOPACITYUSET, m_OpacitySetBtn);
}

BEGIN_MESSAGE_MAP(CDlgMC, CDialogEx)
	ON_BN_CLICKED(IDC_STARTMC, &CDlgMC::OnBnClickedStartmc)
	ON_BN_CLICKED(IDC_BTNSETSKINVALUE, &CDlgMC::OnBnClickedBtnsetskinvalue)
	ON_BN_CLICKED(IDC_MCBKCOLOR, &CDlgMC::OnBnClickedMcbkcolor)
	ON_BN_CLICKED(IDC_MCSKINCOLOR, &CDlgMC::OnBnClickedMcskincolor)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_STARTVR, &CDlgMC::OnBnClickedStartvr)
	ON_CBN_SELCHANGE(IDC_VRALGORITHMCOM, &CDlgMC::OnCbnSelchangeVralgorithmcom)
	ON_BN_CLICKED(IDC_RESETVRISOVALUE, &CDlgMC::OnBnClickedResetvrisovalue)
	ON_WM_PAINT()
	ON_NOTIFY(UDN_DELTAPOS, IDC_OPACITYSPIN1, &CDlgMC::OnDeltaposOpacityspin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OPACITYSPIN2, &CDlgMC::OnDeltaposOpacityspin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OPACITYSPIN3, &CDlgMC::OnDeltaposOpacityspin3)
	ON_BN_CLICKED(IDC_SETVROPACITY, &CDlgMC::OnBnClickedSetvropacity)
	ON_BN_CLICKED(IDC_SETVRCOLOR, &CDlgMC::OnBnClickedSetvrcolor)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CDlgMC::OnBnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &CDlgMC::OnBnClickedMfccolorbutton2)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON3, &CDlgMC::OnBnClickedMfccolorbutton3)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON4, &CDlgMC::OnBnClickedMfccolorbutton4)
	ON_MESSAGE(WM_USER_CHECKALGORITHM, CheckAlgorithm) 
	ON_BN_CLICKED(IDC_3DCUT, &CDlgMC::OnBnClicked3dcut)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgMC::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_SAVESTL, &CDlgMC::OnBnClickedSavestl)
	ON_BN_CLICKED(IDC_MCDIFFUSESET, &CDlgMC::OnBnClickedMcdiffuseset)
	ON_BN_CLICKED(IDC_MCAMBIENTCOLOR, &CDlgMC::OnBnClickedMcambientcolor)
	ON_BN_CLICKED(IDC_MCAMBIENTSET, &CDlgMC::OnBnClickedMcambientset)
	ON_BN_CLICKED(IDC_MCSPECULARCOLOR, &CDlgMC::OnBnClickedMcspecularcolor)
	ON_BN_CLICKED(IDC_MCSPECULARSET, &CDlgMC::OnBnClickedMcspecularset)
	ON_BN_CLICKED(IDC_MCOPACITYUSET, &CDlgMC::OnBnClickedMcopacityuset)
END_MESSAGE_MAP()


// CDlgMC 消息处理程序


void CDlgMC::OnBnClickedStartmc()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0)
		return;
	else
	{
		pView->MarchingCubes();	
		pView->Invalidate(TRUE);
		McFinish_fg = true;
		VrFinish_fg = false;
		EnableMCDialog(true);
		EnableVRDialog(false);
	}			
}

void CDlgMC::OnBnClickedBtnsetskinvalue()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || McFinish_fg==false)
		return;
	else
	{
		UpdateData(TRUE);
		pView->ChangeSkinValue(m_McSkinValue);		
	}	
}


void CDlgMC::OnBnClickedMcbkcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0)
		return;
	else
	{
		
		MCBkRGB = m_MCBkColor.GetColor();
		BYTE rr = GetRValue(MCBkRGB);
		BYTE gg = GetGValue(MCBkRGB);
		BYTE bb = GetBValue(MCBkRGB);
		float R = (float)rr / 255.0;
		float G  = (float)gg / 255.0;
		float B  = (float)bb / 255.0;
		if(McFinish_fg)
			pView->ChangeMCBkColor(R,G,B);
		if(VrFinish_fg)
			pView->ChangeVRBkColor(R,G,B);
	}	
}


void CDlgMC::OnBnClickedMcskincolor()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || McFinish_fg==false)
		return;
	else
	{
		MCSKinRGB = m_MCSkinColor.GetColor();
		BYTE rr = GetRValue(MCSKinRGB);
		BYTE gg = GetGValue(MCSKinRGB);
		BYTE bb = GetBValue(MCSKinRGB);
		float R = (float)rr / 255.0;
		float G  = (float)gg / 255.0;
		float B  = (float)bb / 255.0;
		pView->ChangeMCSkinColor(R,G,B);
	}	
}


void CDlgMC::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(TRUE);
	int nID = pScrollBar->GetDlgCtrlID();

	/////面绘制
	if(nID == IDC_SLID_MCOPACITY)
	{
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLID_MCOPACITY);		
		m_McOpacity =  pSlidCtrl->GetPos();		
	}

	if(nID ==IDC_SLID_MCDIFFUSE)
	{
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLID_MCDIFFUSE);
		m_McDiffuse = pSlidCtrl->GetPos();
	}
	if(nID ==IDC_SLID_AMBIENT)
	{
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLID_AMBIENT);
		m_McAmbient = pSlidCtrl->GetPos();
	}
	if(nID == IDC_SLID_MCSPECULAR)
	{
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLID_MCSPECULAR);
		m_McSpecular = pSlidCtrl->GetPos();			
	}
	
	/////体绘制
	if(nID == IDC_OPACITYSLIDER1)
	{
		if(VrFinish_fg == FALSE)
			return;
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_OPACITYSLIDER1);
		m_nOpacity1 = pSlidCtrl->GetPos();			
	}
	if(nID == IDC_OPACITYSLIDER2)
	{
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_OPACITYSLIDER2);
		m_nOpacity2= pSlidCtrl->GetPos();			
	}
	if(nID == IDC_OPACITYSLIDER3)
	{
		if(VrFinish_fg == FALSE)
			return;
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_OPACITYSLIDER3);
		m_nOpacity3 = pSlidCtrl->GetPos();			
	}

	UpdateData(FALSE);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CDlgMC::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_MCOpacity.SetRange(0,100);
	m_MCOpacity.SetTicFreq(1);
	m_MCOpacity.SetPos(100);

	m_MCSpecular.SetRange(0,100);
	m_MCSpecular.SetTicFreq(1);
	m_MCSpecular.SetPos(30);

	m_MCAmbient.SetRange(0,100);
	m_MCAmbient.SetTicFreq(1);
	m_MCAmbient.SetPos(20);
	
	m_MCDiffuse.SetRange(0,100);
	m_MCDiffuse.SetTicFreq(1);
	m_MCDiffuse.SetPos(60);

	m_McStartBtn.SetIcon(IDI_MC);
	m_ResetSurfaceBtn.SetIcon(IDI_SURFACE);
	m_VrBtn.SetIcon(IDI_LIGHT);
	m_VRIsoValueBtn.SetIcon(IDI_ISOVALUE);
	m_SetColorBtn.SetIcon(IDI_COLOR);
	m_VrOpacitySetBtn.SetIcon(IDI_OPACITY);
	m_3DCutBtn.SetIcon(IDI_CUT);
	m_3DCutCancelBtn.SetIcon(IDI_CUTCANCEL);
	m_SaveStlBtn.SetIcon(IDI_STL);
	m_AmbientSetBtn.SetIcon(IDI_SETOK);
	m_DiffuseSetBtn.SetIcon(IDI_SETOK);
	m_OpacitySetBtn.SetIcon(IDI_SETOK);
	m_McdiffuseSet.SetIcon(IDI_SETOK);

	m_VrAlgorithm.AddString("合成体绘制");
	m_VrAlgorithm.AddString("最大密度投影");
	m_VrAlgorithm.AddString("等值面提取");
	m_VrAlgorithm.SetCurSel(0);
	
	((CDlgMC*)GetDlgItem(IDC_EDIT_ISOVALUE))->EnableWindow(FALSE);
	((CDlgMC*)GetDlgItem(IDC_RESETVRISOVALUE))->EnableWindow(FALSE);
	
	m_OpcitySlider1.SetRange(0,255);
	m_OpcitySlider1.SetTicFreq(1);
	m_OpcitySlider1.SetPos(30);
	m_OpcitySlider2.SetRange(0,255);
	m_OpcitySlider2.SetTicFreq(1);
	m_OpcitySlider2.SetPos(100);
	m_OpcitySlider3.SetRange(0,255);
	m_OpcitySlider3.SetTicFreq(1);
	m_OpcitySlider3.SetPos(220);

	EnableVRDialog(false);
	EnableMCDialog(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgMC::OnCbnSelchangeVralgorithmcom()
{
	// TODO: 在此添加控件通知处理程序代码
	m_VRAlgorithmType = m_VrAlgorithm.GetCurSel();
	switch(m_VRAlgorithmType)
	{
	case 0:
		((CDlgMC*)GetDlgItem(IDC_EDIT_ISOVALUE))->EnableWindow(FALSE);
		((CDlgMC*)GetDlgItem(IDC_RESETVRISOVALUE))->EnableWindow(FALSE);
		break;
	case 1:
		((CDlgMC*)GetDlgItem(IDC_EDIT_ISOVALUE))->EnableWindow(FALSE);
		((CDlgMC*)GetDlgItem(IDC_RESETVRISOVALUE))->EnableWindow(FALSE);
		break;
	case 2:
		((CDlgMC*)GetDlgItem(IDC_EDIT_ISOVALUE))->EnableWindow(TRUE);
		((CDlgMC*)GetDlgItem(IDC_RESETVRISOVALUE))->EnableWindow(TRUE);
	}
}

 LRESULT CDlgMC::CheckAlgorithm(WPARAM wParam, LPARAM lParam) 
 {
	 switch(m_VRAlgorithmType)
	{
	case 0:
		((CDlgMC*)GetDlgItem(IDC_EDIT_ISOVALUE))->EnableWindow(FALSE);
		((CDlgMC*)GetDlgItem(IDC_RESETVRISOVALUE))->EnableWindow(FALSE);
		m_VrAlgorithm.SetCurSel(0);
		break;
	case 1:
		((CDlgMC*)GetDlgItem(IDC_EDIT_ISOVALUE))->EnableWindow(FALSE);
		((CDlgMC*)GetDlgItem(IDC_RESETVRISOVALUE))->EnableWindow(FALSE);
		m_VrAlgorithm.SetCurSel(1);
		break;
	case 2:
		((CDlgMC*)GetDlgItem(IDC_EDIT_ISOVALUE))->EnableWindow(TRUE);
		((CDlgMC*)GetDlgItem(IDC_RESETVRISOVALUE))->EnableWindow(TRUE);
		m_VrAlgorithm.SetCurSel(2);
	}
	 return 0;
 }



void CDlgMC::OnBnClickedStartvr()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0)
		return;
	else
	{	
		pView->RayCasting();	
		pView->Invalidate(TRUE);
		VrFinish_fg = true;
		McFinish_fg = false;
		EnableVRDialog(true);
		EnableMCDialog(false);
	}		
}


void CDlgMC::OnBnClickedResetvrisovalue()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || VrFinish_fg == false)
		return;
	else
	{		
		pView->ReSetISOValue(m_IsoValue);			
	}

}

void CDlgMC::OnDeltaposOpacityspin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if(VrFinish_fg == FALSE)
		return;
	int nPos = m_OpcitySlider1.GetPos();
	if(nPos<255 && nPos>0)
	{
		if(pNMUpDown->iDelta >0)	
			nPos--;
		if(pNMUpDown->iDelta <0)
			nPos++;	

	}	
	if(nPos==255 && pNMUpDown->iDelta>0)
		nPos--;
	if(nPos==0 && pNMUpDown->iDelta<0)
		nPos++;	
	m_OpcitySlider1.SetPos(nPos);
	m_nOpacity1 = nPos;
	UpdateData(FALSE);	
}


void CDlgMC::OnDeltaposOpacityspin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if(VrFinish_fg == FALSE)
		return;
	int nPos = m_OpcitySlider2.GetPos();
	if(nPos<255 && nPos>0)
	{
		if(pNMUpDown->iDelta >0)	
			nPos--;
		if(pNMUpDown->iDelta <0)
			nPos++;	

	}	
	if(nPos==255 && pNMUpDown->iDelta>0)
		nPos--;
	if(nPos==0 && pNMUpDown->iDelta<0)
		nPos++;	
	m_OpcitySlider2.SetPos(nPos);
	m_nOpacity2 = nPos;
	UpdateData(FALSE);
}


void CDlgMC::OnDeltaposOpacityspin3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(VrFinish_fg == FALSE)
		return;
	*pResult = 0;
	int nPos = m_OpcitySlider3.GetPos();
	if(nPos<255 && nPos>0)
	{
		if(pNMUpDown->iDelta >0)	
			nPos--;
		if(pNMUpDown->iDelta <0)
			nPos++;	

	}	
	if(nPos==255 && pNMUpDown->iDelta>0)
		nPos--;
	if(nPos==0 && pNMUpDown->iDelta<0)
		nPos++;	
	m_OpcitySlider3.SetPos(nPos);
	m_nOpacity3 = nPos;
	UpdateData(FALSE);
}


void CDlgMC::OnBnClickedSetvropacity()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || VrFinish_fg == false)
		return;
	else
	{		
		pView->ReSetOPACITY(m_nOpacity1,m_nOpacity2,m_nOpacity3,m_fOpacityValue1,m_fOpacityValue2,
			m_fOpacityValue3);			
	}
}
void CDlgMC::OnBnClickedSetvrcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || VrFinish_fg == false)
		return;
	else
	{		
		pView->ReSetColor(m_nGray1,m_nGray2,m_nGray3,m_nGray4,
			m_colorValue1,m_colorValue2,m_colorValue3,m_colorValue4);			
	}
}


void CDlgMC::OnBnClickedMfccolorbutton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_colorValue1 = m_VrColorCtr1.GetColor();
}


void CDlgMC::OnBnClickedMfccolorbutton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_colorValue2 = m_VrColorCtr2.GetColor();
}


void CDlgMC::OnBnClickedMfccolorbutton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_colorValue3 = m_VrColorCtr3.GetColor();
}


void CDlgMC::OnBnClickedMfccolorbutton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_colorValue4 = m_VrColorCtr4.GetColor();
}


void CDlgMC::EnableVRDialog(BOOL flag)
{
	((CDlgMC*)GetDlgItem(IDC_OPACITYSPIN1))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_OPACITYSPIN2))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_OPACITYSPIN3))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_OPACITYSLIDER1))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_OPACITYSLIDER2))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_OPACITYSLIDER3))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_OPACITYEDIT1))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_OPACITYEDIT2))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_OPACITYEDIT3))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_SETVROPACITY))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_COLORTEXT1))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_COLORTEXT2))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_COLORTEXT3))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_COLORTEXT4))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_MFCCOLORBUTTON1))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_MFCCOLORBUTTON2))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_MFCCOLORBUTTON3))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_MFCCOLORBUTTON4))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_SETVRCOLOR))->EnableWindow(flag);
	
}

void CDlgMC::EnableMCDialog(BOOL flag)
{
	
	((CDlgMC*)GetDlgItem(IDC_SKINVALUE))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_BTNSETSKINVALUE))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_SLID_MCOPACITY))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_SLID_MCSPECULAR))->EnableWindow(flag);	
	((CDlgMC*)GetDlgItem(IDC_MCSKINCOLOR))->EnableWindow(flag);		
	((CDlgMC*)GetDlgItem(IDC_MCAMBIENTCOLOR))->EnableWindow(flag);	
	((CDlgMC*)GetDlgItem(IDC_SAVESTL))->EnableWindow(flag);	
	((CDlgMC*)GetDlgItem(IDC_MCSPECULARCOLOR))->EnableWindow(flag);	
	((CDlgMC*)GetDlgItem(IDC_SLID_MCOPACITY))->EnableWindow(flag);
	((CDlgMC*)GetDlgItem(IDC_SLID_MCSPECULAR))->EnableWindow(flag);	
	((CDlgMC*)GetDlgItem(IDC_SLID_MCDIFFUSE))->EnableWindow(flag);		
	((CDlgMC*)GetDlgItem(IDC_SLID_AMBIENT))->EnableWindow(flag);	
	((CDlgMC*)GetDlgItem(IDC_MCOPACITYUSET))->EnableWindow(flag);	
	((CDlgMC*)GetDlgItem(IDC_MCSPECULARSET))->EnableWindow(flag);	
	((CDlgMC*)GetDlgItem(IDC_MCDIFFUSESET))->EnableWindow(flag);		
	((CDlgMC*)GetDlgItem(IDC_MCAMBIENTSET))->EnableWindow(flag);	

}



void CDlgMC::OnBnClicked3dcut()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 )
		return;
	if(VrFinish_fg)
	{
		pView->VRVolumeCut();

	}
	else if(McFinish_fg)
	{		
		pView->MCVolumeCut();		
	}
}

void CDlgMC::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 )
		return;
	if(VrFinish_fg)
	{
		pView->VRVolumeCutCancel();
	}
	else if(McFinish_fg)
	{		
		pView->MCVolumeCutCancel();
	}
}


void CDlgMC::OnBnClickedSavestl()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 ||McFinish_fg==false)
		return;	
	CDlgSaveStlSet dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_stlFileFolder = dlg.m_strFolder;
		m_stlfileName = dlg.m_strName;		
	}
	else
		return;	
	pView->SaveStl(m_stlFileFolder,m_stlfileName);
}


void CDlgMC::OnBnClickedMcdiffuseset()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || McFinish_fg==false)
		return;
	else
	{		
		pView->ChangeMCDiffuse((double)m_McDiffuse/100);		
	}	
}


void CDlgMC::OnBnClickedMcambientcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || McFinish_fg==false)
		return;
	else
	{
		MCAmbientRGB = m_MCAmbientColor.GetColor();
		BYTE rr = GetRValue(MCAmbientRGB);
		BYTE gg = GetGValue(MCAmbientRGB);
		BYTE bb = GetBValue(MCAmbientRGB);
		float R = (float)rr / 255.0;
		float G  = (float)gg / 255.0;
		float B  = (float)bb / 255.0;
		pView->ChangeMCAmbientColor(R,G,B);
	}	
}


void CDlgMC::OnBnClickedMcambientset()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || McFinish_fg==false)
		return;
	else
	{		
		pView->ChangeMCAmbient((double)m_McAmbient/100);		
	}	

}


void CDlgMC::OnBnClickedMcspecularcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || McFinish_fg==false)
		return;
	else
	{
		MCSpecularRGB = m_MCSpecularColor.GetColor();
		BYTE rr = GetRValue(MCSpecularRGB);
		BYTE gg = GetGValue(MCSpecularRGB);
		BYTE bb = GetBValue(MCSpecularRGB);
		float R = (float)rr / 255.0;
		float G  = (float)gg / 255.0;
		float B  = (float)bb / 255.0;
		pView->ChangeMCSpecularColor(R,G,B);
	}	
}


void CDlgMC::OnBnClickedMcspecularset()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || McFinish_fg==false)
		return;
	else
	{		
		pView->ChangeMCSpecular((double)m_McSpecular/100);		
	}	
}


void CDlgMC::OnBnClickedMcopacityuset()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CMy3DVisualView* pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CMy3DVisualDoc * pDoc = (CMy3DVisualDoc *)pFrame->GetActiveDocument();
	if(data_fg==0 || McFinish_fg==false)
		return;
	else
	{		
		pView->ChangeMCOpacity((double)m_McOpacity/100);		
	}	
}
