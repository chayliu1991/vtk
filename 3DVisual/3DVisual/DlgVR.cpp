// DlgVR.cpp : 实现文件
//

#pragma  once
#include "stdafx.h"
#include "3DVisual.h"
#include "DlgVR.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "3DVisualDoc.h"
#include "3DVisualView.h"
#include "BttmView.h"
#include "BttmOneView.h"
#include "BttmTwoView.h"
#include "BttmThreeView.h"
#include "DlgTemplate.h"

#include "DlgCaptureSet.h"




//////////////////////////////////
extern int SliceXNum;
extern int SliceYNum;
extern int SliceZNum;
extern UINT data_fg;
extern double Window;
extern double Level;
int GaussTemplateSize = 5;
float GaussTempltateSd = 3;
int InteraNum = 10;
double DiffThread =20;
int BinValue =100; 


// CDlgVR 对话框

IMPLEMENT_DYNAMIC(CDlgVR, CDialogEx)

CDlgVR::CDlgVR(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVR::IDD, pParent)	
	, m_PicMAinpulateRadioBtn(0)
{
	m_Playfg = false;
	SLiceXBkRGB = RGB(0,0,0);
	SLiceYBkRGB = RGB(0,0,0);
	SLiceZBkRGB = RGB(0,0,0);
	m_SaveFolderName = "";
	m_SaveFileName = "";
	m_SaveFileRangeMin = 0;
	m_SaveFileRangeMax = 0 ;}

CDlgVR::~CDlgVR()
{
}

void CDlgVR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDERSLICEX, m_SliderSliceX);
	DDX_Control(pDX, IDC_SLIDERSLICEY, m_SliderSliceY);
	DDX_Control(pDX, IDC_SLIDERSLICEZ, m_SliderSliceZ);		
	DDX_Control(pDX, IDC_SLICEPLAY_COMB, m_SlicePlayComb);
	DDX_Control(pDX, IDC_WINDOWSLIDER, m_WindowSlider);
	DDX_Control(pDX, IDC_LEVELSLIDER, m_LevelSlider);
	DDX_Control(pDX, IDC_BKCOLORSLICEX, m_SliceXBKColor);
	DDX_Control(pDX, IDC_BKCOLORSLICEY, m_SliceYBKColor);
	DDX_Control(pDX, IDC_BKCOLORSLICEZ, m_SliceZBKColor);
	DDX_Control(pDX, IDC_SLICEPLAYBTN, m_SlicePlayBtn);
	DDX_Control(pDX, IDC_VERTIMIRROR, m_VerticalMirrorBtn);
	DDX_Control(pDX, IDC_HORIMIRROR, m_HorizontalMirrorBtn);
	DDX_Control(pDX, IDC_LEFTROTATION, m_TurnLeftBtn);
	DDX_Control(pDX, IDC_RIGHTROTATION, m_TurnRightBtn);
	DDX_Control(pDX, IDC_ANISOTROPYFILTER, m_AnistropyFilterBtn);
	DDX_Control(pDX, IDC_GAUSS, m_GaussSmoothBtn);
	DDX_Control(pDX, IDC_TEMPLATE, m_TemplateSetBtn);
	DDX_Control(pDX, IDC_MEANFILTER, m_MeanFilterBtn);
	DDX_Control(pDX, IDC_EDGEDETECTION, m_EdgeDetectionBtn);
	DDX_Control(pDX, IDC_SAVEBMP, m_SaveBmpBtn);

	DDX_Control(pDX, IDC_BINARY, m_binBtn);
	DDX_Control(pDX, IDC_CAPTURE, m_CaptureBtn);
	DDX_Control(pDX, IDC_SETWINWDOWLEVELBTN, m_SetWindowBtn);
	DDX_Control(pDX, IDC_RESETWINWDOWLEVELBTN, m_ResetWindowBtn);
}


