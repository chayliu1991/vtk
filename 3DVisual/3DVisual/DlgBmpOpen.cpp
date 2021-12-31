// DlgBmpOpen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgBmpOpen.h"
#include "afxdialogex.h"


// CDlgBmpOpen �Ի���

IMPLEMENT_DYNAMIC(CDlgBmpOpen, CDialogEx)

CDlgBmpOpen::CDlgBmpOpen(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBmpOpen::IDD, pParent)	
	, m_BmpWidth(1024)
	, m_BmpHeight(1024)
	, m_bmpStartNum(322)
	, m_bmpEndNum(365)
	, m_fsample(0.5)
	, m_fbmpSpaceX(1)
	, m_fbmpSpaceY(1)
	, m_fbmpSpaceZ(1)
{
	m_BmpFolderName ="";

}

CDlgBmpOpen::~CDlgBmpOpen()
{
}

void CDlgBmpOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BMPLIST, m_BmpStackList);	
	DDX_Text(pDX, IDC_BMPWIDTH, m_BmpWidth);
	DDX_Text(pDX, IDC_BMPHEIGHT, m_BmpHeight);
	DDX_Text(pDX, IDC_BMPSTARTNUM, m_bmpStartNum);
	DDV_MinMaxInt(pDX, m_bmpStartNum, 0, 999);
	DDX_Text(pDX, IDC_BMPENDNUM, m_bmpEndNum);
	DDV_MinMaxInt(pDX, m_bmpEndNum, 0, 999);
	DDX_Text(pDX, IDC_BMPSAMPLE, m_fsample);
	DDX_Text(pDX, IDC_BMPSPACEX, m_fbmpSpaceX);
	DDX_Text(pDX, IDC_BMPSPACEY, m_fbmpSpaceY);
	DDX_Text(pDX, IDC_BMPSPACEZ, m_fbmpSpaceZ);
	DDX_Control(pDX, IDC_BTNBMPOPEN, m_BmpOpenBtn);
	DDX_Control(pDX, IDOK, m_DocYesBtn);
	DDX_Control(pDX, IDCANCEL, m_DocNoBtn);
}


BEGIN_MESSAGE_MAP(CDlgBmpOpen, CDialogEx)
	ON_BN_CLICKED(IDC_BTNBMPOPEN, &CDlgBmpOpen::OnBnClickedBtnbmpopen)
END_MESSAGE_MAP()


// CDlgBmpOpen ��Ϣ�������


BOOL CDlgBmpOpen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BmpStackList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_BmpStackList.InsertColumn(0, _T("ѡ���ļ�"));
	m_BmpStackList.SetColumnWidth(0, 400);

	m_BmpOpenBtn.SetIcon(IDI_DOCOPEN);
	m_DocYesBtn.SetIcon(IDI_DOCYES);
	m_DocNoBtn.SetIcon(IDI_DOCNO);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgBmpOpen::OnBnClickedBtnbmpopen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString FilePathName = "";
	CString FolderName = "";
	
	CFileDialog fileDlg( TRUE, NULL, NULL,OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY,
		(LPCTSTR)_TEXT("BMP Files (*.bmp)|*.bmp||"),NULL );

	const int MIN_FILE_NUMBER = 2000;     //��������ѡ��1000���ļ�
	fileDlg.m_ofn.lpstrFile = new TCHAR[_MAX_PATH * MIN_FILE_NUMBER]; //���¶��建������С          
	memset(fileDlg.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //��ʼ������Ļ�����
	fileDlg.m_ofn.nMaxFile = _MAX_PATH * MIN_FILE_NUMBER;
	bool firstfilefg = false;
	if(fileDlg.DoModal()==IDOK)
	{
		POSITION pos_file;
		pos_file = fileDlg.GetStartPosition();
		FolderName =fileDlg.GetFolderPath();
		((CDlgBmpOpen *)GetDlgItem(IDC_BMPFOLDER_EDIT))->SetWindowText(FolderName);
		while (pos_file != NULL)
		{
			FilePathName = fileDlg.GetNextPathName(pos_file);	
			m_BmpStackList.InsertItem(m_BmpStackList.GetItemCount(), FilePathName);
		}	
		m_BmpFolderName = FolderName;
	}
	else
		return;
	delete[] fileDlg.m_ofn.lpstrFile;     
}
