// DlgSaveSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgSaveSet.h"
#include "afxdialogex.h"


// CDlgSaveSet �Ի���

IMPLEMENT_DYNAMIC(CDlgSaveSet, CDialogEx)

CDlgSaveSet::CDlgSaveSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSaveSet::IDD, pParent)
	, m_SaveName(_T("Slice"))
	, m_SaveRangeMin(0)
	, m_SaveRangeMax(0)
	, m_strFolderPath(_T("D:\\"))
{

}

CDlgSaveSet::~CDlgSaveSet()
{
}

void CDlgSaveSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SAVENAME, m_SaveName);
	DDX_Text(pDX, IDC_SAVERANGEMIN, m_SaveRangeMin);
	DDX_Text(pDX, IDC_SAVERANGEMAX, m_SaveRangeMax);
	DDX_Text(pDX, IDC_FILEFOLDER, m_strFolderPath);
	DDX_Control(pDX, IDC_SAVEFOLDERSELECT, m_SAveBmpBtn);
	DDX_Control(pDX, IDOK, m_SAveBmpOKBtn);
	DDX_Control(pDX, IDCANCEL, m_SAveBmpCancelBtn);
}


BEGIN_MESSAGE_MAP(CDlgSaveSet, CDialogEx)
	ON_BN_CLICKED(IDC_SAVEFOLDERSELECT, &CDlgSaveSet::OnBnClickedSavefolderselect)
END_MESSAGE_MAP()


// CDlgSaveSet ��Ϣ�������

void CDlgSaveSet::OnBnClickedSavefolderselect()
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
		m_strFolderPath = szDisName;  
	}  
	UpdateData(false);
}


BOOL CDlgSaveSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_SAveBmpBtn.SetIcon(IDI_DOCOPEN);
	m_SAveBmpOKBtn.SetIcon(IDI_DOCYES);
	m_SAveBmpCancelBtn.SetIcon(IDI_DOCNO);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