BEGIN_MESSAGE_MAP(CDlgVR, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SLICESPINX, &CDlgVR::OnDeltaposSlicespinx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SLICESPINY, &CDlgVR::OnDeltaposSlicespiny)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SLICESPINZ, &CDlgVR::OnDeltaposSlicespinz)
	ON_WM_HSCROLL()	
	ON_BN_CLICKED(IDC_SLICEPLAYBTN, &CDlgVR::OnBnClickedSliceplaybtn)
	ON_WM_TIMER()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RESETWINWDOWLEVELBTN, &CDlgVR::OnBnClickedResetwinwdowlevelbtn)
	ON_BN_CLICKED(IDC_SETWINWDOWLEVELBTN, &CDlgVR::OnBnClickedSetwinwdowlevelbtn)
	ON_BN_CLICKED(IDC_BKCOLORSLICEX, &CDlgVR::OnBnClickedBkcolorslicex)
	ON_BN_CLICKED(IDC_BKCOLORSLICEY, &CDlgVR::OnBnClickedBkcolorslicey)
	ON_BN_CLICKED(IDC_BKCOLORSLICEZ, &CDlgVR::OnBnClickedBkcolorslicez)
	ON_BN_CLICKED(IDC_ZXMAINPULATERADIO, &CDlgVR::OnBnClickedZxmainpulateradio)
	ON_BN_CLICKED(IDC_YZMAINPULATERADIO, &CDlgVR::OnBnClickedYzmainpulateradio)
	ON_BN_CLICKED(IDC_XYMAINPULATERADIO, &CDlgVR::OnBnClickedXymainpulateradio)
	ON_BN_CLICKED(IDC_LEFTROTATION, &CDlgVR::OnBnClickedLeftrotation)
	ON_BN_CLICKED(IDC_RIGHTROTATION, &CDlgVR::OnBnClickedRightrotation)
	ON_BN_CLICKED(IDC_HORIMIRROR, &CDlgVR::OnBnClickedHorimirror)
	ON_BN_CLICKED(IDC_VERTIMIRROR, &CDlgVR::OnBnClickedVertimirror)
	ON_BN_CLICKED(IDC_ANISOTROPYFILTER, &CDlgVR::OnBnClickedAnisotropyfilter)
	ON_BN_CLICKED(IDC_GAUSS, &CDlgVR::OnBnClickedGauss)
	ON_BN_CLICKED(IDC_TEMPLATE, &CDlgVR::OnBnClickedTemplate)
	ON_BN_CLICKED(IDC_MEANFILTER, &CDlgVR::OnBnClickedMeanfilter)
	ON_BN_CLICKED(IDC_EDGEDETECTION, &CDlgVR::OnBnClickedEdgedetection)
	ON_BN_CLICKED(IDC_SAVEBMP, &CDlgVR::OnBnClickedSavebmp)
	ON_BN_CLICKED(IDC_BINARY, &CDlgVR::OnBnClickedBinary)
	ON_BN_CLICKED(IDC_CAPTURE, &CDlgVR::OnBnClickedCapture)
END_MESSAGE_MAP()


// CDlgVR 消息处理程序


void CDlgVR::OnDeltaposSlicespinx(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_SliderSliceX.GetPos();
	if(nPos<SliceXNum && nPos>0)
	{
		if(pNMUpDown->iDelta >0)	
			nPos--;
		if(pNMUpDown->iDelta <0)
			nPos++;	
		
	}	
	if(nPos==SliceXNum && pNMUpDown->iDelta>0)
		nPos--;
	if(nPos==0 && pNMUpDown->iDelta<0)
		nPos++;	
	m_SliderSliceX.SetPos(nPos);
	SetSliceX(nPos);		
	char str[100];
	sprintf(str,"%d",nPos);
	((CDlgVR*)GetDlgItem(IDC_TXT_SLICEPOSX))->SetWindowTextA(str);
	*pResult = 0;
}


