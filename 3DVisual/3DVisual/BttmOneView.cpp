// BttmOneView.cpp : 实现文件
//

#include "stdafx.h"
#include "3DVisual.h"
#include "BttmOneView.h"
#include <vtkInteractorStyleImage.h>
#include "MainFrm.h"
#include "3DVisualDoc.h"
#include <vtkDICOMImageReader.h>
#include "vtkLookupTable.h"
#include "vtkCamera.h"
#include "vtkImageAnisotropicDiffusion2D.h"
#include "vtkImageHybridMedian2D.h"
#include "vtkImageGaussianSmooth.h"
#include "vtkImageConvolve.h"
#include "vtkImageCast.h"
#include "vtkImageGradient.h"
#include "vtkImageMagnitude.h"
#include "vtkImageShiftScale.h"
#include "vtkTIFFReader.h"
#include "vtkTIFFWriter.h"

#include "vtkImageAccumulate.h"
#include "vtkXYPlotActor.h"
#include "vtkBarChartActor.h"
#include "DlgCaptureSet.h"
#include "vtkWindowToImageFilter.h"
#include "vtkImageThreshold.h"



// CBttmOneView
///////////////////////////////
////////////////////
int SliceXNum = 0;
double Window = 0.0;
double Level = 0.0;
IMPLEMENT_DYNCREATE(CBttmOneView, CView)

CBttmOneView::CBttmOneView()
{
	m_backgroundColor = RGB(0, 0, 0);	
	m_frontgroundColor = RGB(0,0, 255);
	mfcWinSlice1 = NULL;
	m_SliceRender1 = vtkRenderer::New();//创建绘制者		
	m_SliceActor1 = vtkImageActor::New();//建立一个代表皮肤的演员
	colorMap1 = vtkImageMapToColors::New();
	planeWight1 = vtkImagePlaneWidget::New();
	ipwProp1 = vtkProperty::New();
	planeWight1->SetKeyPressActivationValue('x');
	planeWight1->RestrictPlaneToVolumeOn();
	planeWight1->GetPlaneProperty()->SetColor(1,0,0);
	planeWight1->SetTexturePlaneProperty(ipwProp1);
	planeWight1->SetResliceInterpolateToNearestNeighbour();	
	planeWight1->DisplayTextOn();
	colorMap1->PassAlphaToOutputOff();
	colorMap1->SetActiveComponent(0);
	colorMap1->SetOutputFormatToLuminance();
	sliceXTextProp = vtkTextProperty::New();
	sliceXTextProp->SetFontFamilyToCourier();
	sliceXTextProp->SetFontSize(16);
	sliceXTextProp->SetVerticalJustificationToBottom();
	sliceXTextProp->SetJustificationToLeft();
	sliceXTextMapper1 = vtkTextMapper::New();	
	sliceXTextMapper1->SetTextProperty(sliceXTextProp);
	sliceXTextActor1 = vtkActor2D::New();
	sliceXTextActor1->SetMapper(sliceXTextMapper1);
	sliceXTextActor1->SetPosition(5,25);
	sliceXTextMapper2 = vtkTextMapper::New();	
	sliceXTextMapper2->SetTextProperty(sliceXTextProp);
	sliceXTextActor2 = vtkActor2D::New();
	sliceXTextActor2->SetMapper(sliceXTextMapper2);
	sliceXTextActor2->SetPosition(5, 5);
}

CBttmOneView::~CBttmOneView()
{
	if (mfcWinSlice1)
		delete mfcWinSlice1;
}

BEGIN_MESSAGE_MAP(CBttmOneView, CView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_ZOXCAPTURE, &CBttmOneView::OnZoxcapture)
END_MESSAGE_MAP()


// CBttmOneView 绘图

void CBttmOneView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
	CRect rc;
	GetClientRect(&rc);
	CBrush br(m_backgroundColor);
	pDC->FillRect(&rc,&br);	
	pDC->Draw3dRect(rc, m_frontgroundColor, m_frontgroundColor);
	rc.DeflateRect(1, 1);
	pDC->Draw3dRect(rc, m_frontgroundColor, m_frontgroundColor);
}

// CBttmOneView 诊断
#ifdef _DEBUG
void CBttmOneView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBttmOneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBttmOneView 消息处理程序
void CBttmOneView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class	
	mfcWinSlice1 = new vtkMFCWindow(this);
	mfcWinSlice1->SetXYZ();
	(mfcWinSlice1->GetRenderWindow())->SetPosition(2,2);
	CRect rect;
	GetClientRect(&rect);
	(mfcWinSlice1->GetRenderWindow())->SetSize(rect.Width()-5,rect.Height()-5);
	mfcWinSlice1->GetRenderWindow()->AddRenderer(m_SliceRender1);
	
}


