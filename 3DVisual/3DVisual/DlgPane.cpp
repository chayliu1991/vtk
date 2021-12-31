// DlgPane.cpp : 实现文件
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgPane.h"
#include "afxdialogex.h"



/////////////////////////////
extern int SliceXNum;
extern int SliceYNum;
extern int SliceZNum;
extern double Window;
extern double Level;
extern UINT data_fg;

// CDlgPane 对话框

IMPLEMENT_DYNAMIC(CDlgPane, CDialogEx)

CDlgPane::CDlgPane(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPane::IDD, pParent)
{

}

CDlgPane::~CDlgPane()
{
}

void CDlgPane::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PANETAB, m_paneTab);
}


BEGIN_MESSAGE_MAP(CDlgPane, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_PANETAB, &CDlgPane::OnTcnSelchangePanetab)
END_MESSAGE_MAP()


// CDlgPane 消息处理程序


BOOL CDlgPane::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_paneTab.InsertItem(0, _T("可视化"));
	m_paneTab.InsertItem(1, _T("图像处理"));
	m_dlgvr.Create(IDD_DLG_VR, &m_paneTab);
	m_dlgmc.Create(IDD_DLG_MC, &m_paneTab);
	m_paneTab.GetClientRect(&tabRect);    // 获取标签控件客户区Rect   
	// 调整tabRect，使其覆盖范围适合放置标签页   
	tabRect.left += 1;
	tabRect.right -= 3;
	tabRect.top += 21;
	tabRect.bottom -= 2;
	m_dlgvr.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_dlgmc.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW );
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgPane::OnTcnSelchangePanetab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	switch (m_paneTab.GetCurSel())
	{
	case 0:
		m_dlgvr.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_dlgmc.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW );
		break;
	case 1:
		m_dlgvr.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW );
		m_dlgmc.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	default:
		break;
	}
}


void CDlgPane::InitSliceSlider()
{
	char str[100];		
	m_dlgvr.m_SliderSliceX.SetRange(0,SliceXNum);
	m_dlgvr.m_SliderSliceX.SetPos(SliceXNum/2);
	m_dlgvr.m_SliderSliceY.SetRange(0,SliceYNum);
	m_dlgvr.m_SliderSliceY.SetPos(SliceYNum/2);
	m_dlgvr.m_SliderSliceZ.SetRange(0,SliceZNum);
	m_dlgvr.m_SliderSliceZ.SetPos(SliceZNum/2);
	sprintf(str,"%d",SliceXNum);
	m_dlgvr.GetDlgItem(IDC_TXT_SLICEENDX)->SetWindowTextA(str);
	sprintf(str,"%d",SliceYNum);
	m_dlgvr.GetDlgItem(IDC_TXT_SLICEENDY)->SetWindowTextA(str);
	sprintf(str,"%d",SliceZNum);
	m_dlgvr.GetDlgItem(IDC_TXT_SLICEENDZ)->SetWindowTextA(str);	
	sprintf(str,"%d",SliceXNum/2);
	m_dlgvr.GetDlgItem(IDC_TXT_SLICEPOSX)->SetWindowTextA(str);
	sprintf(str,"%d",SliceYNum/2);
	m_dlgvr.GetDlgItem(IDC_TXT_SLICEPOSY)->SetWindowTextA(str);
	sprintf(str,"%d",SliceZNum/2);
	m_dlgvr.GetDlgItem(IDC_TXT_SLICEPOSZ)->SetWindowTextA(str);
	switch(data_fg)
	{
	case 0:
		break;
	case 1:
		m_dlgvr.m_WindowSlider.SetRange(0,65535);
		m_dlgvr.m_LevelSlider.SetRange(0,65535);
		m_dlgvr.m_WindowSlider.SetPos(Window);
		m_dlgvr.m_LevelSlider.SetPos(Level);
		sprintf(str,"%.0d",(int)Window);
		m_dlgvr.GetDlgItem(IDC_WINDOWTEXT)->SetWindowTextA(str);
		sprintf(str,"%.0d",(int)Level);
		m_dlgvr.GetDlgItem(IDC_LEVELTEXT)->SetWindowTextA(str);
		break;
	case 2:
		m_dlgvr.m_WindowSlider.SetRange(0,255);
		m_dlgvr.m_LevelSlider.SetRange(0,255);
		m_dlgvr.m_WindowSlider.SetPos(Window);
		m_dlgvr.m_LevelSlider.SetPos(Level);
		sprintf(str,"%.d",(int)Window);
		m_dlgvr.GetDlgItem(IDC_WINDOWTEXT)->SetWindowTextA(str);
		sprintf(str,"%.d",(int)Level);
		m_dlgvr.GetDlgItem(IDC_LEVELTEXT)->SetWindowTextA(str);

	}
	m_dlgvr.SetXYZWindow(Window,Level);
}