void CDlgVR::OnDeltaposSlicespiny(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_SliderSliceY.GetPos();
	if(nPos<SliceYNum && nPos>0)
	{
		if(pNMUpDown->iDelta >0)	
			nPos--;
		if(pNMUpDown->iDelta <0)
			nPos++;			
	}
	if(nPos==SliceYNum && pNMUpDown->iDelta>0)
		nPos--;
	if(nPos==0 && pNMUpDown->iDelta<0)
		nPos++;	
	m_SliderSliceY.SetPos(nPos);
	SetSliceY(nPos);		
	char str[100];
	sprintf(str,"%d",nPos);
	((CDlgVR*)GetDlgItem(IDC_TXT_SLICEPOSY))->SetWindowTextA(str);
	*pResult = 0;
}


void CDlgVR::OnDeltaposSlicespinz(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_SliderSliceZ.GetPos();
	if(nPos<SliceZNum && nPos>0)
	{
		if(pNMUpDown->iDelta >0)	
			nPos--;
		if(pNMUpDown->iDelta <0)
			nPos++;						
	}
	if(nPos==SliceZNum && pNMUpDown->iDelta>0)
		nPos--;
	if(nPos==0 && pNMUpDown->iDelta<0)
		nPos++;		
	char str[100];
	m_SliderSliceZ.SetPos(nPos);
	sprintf(str,"%d",nPos);
	((CDlgVR*)GetDlgItem(IDC_TXT_SLICEPOSZ))->SetWindowTextA(str);
	SetSliceZ(nPos);	
	*pResult = 0;
}


