// DlgCaptureSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgCaptureSet.h"
#include "afxdialogex.h"


// CDlgCaptureSet �Ի���

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


// CDlgCaptureSet ��Ϣ�������


void CDlgCaptureSet::OnBnClickedCapturebtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BROWSEINFO broInfo = {0};  
	TCHAR       szDisName[MAX_PATH] = {0};  

	broInfo.hwndOwner = this->m_hWnd;  
	broInfo.pidlRoot  = NULL;  
	broInfo.pszDisplayName = szDisName;  
	broInfo.lpszTitle = _T("ѡ�񱣴�·��");  
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	 m_CapturePathBtn.SetIcon(IDI_DOCOPEN);
	 m_CaptureOKBtn.SetIcon(IDI_DOCYES);
	 m_CaptureCancelBtn.SetIcon(IDI_DOCNO);	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
