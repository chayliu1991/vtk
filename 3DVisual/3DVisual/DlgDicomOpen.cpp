// DlgDicomOpen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgDicomOpen.h"
#include "afxdialogex.h"


// CDlgDicomOpen �Ի���

IMPLEMENT_DYNAMIC(CDlgDicomOpen, CDialogEx)

CDlgDicomOpen::CDlgDicomOpen(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDicomOpen::IDD, pParent)
{
	m_DicomFolderName = "";
}

CDlgDicomOpen::~CDlgDicomOpen()
{
}

void CDlgDicomOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DICOMLIST, m_DicomStackList);
	DDX_Control(pDX, IDC_BTNDICOMOPEN, m_DocOpenBtn);
	DDX_Control(pDX, IDOK, m_DocYesBtn);
	DDX_Control(pDX, IDCANCEL, m_DocNoBtn);
}


BEGIN_MESSAGE_MAP(CDlgDicomOpen, CDialogEx)
	ON_BN_CLICKED(IDC_BTNDICOMOPEN, &CDlgDicomOpen::OnBnClickedBtndicomopen)
END_MESSAGE_MAP()


// CDlgDicomOpen ��Ϣ�������


BOOL CDlgDicomOpen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_DicomStackList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_DicomStackList.InsertColumn(0, _T("ѡ���ļ�"));
	m_DicomStackList.SetColumnWidth(0, 400);
	m_DocOpenBtn.SetIcon(IDI_DOCOPEN);
	m_DocYesBtn.SetIcon(IDI_DOCYES);
	m_DocNoBtn.SetIcon(IDI_DOCNO);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgDicomOpen::OnBnClickedBtndicomopen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString FilePathName = "";
	CString FolderName = "";
	CFileDialog fileDlg( TRUE, NULL, NULL,OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY,
		(LPCTSTR)_TEXT("DICOM Files (*.dcm)|*.dcm||"),NULL );

	const int MIN_FILE_NUMBER = 2000;     
	fileDlg.m_ofn.lpstrFile = new TCHAR[_MAX_PATH * MIN_FILE_NUMBER]; //���¶��建������С          
	memset(fileDlg.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //��ʼ������Ļ�����
	fileDlg.m_ofn.nMaxFile = _MAX_PATH * MIN_FILE_NUMBER;

	if(fileDlg.DoModal()==IDOK)
	{
		POSITION pos_file;
		pos_file = fileDlg.GetStartPosition();
		FolderName =fileDlg.GetFolderPath();
		((CDlgDicomOpen *)GetDlgItem(IDC_DICOMFOLDER_EDIT))->SetWindowText(FolderName);
		while (pos_file != NULL)
		{
			FilePathName = fileDlg.GetNextPathName(pos_file);	
			m_DicomStackList.InsertItem(m_DicomStackList.GetItemCount(), FilePathName);
		}	
		m_DicomFolderName = FolderName;
	}
	else
		return;

	delete[] fileDlg.m_ofn.lpstrFile;     
}