void CDlgVR::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nID = pScrollBar->GetDlgCtrlID();
	if(nID == IDC_SLIDERSLICEX)
	{
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDERSLICEX);	
		int nPos = pSlidCtrl->GetPos();				
		char str[100];
		sprintf(str,"%d",nPos);
		((CDlgVR*)GetDlgItem(IDC_TXT_SLICEPOSX))->SetWindowTextA(str);
		SetSliceX(nPos);
	}
	if(nID == IDC_SLIDERSLICEY)
	{
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDERSLICEY);	
		int nPos = pSlidCtrl->GetPos();				
		char str[100];
		sprintf(str,"%d",nPos);
		((CDlgVR*)GetDlgItem(IDC_TXT_SLICEPOSY))->SetWindowTextA(str);
		SetSliceY(nPos);	
	}
	if(nID == IDC_SLIDERSLICEZ)
	{
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDERSLICEZ);	
		int nPos = pSlidCtrl->GetPos();				
		char str[100];
		sprintf(str,"%d",nPos);
		((CDlgVR*)GetDlgItem(IDC_TXT_SLICEPOSZ))->SetWindowTextA(str);
		SetSliceZ(nPos);		
	}

	if(nID==IDC_WINDOWSLIDER ||nID==IDC_LEVELSLIDER )
	{
		int window = m_WindowSlider.GetPos();
		int level = m_LevelSlider.GetPos();
		char str[100];
		sprintf(str,"%d",window);
		((CDlgVR*)GetDlgItem(IDC_WINDOWTEXT))->SetWindowTextA(str);
		sprintf(str,"%d",level);
		((CDlgVR*)GetDlgItem(IDC_LEVELTEXT))->SetWindowTextA(str);
		SetXYZWindow((double)window,(double)level);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CDlgVR::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_SliderSliceX.SetTicFreq(1);	
	m_SliderSliceY.SetTicFreq(1);	
	m_SliderSliceZ.SetTicFreq(1);

	m_SlicePlayComb.AddString("XZ平面切片");
	m_SlicePlayComb.AddString("YZ平面切片");
	m_SlicePlayComb.AddString("XY平面切片");
	m_SlicePlayComb.SetCurSel(0);
	m_WindowSlider.SetTicFreq(1);
	m_LevelSlider.SetTicFreq(1);
	((CDlgVR*)GetDlgItem(IDC_WINDOWTEXT))->SetWindowTextA("0");
	((CDlgVR*)GetDlgItem(IDC_LEVELTEXT))->SetWindowTextA("0");	
	m_SlicePlayBtn.SetIcon(IDI_SLICEPLAY);
	m_VerticalMirrorBtn.SetIcon(IDI_VERMIRROR);
	m_VerticalMirrorBtn.SetAlign(CButtonST::ST_ALIGN_VERT);	
	m_HorizontalMirrorBtn.SetIcon(IDI_HORIMIRROR);
	m_HorizontalMirrorBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_TurnLeftBtn.SetIcon(IDI_TURNLEFT);
	m_TurnLeftBtn.SetAlign(CButtonST::ST_ALIGN_VERT);	
	m_TurnRightBtn.SetIcon(IDI_TURNRIGHT);
	m_TurnRightBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_AnistropyFilterBtn.SetIcon(IDI_ANISOTROPY);
	m_AnistropyFilterBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_GaussSmoothBtn.SetIcon(IDI_GAUSS);
	m_GaussSmoothBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_TemplateSetBtn.SetIcon(IDI_TEMPLATE);
	m_TemplateSetBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_MeanFilterBtn.SetIcon(IDI_MEDIAN);
	m_MeanFilterBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_EdgeDetectionBtn.SetIcon(IDI_EDGE);
	m_EdgeDetectionBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_SaveBmpBtn.SetIcon(IDI_SAVE);
	m_SaveBmpBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_binBtn.SetIcon(IDI_BINARY);
	m_binBtn.SetAlign(CButtonST::ST_ALIGN_VERT);	
	m_CaptureBtn.SetIcon(IDI_CAPTURE);	
	m_CaptureBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_SetWindowBtn.SetIcon(IDI_SETWINDOW);
	m_ResetWindowBtn.SetIcon(IDI_RESETWINDOW);



	((CButton*)GetDlgItem(IDC_ZXMAINPULATERADIO))->SetCheck(true);	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgVR::SetSliceX(int sliceindex)
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   	
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	if(data_fg==0)
		return;
	else
	{		
		pSliceView1->SetSliceX(sliceindex);		
		pSliceView1->SetLayerText(sliceindex);
	}	
}
void CDlgVR::SetSliceY(int sliceindex)
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd(); 	
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	if(data_fg==0)
		return;
	else
	{		
		pSliceView2->SetSliceY(sliceindex);		
		pSliceView2->SetLayerText(sliceindex);
	}	
}
void CDlgVR::SetSliceZ(int sliceindex)
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   	
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));

	if(data_fg==0)
		return;
	else
	{		
		pSliceView3->SetSliceZ(sliceindex);	
		pSliceView3->SetLayerText(sliceindex);
	}	
}

void CDlgVR::OnBnClickedSliceplaybtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg == 0)
		return;
	char buf[100];
	int nType = m_SlicePlayComb.GetCurSel();
	if(!m_Playfg)
	{
		((CDlgVR*)GetDlgItem(IDC_SLICEPLAYBTN))->SetWindowTextA("停止");
		m_Playfg = !m_Playfg;		
		SetTimer(0,200,NULL);
		m_SlicePlayBtn.SetIcon(IDI_STOPSLICEPLAY);
	}
	else
	{
		KillTimer(0);
		((CDlgVR*)GetDlgItem(IDC_SLICEPLAYBTN))->SetWindowTextA("播放");
		m_Playfg = !m_Playfg;	
		m_SlicePlayBtn.SetIcon(IDI_SLICEPLAY);
	}		
}