void CBttmOneView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	if(m_SliceRender1)
		m_SliceRender1->Delete();
	if(m_SliceActor1)
		m_SliceActor1->Delete();
	if(colorMap1)
		colorMap1->Delete();	
	if(planeWight1)
		planeWight1->Delete();	
	if(ipwProp1)
		ipwProp1->Delete();
	if(sliceXTextProp)
		sliceXTextProp->Delete();
	if(sliceXTextMapper1)
		sliceXTextMapper1->Delete();
	if(sliceXTextActor1)
		sliceXTextActor1->Delete();
}

void CBttmOneView::DisplaySlice1(vtkDataSet* input)
{
	//planeWight1->SetInput(input);
	//planeWight1->SetPlaneOrientation(0);
	//colorMap1->SetInput((vtkDataObject *)planeWight1->GetResliceOutput());
	//colorMap1->SetLookupTable(planeWight1->GetLookupTable());
	//imageData =	vtkImageData::SafeDownCast(planeWight1->GetInput());
	//int extent[6];
	//imageData->GetExtent(extent);
	//int min = extent[0 *2],max = extent[0 *2 + 1];	
	//SliceXNum = max;
	//planeWight1->SetSliceIndex(SliceXNum/2);
	///////////////添加显示文字
	//int length = extent[0 *2 + 1]+1;
	//int width =  extent[2 *2 + 1]+1;
	//char buf1[100],buf2[100];
	//sprintf(buf1,"%d*%d",length,width);
	//sliceXTextMapper1->SetInput(buf1);
	//m_SliceRender1->AddActor2D(sliceXTextActor1);
	//sprintf(buf2,"%d/%d",SliceXNum/2,SliceXNum);
	//sliceXTextMapper2->SetInput(buf2);	
	//m_SliceRender1->AddActor2D(sliceXTextActor2);	
	/////////////////////////////////////////////	
	//Window = planeWight1->GetWindow();
	//Level = planeWight1->GetLevel();
	//m_SliceActor1->SetInput(colorMap1->GetOutput());
	//m_SliceRender1->AddActor(m_SliceActor1);	
	//m_SliceRender1->ResetCamera();		
	//vtkInteractorStyleImage* style = vtkInteractorStyleImage::New();
	//mfcWinSlice1->GetInteractor()->SetInteractorStyle(style);
	//mfcWinSlice1->RedrawWindow();
}

void CBttmOneView::SetSliceX(int SliceIndex)
{
	if(SliceIndex>=0 && SliceIndex<=SliceXNum)
		planeWight1->SetSliceIndex(SliceIndex);
	mfcWinSlice1->RedrawWindow();
}

void CBttmOneView::ChangeWindowLevel(double window, double level)
{
	planeWight1->SetWindowLevel(window,level);
	mfcWinSlice1->RedrawWindow();
}

void CBttmOneView::ChangeXBkColor(float r,float g,float b)
{
	m_SliceRender1->SetBackground(r,g,b);
	m_SliceRender1->Render();
	mfcWinSlice1->RedrawWindow();
}

void CBttmOneView::SetLayerText(int index)
{
	char buf[100];
	sprintf(buf,"%d/%d",index,SliceXNum);
	sliceXTextMapper2->SetInput(buf);	
	m_SliceRender1->AddActor2D(sliceXTextActor2);
	mfcWinSlice1->RedrawWindow();
}

void CBttmOneView::LeftRotation()
{
	m_SliceActor1->SetOrigin( m_SliceActor1->GetCenter() ); 	
	m_SliceActor1->RotateZ(90); 	
	mfcWinSlice1->RedrawWindow();
}

void CBttmOneView::RightRotation()
{
	m_SliceActor1->SetOrigin( m_SliceActor1->GetCenter() );  
	m_SliceActor1->RotateZ(270); 
	mfcWinSlice1->RedrawWindow();
}

void CBttmOneView::HoriMirror()
{
	m_SliceActor1->SetOrigin( m_SliceActor1->GetCenter() );  
	m_SliceActor1->RotateX(180); 
	mfcWinSlice1->RedrawWindow();
}

void CBttmOneView::VertiMirror()
{
	m_SliceActor1->SetOrigin( m_SliceActor1->GetCenter() );  
	m_SliceActor1->RotateY(180); 
	mfcWinSlice1->RedrawWindow();
}


void CBttmOneView::AnisotropyFilter(int InteraNum,double DiffThread)
{
	/*vtkSmartPointer<vtkImageAnisotropicDiffusion2D> diffusionX =
		vtkSmartPointer<vtkImageAnisotropicDiffusion2D>::New();
	diffusionX->SetInput((vtkDataObject *)planeWight1->GetResliceOutput());
	diffusionX->SetNumberOfIterations(InteraNum);
	diffusionX->SetDiffusionThreshold(DiffThread);
	diffusionX->Update();
	vtkImageData* out = diffusionX->GetOutput();
	colorMap1->SetInput((vtkDataObject *)out);
	mfcWinSlice1->RedrawWindow();	*/
}

