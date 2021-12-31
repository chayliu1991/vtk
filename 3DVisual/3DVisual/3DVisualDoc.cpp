
// 3DVisualDoc.cpp : CMy3DVisualDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "3DVisual.h"
#endif

#include "MainFrm.h"
#include "3DVisualDoc.h"
#include "3DVisualView.h"
#include "DlgDicomOpen.h"
#include "DlgBmpOpen.h"
#include "DlgBinOpen.h"
#include "BttmView.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy3DVisualDoc

IMPLEMENT_DYNCREATE(CMy3DVisualDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy3DVisualDoc, CDocument)
	ON_COMMAND(ID_DICOMOPEN, &CMy3DVisualDoc::OnDicomopen)
	ON_COMMAND(ID_BMPOPEN, &CMy3DVisualDoc::OnBmpopen)
	ON_COMMAND(ID_BINOPEN, &CMy3DVisualDoc::OnBinopen)
END_MESSAGE_MAP()

//////////////////////////////
UINT data_fg = 0;//标志是否读入数据以及数据的类型,等于0时表示当前无数据

// CMy3DVisualDoc 构造/析构

//定义全局变量标志使用数据源的类型
bool Dicom_fg = false;
bool Bmp_fg = false;

CMy3DVisualDoc::CMy3DVisualDoc()
{
	// TODO: 在此添加一次性构造代码
	Dicomreader = NULL;
	samplevalue = 0;
}

CMy3DVisualDoc::~CMy3DVisualDoc()
{
}

BOOL CMy3DVisualDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle(_T("Volume"));
	return TRUE;
}




// CMy3DVisualDoc 序列化

void CMy3DVisualDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMy3DVisualDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMy3DVisualDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMy3DVisualDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy3DVisualDoc 诊断

#ifdef _DEBUG
void CMy3DVisualDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy3DVisualDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy3DVisualDoc 命令


void CMy3DVisualDoc::OnDicomopen()
{
	// TODO: 在此添加命令处理程序代码
	CDlgDicomOpen m_DlgDicomImport;
	if(m_DlgDicomImport.DoModal() == IDOK)
	{
		Dicomreader =  vtkSmartPointer<vtkDICOMImageReader>::New(); 
		Dicomreader->SetDirectoryName(m_DlgDicomImport.m_DicomFolderName);
		Dicomreader->Update();			
		data_fg = 1;//等于1时表示当前的数据类型为Dicom
		Dicom_fg = true;
		Bmp_fg = false;
		SetDicomSlice();
		InitSliceDlg();
	}
	else
		return;
}
void CMy3DVisualDoc::SetDicomSlice()
{
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();  
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	pSliceView1->DisplaySlice1((vtkDataSet*)Dicomreader->GetOutput());
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	pSliceView2->DisplaySlice2((vtkDataSet*)Dicomreader->GetOutput());
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	pSliceView3->DisplaySlice3((vtkDataSet*)Dicomreader->GetOutput());
}


void CMy3DVisualDoc::OnBmpopen()
{
	// TODO: 在此添加命令处理程序代码
	CDlgBmpOpen m_DlgBmpImport;
	if(m_DlgBmpImport.DoModal() == IDOK)
	{
		Bmpreader =  vtkSmartPointer<vtkBMPReader>::New();	
		CString fileprefix = m_DlgBmpImport.m_BmpFolderName + "\\FDK_Slice_";		
		Bmpreader->SetFilePrefix(fileprefix);
		int stnum = m_DlgBmpImport.m_bmpStartNum;
		int ednum = m_DlgBmpImport.m_bmpEndNum;
		int width = m_DlgBmpImport.m_BmpWidth-1;
		int height = m_DlgBmpImport.m_BmpHeight-1;
		float xspace = m_DlgBmpImport.m_fbmpSpaceX;
		float yspace = m_DlgBmpImport.m_fbmpSpaceY;
		float zspace = m_DlgBmpImport.m_fbmpSpaceZ;
		samplevalue = m_DlgBmpImport.m_fsample;
		Bmpreader->SetFilePattern("%s%04d.BMP");	
		Bmpreader->SetDataExtent(0,width,0,height,stnum,ednum);
		Bmpreader->SetDataSpacing(xspace,yspace,zspace);	
		Bmpreader->SetAllow8BitBMP(8);	
		Bmpreader->Update();
		data_fg = 2;//等于2时表示当前的数据类型为bmp
		Dicom_fg = false;
		Bmp_fg = true;
		SetBmpSlice();
		InitSliceDlg();
	}
	else
		return;
}

void CMy3DVisualDoc::SetBmpSlice()
{
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();  
	CBttmView* pBtmview = (CBttmView*)(pFrame->m_splitWnd.GetPane(1,0));
	CBttmOneView* pSliceView1 = (CBttmOneView*)(pBtmview->m_splitWnd2.GetPane(0,0));
	pSliceView1->DisplaySlice1((vtkDataSet*)Bmpreader->GetOutput());
	CBttmTwoView* pSliceView2 = (CBttmTwoView*)(pBtmview->m_splitWnd2.GetPane(0,1));
	pSliceView2->DisplaySlice2((vtkDataSet*)Bmpreader->GetOutput());
	CBttmThreeView* pSliceView3 = (CBttmThreeView*)(pBtmview->m_splitWnd2.GetPane(0,2));
	pSliceView3->DisplaySlice3((vtkDataSet*)Bmpreader->GetOutput());
}

void CMy3DVisualDoc::InitSliceDlg()
{
	CMainFrame * pFram = (CMainFrame*)AfxGetMainWnd();
	pFram->m_toolpane.m_paneDlg.InitSliceSlider();		
}

void CMy3DVisualDoc::OnBinopen()
{
	// TODO: 在此添加命令处理程序代码
	CDlgBinOpen m_DlgBinImport;
	if(m_DlgBinImport.DoModal() == IDOK)
	{
		
	Binreader = vtkImageReader::New();	
	CString fileprefix = m_DlgBinImport.m_BinFolderName + "\\FDK_Slice_0";
	Binreader->SetFilePrefix(fileprefix);
	int stnum = m_DlgBinImport.m_binStartNum;
	int ednum = m_DlgBinImport.m_binEndNum;
	int width = m_DlgBinImport.m_BinWidth-1;
	int height = m_DlgBinImport.m_BinHeight-1;
	float xspace = m_DlgBinImport.m_fbinSpaceX;
	float yspace = m_DlgBinImport.m_fbinSpaceY;
	float zspace = m_DlgBinImport.m_fbinSpaceZ;
	samplevalue = m_DlgBinImport.m_fBinsample;
	Binreader->SetFilePattern("%s%03d.bin");	
	Binreader->SetDataExtent(0,width,0,height,stnum,ednum);
	Binreader->SetDataSpacing(xspace,yspace,zspace);	
	Binreader->Update();
	data_fg = 3;//等于2时表示当前的数据类型为bmp	
	//SetBmpSlice();
	//InitSliceDlg();
	}
	else
		return;
}
