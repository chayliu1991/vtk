// DlgSaveStlSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgSaveStlSet.h"
#include "afxdialogex.h"


// CDlgSaveStlSet �Ի���

IMPLEMENT_DYNAMIC(CDlgSaveStlSet, CDialogEx)

CDlgSaveStlSet::CDlgSaveStlSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSaveStlSet::IDD, pParent)
	, m_strFolder(_T("D:\\"))
	, m_strName(_T("ffout"))
{

}

CDlgSaveStlSet::~CDlgSaveStlSet()
{
}

void CDlgSaveStlSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STLFOLDER, m_strFolder);
	DDX_Text(pDX, IDC_STLNAME, m_strName);
	DDX_Control(pDX, IDC_STLSAVE, m_SaveStlBtn);
	DDX_Control(pDX, IDOK, m_StlSaveOK);
	DDX_Control(pDX, IDCANCEL, m_StlSaveCancel);
}


BEGIN_MESSAGE_MAP(CDlgSaveStlSet, CDialogEx)
	ON_BN_CLICKED(IDC_STLSAVE, &CDlgSaveStlSet::OnBnClickedStlsave)
END_MESSAGE_MAP()


// CDlgSaveStlSet ��Ϣ�������


void CDlgSaveStlSet::OnBnClickedStlsave()
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
		m_strFolder = szDisName;  
	}  
	UpdateData(false);
}


BOOL CDlgSaveStlSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_SaveStlBtn.SetIcon(IDI_DOCOPEN);
	m_StlSaveOK.SetIcon(IDI_DOCYES);
	m_StlSaveCancel.SetIcon(IDI_DOCNO);	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
