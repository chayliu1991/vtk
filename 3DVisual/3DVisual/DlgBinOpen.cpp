// DlgBinOpen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgBinOpen.h"
#include "afxdialogex.h"


// CDlgBinOpen �Ի���

IMPLEMENT_DYNAMIC(CDlgBinOpen, CDialogEx)

CDlgBinOpen::CDlgBinOpen(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBinOpen::IDD, pParent)	
	, m_BinWidth(1024)
	, m_BinHeight(1024)
	, m_binStartNum(0)
	, m_binEndNum(0)
	, m_fBinsample(0.5)
	, m_fbinSpaceX(1)
	, m_fbinSpaceY(1)
	, m_fbinSpaceZ(1)
{
	 m_BinFolderName = "";
}

CDlgBinOpen::~CDlgBinOpen()
{
}

void CDlgBinOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BMPLIST, m_BinStackList);
	DDX_Text(pDX, IDC_BMPWIDTH, m_BinWidth);
	DDX_Text(pDX, IDC_BMPHEIGHT, m_BinHeight);
	DDX_Text(pDX, IDC_BMPSTARTNUM, m_binStartNum);
	DDX_Text(pDX, IDC_BMPENDNUM, m_binEndNum);
	DDX_Text(pDX, IDC_BMPSAMPLE, m_fBinsample);
	DDX_Text(pDX, IDC_BMPSPACEX, m_fbinSpaceX);
	DDX_Text(pDX, IDC_BMPSPACEY, m_fbinSpaceY);
	DDX_Text(pDX, IDC_BMPSPACEZ, m_fbinSpaceZ);
}


BEGIN_MESSAGE_MAP(CDlgBinOpen, CDialogEx)

	ON_BN_CLICKED(IDC_BTNBINOPEN, &CDlgBinOpen::OnBnClickedBtnbinopen)
END_MESSAGE_MAP()


// CDlgBinOpen ��Ϣ�������


BOOL CDlgBinOpen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BinStackList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_BinStackList.InsertColumn(0, _T("ѡ���ļ�"));
	m_BinStackList.SetColumnWidth(0, 400);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgBinOpen::OnBnClickedBtnbinopen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString FilePathName = "";
	CString FolderName = "";

	CFileDialog fileDlg( TRUE, NULL, NULL,OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY,
		(LPCTSTR)_TEXT("BIN Files (*.bin)|*.bin||"),NULL );

	const int MIN_FILE_NUMBER = 1000;     //��������ѡ��1000���ļ�
	fileDlg.m_ofn.lpstrFile = new TCHAR[_MAX_PATH * MIN_FILE_NUMBER]; //���¶��建������С          
	memset(fileDlg.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //��ʼ������Ļ�����
	fileDlg.m_ofn.nMaxFile = _MAX_PATH * MIN_FILE_NUMBER;
	bool firstfilefg = false;
	if(fileDlg.DoModal()==IDOK)
	{
		POSITION pos_file;
		pos_file = fileDlg.GetStartPosition();
		FolderName =fileDlg.GetFolderPath();
		((CDlgBinOpen *)GetDlgItem(IDC_BINFOLDER_EDIT))->SetWindowText(FolderName);
		while (pos_file != NULL)
		{
			FilePathName = fileDlg.GetNextPathName(pos_file);	
			m_BinStackList.InsertItem(m_BinStackList.GetItemCount(), FilePathName);
		}	
		m_BinFolderName = FolderName;
	}
	else
		return;
	delete[] fileDlg.m_ofn.lpstrFile;    
}