void CDlgVR::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nType = m_SlicePlayComb.GetCurSel();
	char buf[100];
	if(nType == 0)
	{
		if(m_SliderSliceX.GetPos() == SliceXNum)
		{
			
			((CDlgVR*)GetDlgItem(IDC_SLICEPLAYBTN))->SetWindowTextA("播放");
			m_Playfg = !m_Playfg;	
			m_SlicePlayBtn.SetIcon(IDI_SLICEPLAY);
			KillTimer(0);
		}
		else
		{
			int npos = m_SliderSliceX.GetPos()+1;
			m_SliderSliceX.SetPos(npos);
			SetSliceX(npos);
			sprintf(buf,"%d",(int)npos);
			((CDlgVR*)GetDlgItem(IDC_TXT_SLICEPOSX))->SetWindowTextA(buf);
		}
	}
	if(nType==1)
	{
		if(m_SliderSliceY.GetPos() == SliceYNum)
		{	
			((CDlgVR*)GetDlgItem(IDC_SLICEPLAYBTN))->SetWindowTextA("播放");
			m_Playfg = !m_Playfg;	
			m_SlicePlayBtn.SetIcon(IDI_SLICEPLAY);
			KillTimer(0);
		}
		else
		{
			int npos = m_SliderSliceY.GetPos()+1;	
			m_SliderSliceY.SetPos(npos);
			SetSliceY(npos);
			sprintf(buf,"%d",(int)npos);
			((CDlgVR*)GetDlgItem(IDC_TXT_SLICEPOSY))->SetWindowTextA(buf);
				
		}	
	}
	if(nType == 2)
	{
		if(m_SliderSliceZ.GetPos() == SliceZNum)
		{			
			((CDlgVR*)GetDlgItem(IDC_SLICEPLAYBTN))->SetWindowTextA("播放");
			m_Playfg = !m_Playfg;	
			m_SlicePlayBtn.SetIcon(IDI_SLICEPLAY);
			KillTimer(0);
		}
		else
		{			
			int npos = m_SliderSliceZ.GetPos()+1;	
			m_SliderSliceZ.SetPos(npos);	
			SetSliceZ(npos);
			sprintf(buf,"%d",(int)npos);
			((CDlgVR*)GetDlgItem(IDC_TXT_SLICEPOSZ))->SetWindowTextA(buf);					
		}	
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CDlgVR::SetXYZWindow(double window,double level)
{
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   	
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	if(data_fg==0)
		return;
	else
	{		
		pSliceView1->ChangeWindowLevel(window,level);	
		pSliceView2->ChangeWindowLevel(window,level);
		pSliceView3->ChangeWindowLevel(window,level);
	}	

}

void CDlgVR::OnBnClickedResetwinwdowlevelbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   	
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	if(data_fg==0)
		return;
	else
	{		
		pSliceView1->ChangeWindowLevel(Window,Level);	
		pSliceView2->ChangeWindowLevel(Window,Level);
		pSliceView3->ChangeWindowLevel(Window,Level);
		char buf[100];
		sprintf(buf,"%d",(int)Window);
		((CDlgVR*)GetDlgItem(IDC_WINDOWTEXT))->SetWindowTextA(buf);
		sprintf(buf,"%d",(int)Level);
		((CDlgVR*)GetDlgItem(IDC_LEVELTEXT))->SetWindowTextA(buf);
	}	
}


void CDlgVR::OnBnClickedSetwinwdowlevelbtn()
{
	// TODO: 在此添加控件通知处理程序代码

	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   	
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	if(data_fg==0)
		return;
	else
	{	
		char buf[100];
		((CDlgVR*)GetDlgItem(IDC_WINDOWTEXT))->GetWindowTextA(buf,100);
		int windowValue =  atoi(buf);
		((CDlgVR*)GetDlgItem(IDC_LEVELTEXT))->GetWindowTextA(buf,100);
		int LevelValue = atoi(buf);
		m_WindowSlider.SetPos(windowValue);
		m_LevelSlider.SetPos(LevelValue);
		pSliceView1->ChangeWindowLevel(windowValue,LevelValue);	
		pSliceView2->ChangeWindowLevel(windowValue,LevelValue);
		pSliceView3->ChangeWindowLevel(windowValue,LevelValue);
	}

}


