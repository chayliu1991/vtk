// DlgTemplate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DVisual.h"
#include "DlgTemplate.h"
#include "afxdialogex.h"

extern int GaussTemplateSize;
extern float GaussTempltateSd;
extern int InteraNum;
extern double DiffThread;
extern int BinValue;

// CDlgTemplate �Ի���

IMPLEMENT_DYNAMIC(CDlgTemplate, CDialogEx)

CDlgTemplate::CDlgTemplate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTemplate::IDD, pParent)
{

}

CDlgTemplate::~CDlgTemplate()	
{
}

void CDlgTemplate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GAUSSTEMPLATE, m_GaussTemplate);
	DDX_Text(pDX, IDC_GAUSSSD, m_GaussSd);
	DDX_Text(pDX, IDC_NUMTERA, m_InteraNum);
	DDX_Text(pDX, IDC_DIFFTHREAD, m_DiffThread);
	DDX_Text(pDX, IDC_BINARYVALUEEDIT, m_BinaryValue);
	DDV_MinMaxInt(pDX, m_BinaryValue, 0, 255);
}


BEGIN_MESSAGE_MAP(CDlgTemplate, CDialogEx)
END_MESSAGE_MAP()


// CDlgTemplate ��Ϣ�������


BOOL CDlgTemplate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_GaussTemplate = GaussTemplateSize;
	m_GaussSd = GaussTempltateSd;
	m_InteraNum  = InteraNum;
	m_DiffThread = DiffThread;
	m_BinaryValue = BinValue;
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