void CBttmOneView::MeDianFilter()
{
	/*vtkSmartPointer<vtkImageHybridMedian2D>hybridMedianX =
		vtkSmartPointer<vtkImageHybridMedian2D>::New();
	hybridMedianX->SetInput((vtkDataObject *)planeWight1->GetResliceOutput());
	hybridMedianX->Update();
	vtkImageData* out = hybridMedianX->GetOutput();
	colorMap1->SetInput((vtkDataObject *)out);
	mfcWinSlice1->RedrawWindow();	*/
}

void CBttmOneView::GaussSmooth(int GaussTemplateSize, float GaussTempltateSd)
{

	//vtkSmartPointer<vtkImageGaussianSmooth> gaussianSmoothFilterX=
	//	vtkSmartPointer<vtkImageGaussianSmooth>::New();
	//gaussianSmoothFilterX->SetInput((vtkDataObject *)planeWight1->GetResliceOutput());
	//gaussianSmoothFilterX->SetDimensionality(2);
	//gaussianSmoothFilterX->SetRadiusFactor(GaussTemplateSize);
	//gaussianSmoothFilterX->SetStandardDeviation(GaussTempltateSd);
	//gaussianSmoothFilterX->Update();
	//vtkImageData* out = gaussianSmoothFilterX->GetOutput();
	//colorMap1->SetInput((vtkDataObject *)out);
	//mfcWinSlice1->RedrawWindow();
}

void CBttmOneView::MeanFilter()
{
	//vtkSmartPointer<vtkImageConvolve> convolveFilterX =
	//	vtkSmartPointer<vtkImageConvolve>::New();
	//convolveFilterX->SetInput((vtkDataObject *)planeWight1->GetResliceOutput());
	//double kernel[25] ={0.04,0.04,0.04,0.04,0.04,
	//					0.04,0.04,0.04,0.04,0.04,
	//					0.04,0.04,0.04,0.04,0.04,
	//					0.04,0.04,0.04,0.04,0.04,
	//					0.04,0.04,0.04,0.04,0.04};
	//convolveFilterX->SetKernel5x5(kernel);
	//convolveFilterX->Update();
	//vtkSmartPointer<vtkImageCast>convCastFilterX = vtkSmartPointer<vtkImageCast>::New();
	//convCastFilterX->SetInput(convolveFilterX->GetOutput());
	//convCastFilterX->SetOutputScalarTypeToUnsignedChar();
	//convCastFilterX->Update();
	//vtkImageData* out = convCastFilterX->GetOutput();
	//colorMap1->SetInput((vtkDataObject *)out);
	//mfcWinSlice1->RedrawWindow();
}

void CBttmOneView::EdgeDetection()
{
/*	vtkSmartPointer<vtkImageGradient> gradientFilter =  
		vtkSmartPointer<vtkImageGradient>::New();  
	gradientFilter->SetInput((vtkDataObject *)planeWight1->GetResliceOutput());  
	gradientFilter->SetDimensionality(2);  
	vtkSmartPointer<vtkImageMagnitude> magnitudeFilter =  
		vtkSmartPointer<vtkImageMagnitude>::New();  
	magnitudeFilter->SetInputConnection(gradientFilter->GetOutputPort());  
	magnitudeFilter->Update();  
	double range[2];  
	magnitudeFilter->GetOutput()->GetScalarRange(range);  
	vtkSmartPointer<vtkImageShiftScale> ShiftScale =  
		vtkSmartPointer<vtkImageShiftScale>::New();  
	ShiftScale->SetOutputScalarTypeToUnsignedChar();  
	ShiftScale->SetScale( 255 / range[1] );  
	ShiftScale->SetInputConnection(magnitudeFilter->GetOutputPort());  
	ShiftScale->Update(); 
	vtkImageData* out = ShiftScale->GetOutput();
	colorMap1->SetInput((vtkDataObject *)out);
	mfcWinSlice1->RedrawWindow();*/	
}

void CBttmOneView::WriteBmpX(CString FolderName,CString FileName,int RangeMin,int RangeMax)	
{
	//vtkBMPWriter* writer  = vtkBMPWriter::New();	
	//if(RangeMax>SliceXNum)
	//	RangeMax = SliceXNum;
	//for(int i=RangeMin;i<=RangeMax;i++)
	//{
	//	planeWight1->SetSliceIndex(i);
	//	vtkImageData* out1= planeWight1->GetResliceOutput();	
	//	out1->SetScalarTypeToUnsignedChar();		
	//	out1->SetNumberOfScalarComponents(1);			
	//	out1->Update();
	//	writer->SetInput(out1);
	//	char ch[100];
	//	sprintf(ch,"%s\\%s_%d.bmp",FolderName,FileName,i);		
	//	writer->SetFileName(ch);
	//	writer->Update();
	//}
}

