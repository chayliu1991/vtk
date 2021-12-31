// DlgCaptureSet.cpp : 实现文件
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgCaptureSet.h"
#include "afxdialogex.h"


// CDlgCaptureSet 对话框

IMPLEMENT_DYNAMIC(CDlgCaptureSet, CDialogEx)

CDlgCaptureSet::CDlgCaptureSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCaptureSet::IDD, pParent)
	, m_strCaptureFolderPath(_T("D:\\"))
	, m_CaptureName(_T("Capture"))
{

}

CDlgCaptureSet::~CDlgCaptureSet()
{
}

void CDlgCaptureSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CAPTUREFOLDER, m_strCaptureFolderPath);
	DDX_Text(pDX, IDC_CAPTURENAME, m_CaptureName);
	DDX_Control(pDX, IDC_CAPTUREBTN, m_CapturePathBtn);
	DDX_Control(pDX, IDOK, m_CaptureOKBtn);
	DDX_Control(pDX, IDCANCEL, m_CaptureCancelBtn);
}


BEGIN_MESSAGE_MAP(CDlgCaptureSet, CDialogEx)
	ON_BN_CLICKED(IDC_CAPTUREBTN, &CDlgCaptureSet::OnBnClickedCapturebtn)
END_MESSAGE_MAP()


// CDlgCaptureSet 消息处理程序


void CDlgCaptureSet::OnBnClickedCapturebtn()
{
	// TODO: 在此添加控件通知处理程序代码
	BROWSEINFO broInfo = {0};  
	TCHAR       szDisName[MAX_PATH] = {0};  

	broInfo.hwndOwner = this->m_hWnd;  
	broInfo.pidlRoot  = NULL;  
	broInfo.pszDisplayName = szDisName;  
	broInfo.lpszTitle = _T("选择保存路径");  
	broInfo.ulFlags   = BIF_NEWDIALOGSTYLE | BIF_DONTGOBELOWDOMAIN  
		| BIF_BROWSEFORCOMPUTER | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;  
	broInfo.lpfn      = NULL;  
	broInfo.lParam    = NULL;  
	broInfo.iImage    = IDR_MAINFRAME;  

	LPITEMIDLIST pIDList = SHBrowseForFolder(&broInfo);  
	if (pIDList != NULL)  
	{  
		memset(szDisName, 0, sizeof(szDisName));  
		SHGetPathFromIDList(pIDList, szDisName);  
		m_strCaptureFolderPath = szDisName;  
	}  
	UpdateData(false);
}


BOOL CDlgCaptureSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	 m_CapturePathBtn.SetIcon(IDI_DOCOPEN);
	 m_CaptureOKBtn.SetIcon(IDI_DOCYES);
	 m_CaptureCancelBtn.SetIcon(IDI_DOCNO);	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
