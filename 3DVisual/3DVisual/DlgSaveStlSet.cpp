// DlgSaveStlSet.cpp : 实现文件
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgSaveStlSet.h"
#include "afxdialogex.h"


// CDlgSaveStlSet 对话框

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


// CDlgSaveStlSet 消息处理程序


void CDlgSaveStlSet::OnBnClickedStlsave()
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
		m_strFolder = szDisName;  
	}  
	UpdateData(false);
}


BOOL CDlgSaveStlSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_SaveStlBtn.SetIcon(IDI_DOCOPEN);
	m_StlSaveOK.SetIcon(IDI_DOCYES);
	m_StlSaveCancel.SetIcon(IDI_DOCNO);	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