void CDlgVR::OnBnClickedBkcolorslicex()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	if(data_fg==0)
		return;
	else
	{
		SLiceXBkRGB = m_SliceXBKColor.GetColor();
		BYTE rr = GetRValue(SLiceXBkRGB);
		BYTE gg = GetGValue(SLiceXBkRGB);
		BYTE bb = GetBValue(SLiceXBkRGB);
		float R = (float)rr / 255.0;
		float G  = (float)gg / 255.0;
		float B  = (float)bb / 255.0;
		pSliceView1->ChangeXBkColor(R,G,B);		
	}	
}


void CDlgVR::OnBnClickedBkcolorslicey()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	if(data_fg==0)
		return;
	else
	{
		SLiceYBkRGB = m_SliceYBKColor.GetColor();
		BYTE rr = GetRValue(SLiceYBkRGB);
		BYTE gg = GetGValue(SLiceYBkRGB);
		BYTE bb = GetBValue(SLiceYBkRGB);
		float R = (float)rr / 255.0;
		float G  = (float)gg / 255.0;
		float B  = (float)bb / 255.0;	
		pSliceView2->ChangeYBkColor(R,G,B);	
	}	
}


void CDlgVR::OnBnClickedBkcolorslicez()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	if(data_fg==0)
		return;
	else
	{
		SLiceZBkRGB = m_SliceZBKColor.GetColor();
		BYTE rr = GetRValue(SLiceZBkRGB);
		BYTE gg = GetGValue(SLiceZBkRGB);
		BYTE bb = GetBValue(SLiceZBkRGB);
		float R = (float)rr / 255.0;
		float G  = (float)gg / 255.0;
		float B  = (float)bb / 255.0;		
		pSliceView3->ChangeZBkColor(R,G,B);
	}	
}



void CDlgVR::OnBnClickedZxmainpulateradio()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PicMAinpulateRadioBtn = 0;
}


void CDlgVR::OnBnClickedYzmainpulateradio()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PicMAinpulateRadioBtn = 1;
}


void CDlgVR::OnBnClickedXymainpulateradio()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PicMAinpulateRadioBtn = 2;
}


void CDlgVR::OnBnClickedLeftrotation()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg==0)
		return;
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();  
	CMy3DVisualView *pView = (CMy3DVisualView*)(pFrame->m_splitWnd.GetPane(0,0));
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	switch (m_PicMAinpulateRadioBtn)
	{
	case 0:		
		pSliceView1->LeftRotation();	
			break;
	case 1:
		pSliceView2->LeftRotation();
		break;
	case 2:
		pSliceView3->LeftRotation();
		break;
	}
}


void CDlgVR::OnBnClickedRightrotation()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg==0)
		return;
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	switch (m_PicMAinpulateRadioBtn)
	{
	case 0:
		pSliceView1->RightRotation();
		break;
	case 1:
		pSliceView2->RightRotation();
		break;
	case 2:
		pSliceView3->RightRotation();
		break;
	}
}


void CDlgVR::OnBnClickedHorimirror()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg==0)
		return;
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	switch (m_PicMAinpulateRadioBtn)
	{
	case 0:
		pSliceView1->HoriMirror();
		break;
	case 1:
		pSliceView2->HoriMirror();
		break;
	case 2:
		pSliceView3->HoriMirror();
		break;
	}
}


void CDlgVR::OnBnClickedVertimirror()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg==0)
		return;
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	switch (m_PicMAinpulateRadioBtn)
	{
	case 0:
		pSliceView1->VertiMirror();			
		break;
	case 1:
		pSliceView2->VertiMirror();
		break;
	case 2:
		pSliceView3->VertiMirror();		
		break;
	}
}


void CDlgVR::OnBnClickedAnisotropyfilter()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg==0)
		return;
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	switch (m_PicMAinpulateRadioBtn)
	{
	case 0:
		pSliceView1->AnisotropyFilter(InteraNum,DiffThread);			
		break;
	case 1:
		pSliceView2->AnisotropyFilter(InteraNum,DiffThread);
		break;
	case 2:
		pSliceView3->AnisotropyFilter(InteraNum,DiffThread);		
		break;
	}
}