void CBttmOneView::HistormX()
{


	//double range[2];
	//vtkImageData* pImg = (vtkImageData*)planeWight1->GetResliceOutput();
	//pImg->Update();
	//pImg->GetScalarRange(range);

	//vtkImageAccumulate* pHistgram = vtkImageAccumulate::New();
	//pHistgram->SetInput((vtkDataObject*)planeWight1->GetResliceOutput());
	//pHistgram->SetComponentExtent(0, static_cast<int>(range[1] - range[0]), 0, 0, 0, 0);
	//pHistgram->SetComponentOrigin(range[0], 0, 0);
	//pHistgram->UpdateWholeExtent();

	//vtkXYPlotActor* plot = vtkXYPlotActor::New();
	//plot->ExchangeAxesOff();
	//plot->SetLabelFormat("%g");
	//plot->SetXRange(range[0], range[1]);
	//plot->SetYRange(0, 4096);
	//plot->SetXTitle("Gray Level");
	//plot->SetYTitle("");
	//plot->AddInput(pHistgram->GetOutput());
	//plot->SetXValuesToValue();

	//vtkRenderer* pRender = vtkRenderer::New();
	//pRender->AddActor(plot);

	//vtkRenderWindow* pRenWnd = vtkRenderWindow::New();
	//pRenWnd->AddRenderer(pRender);
	//pRenWnd->SetSize(512, 512);

	//vtkRenderWindowInteractor* pRenWndInact = vtkRenderWindowInteractor::New();
	//pRenWndInact->SetRenderWindow(pRenWnd);
	//pRenWndInact->Initialize();
	//pRenWndInact->Start();

	/*double range[2];
	vtkImageData* pImg = (vtkImageData*)planeWight1->GetResliceOutput();
	pImg->Update();
	pImg->GetScalarRange(range);

	vtkImageAccumulate* pHistgram = vtkImageAccumulate::New();
	pHistgram->SetInput((vtkDataObject*)planeWight1->GetResliceOutput());
	pHistgram->SetComponentExtent(0, static_cast<int>(range[1] - range[0]), 0, 0, 0, 0);
	pHistgram->SetComponentOrigin(range[0], 0, 0);
	pHistgram->UpdateWholeExtent();

	vtkXYPlotActor* plot = vtkXYPlotActor::New();
	plot->ExchangeAxesOff();
	plot->SetLabelFormat("%g");
	plot->SetXRange(range[0], range[1]);
	plot->SetYRange(0, 4096);
	plot->SetXTitle("Gray Level");
	plot->SetYTitle("");
	plot->AddInput(pHistgram->GetOutput());
	plot->SetXValuesToValue();		

	vtkRenderer* pRender = vtkRenderer::New();
	pRender->AddActor(plot);
	vtkRenderWindow* pRenWnd = vtkRenderWindow::New();
	pRenWnd->AddRenderer(pRender);
	pRenWnd->SetSize(512, 512);	
	vtkRenderWindowInteractor* pRenWndInact = vtkRenderWindowInteractor::New();
	pRenWndInact->SetRenderWindow(pRenWnd);
	pRenWndInact->Initialize();
	pRenWndInact->Start();*/
}


void CBttmOneView::OnZoxcapture()
{
	// TODO: 在此添加命令处理程序代码
	CDlgCaptureSet dlg;
	if(dlg.DoModal())
	{
		m_captureFolder = dlg.m_strCaptureFolderPath;
		m_CaptureName = dlg.m_CaptureName;
		Capture(m_captureFolder,m_CaptureName);	
	}
	else
		return;		
}


void CBttmOneView::Capture(CString path,CString name)
{
	/*vtkWindowToImageFilter * wif = vtkWindowToImageFilter::New();
	vtkBMPWriter *bmpw = vtkBMPWriter::New();
	wif->SetInput(mfcWinSlice1->GetRenderWindow());
	bmpw->SetInput(wif->GetOutput());
	CString savepath = path + "\\" + name +".bmp";
	bmpw->SetFileName(savepath);
	bmpw->Write();*/
}


void CBttmOneView::BinaryX(int value)
{
	//vtkSmartPointer<vtkImageThreshold> thresholdFilter =
	//	vtkSmartPointer<vtkImageThreshold>::New();
	//thresholdFilter->SetInput(planeWight1->GetResliceOutput());
	//thresholdFilter->ThresholdByUpper(value);
	//thresholdFilter->SetInValue(255);
	//thresholdFilter->SetOutValue(0);
	//vtkImageData* out = thresholdFilter->GetOutput();
	//colorMap1->SetInput((vtkDataObject *)out);
	//mfcWinSlice1->RedrawWindow();
}