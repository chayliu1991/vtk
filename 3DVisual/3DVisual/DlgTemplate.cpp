// DlgTemplate.cpp : 实现文件
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

// CDlgTemplate 对话框

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


// CDlgTemplate 消息处理程序


BOOL CDlgTemplate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_GaussTemplate = GaussTemplateSize;
	m_GaussSd = GaussTempltateSd;
	m_InteraNum  = InteraNum;
	m_DiffThread = DiffThread;
	m_BinaryValue = BinValue;
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