void CDlgVR::OnBnClickedGauss()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg==0)
		return;
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	switch (m_PicMAinpulateRadioBtn)
	{
	case 0:		
		pSliceView1->GaussSmooth(GaussTemplateSize,GaussTempltateSd);			
		break;
	case 1:
		pSliceView2->GaussSmooth(GaussTemplateSize,GaussTempltateSd);
		break;
	case 2:
		pSliceView3->GaussSmooth(GaussTemplateSize,GaussTempltateSd);		
		break;
	}
}

void CDlgVR::OnBnClickedTemplate()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgTemplate temdlg;	
	if(temdlg.DoModal() == IDOK)
	{		
		GaussTemplateSize = temdlg.m_GaussTemplate;
		GaussTempltateSd = temdlg.m_GaussSd;
		InteraNum =  temdlg.m_InteraNum;
		DiffThread = temdlg.m_DiffThread;
		BinValue = temdlg.m_BinaryValue;
	}
}


void CDlgVR::OnBnClickedMeanfilter()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg==0)
		return;
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	switch (m_PicMAinpulateRadioBtn)
	{
	case 0:		
		pSliceView1->MeanFilter();		
		break;
	case 1:
		pSliceView2->MeanFilter();
		break;
	case 2:
		pSliceView3->MeanFilter();		
		break;
	}
}


void CDlgVR::OnBnClickedEdgedetection()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg==0)
		return;
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	switch (m_PicMAinpulateRadioBtn)
	{
	case 0:		
		pSliceView1->EdgeDetection();		
		break;
	case 1:
		pSliceView2->EdgeDetection();
		break;
	case 2:
		pSliceView3->EdgeDetection();		
		break;
	}
}


void CDlgVR::OnBnClickedSavebmp()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg==0)
		return;	
	CDlgSaveSet dlg;
	if(dlg.DoModal())
	{
		m_SaveFolderName = dlg.m_strFolderPath;
		m_SaveFileName = dlg.m_SaveName;
		m_SaveFileRangeMin = dlg.m_SaveRangeMin;
		m_SaveFileRangeMax = dlg.m_SaveRangeMax;
	}
	else
		return;	
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   	
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	switch (m_PicMAinpulateRadioBtn)
	{
	case 0:		
		pSliceView1->WriteBmpX(m_SaveFolderName, m_SaveFileName,m_SaveFileRangeMin,m_SaveFileRangeMax);			
		break;
	case 1:
		pSliceView2->WriteBmpY(m_SaveFolderName, m_SaveFileName,m_SaveFileRangeMin,m_SaveFileRangeMax);
		break;
	case 2:
		pSliceView3->WriteBmpZ(m_SaveFolderName, m_SaveFileName,m_SaveFileRangeMin,m_SaveFileRangeMax);		
		break;
	}
}


void CDlgVR::OnBnClickedBinary()
{
	// TODO: 在此添加控件通知处理程序代码
	if(data_fg ==0)
		return;
	CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   	
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	switch (m_PicMAinpulateRadioBtn)
	{
	case 0:		
		pSliceView1->BinaryX(BinValue);			
		break;
	case 1:
		pSliceView2->BinaryY(BinValue);
		break;
	case 2:
		pSliceView3->BinaryZ(BinValue);
		break;
	}
}


void CDlgVR::OnBnClickedCapture()
{
	// TODO: 在此添加控件通知处理程序代码
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

	switch(m_PicMAinpulateRadioBtn)
	{
	case 0:
		pSliceView1->Capture(m_captureFolder,m_CaptureName);
		break;
	case 1:
		pSliceView2->Capture(m_captureFolder,m_CaptureName);
		break;
	case 2:
		pSliceView3->Capture(m_captureFolder,m_CaptureName);
		break;
	}
}
