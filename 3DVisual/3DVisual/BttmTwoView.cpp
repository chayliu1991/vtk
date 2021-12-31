// BttmTwoView.cpp : 实现文件
//

#include "stdafx.h"
#include "3DVisual.h"
#include "BttmTwoView.h"
#include <vtkInteractorStyleImage.h>
#include "MainFrm.h"
#include "3DVisualDoc.h"
#include <vtkDICOMImageReader.h>
#include "vtkLookupTable.h"
#include "vtkImageAnisotropicDiffusion2D.h"
#include "vtkImageHybridMedian2D.h"
#include "vtkImageGaussianSmooth.h"
#include "vtkImageConvolve.h"
#include "vtkImageCast.h"
#include "vtkImageGradient.h"
#include "vtkImageMagnitude.h"
#include "vtkImageShiftScale.h"
#include "vtkImageAccumulate.h"
#include "vtkXYPlotActor.h"
#include "vtkWindowToImageFilter.h"


////////////////////
int SliceYNum = 0;

// CBttmTwoView

IMPLEMENT_DYNCREATE(CBttmTwoView, CView)

CBttmTwoView::CBttmTwoView()
{
	m_backgroundColor = RGB(0, 0, 0);
	m_frontgroundColor = RGB(0,0, 255);
	mfcWinSlice2 = NULL;
	m_SliceRender2 = vtkRenderer::New();//创建绘制者		
	m_SliceActor2 = vtkImageActor::New();//建立一个代表皮肤的演员
	colorMap2 = vtkImageMapToColors::New();
	planeWight2 = vtkImagePlaneWidget::New();
	ipwProp2 = vtkProperty::New();
	planeWight2->SetKeyPressActivationValue('x');
	planeWight2->RestrictPlaneToVolumeOn();
	planeWight2->GetPlaneProperty()->SetColor(1,0,0);
	planeWight2->SetTexturePlaneProperty(ipwProp2);
	planeWight2->SetResliceInterpolateToNearestNeighbour();	
	planeWight2->DisplayTextOn();
	colorMap2->PassAlphaToOutputOff();
	colorMap2->SetActiveComponent(0);
	colorMap2->SetOutputFormatToLuminance();
	sliceYTextProp = vtkTextProperty::New();
	sliceYTextProp->SetFontFamilyToCourier();
	sliceYTextProp->SetFontSize(16);
	sliceYTextProp->SetVerticalJustificationToBottom();
	sliceYTextProp->SetJustificationToLeft();
	sliceYTextMapper1 = vtkTextMapper::New();	
	sliceYTextMapper1->SetTextProperty(sliceYTextProp);
	sliceYTextActor1 = vtkActor2D::New();
	sliceYTextActor1->SetMapper(sliceYTextMapper1);
	sliceYTextActor1->SetPosition(5,25);
	sliceYTextMapper2 = vtkTextMapper::New();	
	sliceYTextMapper2->SetTextProperty(sliceYTextProp);
	sliceYTextActor2 = vtkActor2D::New();
	sliceYTextActor2->SetMapper(sliceYTextMapper2);
	sliceYTextActor2->SetPosition(5, 5);
}

CBttmTwoView::~CBttmTwoView()
{
	if (mfcWinSlice2)
		delete mfcWinSlice2;
}

BEGIN_MESSAGE_MAP(CBttmTwoView, CView)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CBttmTwoView 绘图

void CBttmTwoView::OnDraw(CDC* pDC)
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


// CBttmTwoView 诊断

#ifdef _DEBUG
void CBttmTwoView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBttmTwoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBttmTwoView 消息处理程序


void CBttmTwoView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	mfcWinSlice2 = new vtkMFCWindow(this);
	mfcWinSlice2->SetXYZ();
	(mfcWinSlice2->GetRenderWindow())->SetPosition(2,2);
	CRect rect;
	GetClientRect(&rect);
	(mfcWinSlice2->GetRenderWindow())->SetSize(rect.Width()-5,rect.Height()-5);
	mfcWinSlice2->GetRenderWindow()->AddRenderer(m_SliceRender2);
}


void CBttmTwoView::OnDestroy()
{
	CView::OnDestroy();
	// TODO: Add your message handler code here
	if(m_SliceRender2)
		m_SliceRender2->Delete();
	if(m_SliceActor2)
		m_SliceActor2->Delete();
	if(colorMap2)
		colorMap2->Delete();	
	if(planeWight2)
		planeWight2->Delete();	
	if(ipwProp2)
		ipwProp2->Delete();
}

void CBttmTwoView::DisplaySlice2(vtkDataSet* input)
{
	//planeWight2->SetInput(input);
	//planeWight2->SetPlaneOrientation(1);
	//colorMap2->SetInput((vtkDataObject *)planeWight2->GetResliceOutput());
	//colorMap2->SetLookupTable(planeWight2->GetLookupTable());
	//imageData =	vtkImageData::SafeDownCast(planeWight2->GetInput());
	//int extent[6];
	//imageData->GetExtent(extent);
	//int min = extent[1 *2],max = extent[1 *2 + 1];
	//SliceYNum = max;
	//planeWight2->SetSliceIndex(SliceYNum/2);
	/////////////添加显示文字
	//int length =  extent[2 *2 + 1]+1;
	//int width =  extent[1 *2 + 1]+1;	
	//char buf1[100],buf2[100];
	//sprintf(buf1,"%d*%d",length,width);
	//sliceYTextMapper1->SetInput(buf1);
	//m_SliceRender2->AddActor2D(sliceYTextActor1);
	//sprintf(buf2,"%d/%d",SliceYNum/2,SliceYNum);
	//sliceYTextMapper2->SetInput(buf2);	
	//m_SliceRender2->AddActor2D(sliceYTextActor2);	
	///////////////////////////////////////////	
	//m_SliceActor2->SetInput(colorMap2->GetOutput());
	//m_SliceRender2->AddActor(m_SliceActor2);	
	//m_SliceRender2->ResetCamera();
	//vtkInteractorStyleImage* style = vtkInteractorStyleImage::New();
	//mfcWinSlice2->GetInteractor()->SetInteractorStyle(style);
	//mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::SetSliceY(int SliceIndex)
{
	if(SliceIndex>=0 && SliceIndex<=SliceYNum)
		planeWight2->SetSliceIndex(SliceIndex);
	mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::ChangeWindowLevel(double window, double level)
{
	planeWight2->SetWindowLevel(window,level);
	mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::ChangeYBkColor(float r,float g,float b)
{
	m_SliceRender2->SetBackground(r,g,b);
	m_SliceRender2->Render();
	mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::SetLayerText(int index)
{
	char buf[100];
	sprintf(buf,"%d/%d",index,SliceYNum);
	sliceYTextMapper2->SetInput(buf);	
	m_SliceRender2->AddActor2D(sliceYTextActor2);
	mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::LeftRotation()
{
	m_SliceActor2->SetOrigin( m_SliceActor2->GetCenter() );  
	m_SliceActor2->RotateZ(90); 
	mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::RightRotation()
{
	m_SliceActor2->SetOrigin( m_SliceActor2->GetCenter() );  
	m_SliceActor2->RotateZ(270); 
	mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::HoriMirror()
{
	m_SliceActor2->SetOrigin( m_SliceActor2->GetCenter() );  
	m_SliceActor2->RotateX(180); 
	mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::VertiMirror()
{
	m_SliceActor2->SetOrigin( m_SliceActor2->GetCenter() );  
	m_SliceActor2->RotateY(180); 
	mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::AnisotropyFilter(int InteraNum,double DiffThread)
{
	/*vtkSmartPointer<vtkImageAnisotropicDiffusion2D> diffusionY =
		vtkSmartPointer<vtkImageAnisotropicDiffusion2D>::New();
	diffusionY->SetInput((vtkDataObject *)planeWight2->GetResliceOutput());
	diffusionY->SetNumberOfIterations(InteraNum);
	diffusionY->SetDiffusionThreshold(DiffThread);
	diffusionY->Update();
	vtkImageData* out = diffusionY->GetOutput();
	colorMap2->SetInput((vtkDataObject *)out);
	mfcWinSlice2->RedrawWindow();	*/
}

void CBttmTwoView::MeDianFilter()
{
/*	vtkSmartPointer<vtkImageHybridMedian2D>hybridMedianY =
		vtkSmartPointer<vtkImageHybridMedian2D>::New();
	hybridMedianY->SetInput((vtkDataObject *)planeWight2->GetResliceOutput());
	hybridMedianY->Update();
	vtkImageData* out = hybridMedianY->GetOutput();
	colorMap2->SetInput((vtkDataObject *)out);
	mfcWinSlice2->RedrawWindow();*/	
}

void CBttmTwoView::GaussSmooth(int GaussTemplateSize, float GaussTempltateSd)
{

	//vtkSmartPointer<vtkImageGaussianSmooth> gaussianSmoothFilterY=
	//	vtkSmartPointer<vtkImageGaussianSmooth>::New();
	//gaussianSmoothFilterY->SetInput((vtkDataObject *)planeWight2->GetResliceOutput());
	//gaussianSmoothFilterY->SetDimensionality(2);
	//gaussianSmoothFilterY->SetRadiusFactor(GaussTemplateSize);
	//gaussianSmoothFilterY->SetStandardDeviation(GaussTempltateSd);
	//gaussianSmoothFilterY->Update();
	//vtkImageData* out = gaussianSmoothFilterY->GetOutput();
	//colorMap2->SetInput((vtkDataObject *)out);
	//mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::MeanFilter()
{
	//vtkSmartPointer<vtkImageConvolve> convolveFilterY =
	//	vtkSmartPointer<vtkImageConvolve>::New();
	//convolveFilterY->SetInput((vtkDataObject *)planeWight2->GetResliceOutput());
	//double kernel[25] ={0.04,0.04,0.04,0.04,0.04,
	//	0.04,0.04,0.04,0.04,0.04,
	//	0.04,0.04,0.04,0.04,0.04,
	//	0.04,0.04,0.04,0.04,0.04,
	//	0.04,0.04,0.04,0.04,0.04};
	//convolveFilterY->SetKernel5x5(kernel);
	//convolveFilterY->Update();
	//vtkSmartPointer<vtkImageCast>convCastFilterY = vtkSmartPointer<vtkImageCast>::New();
	//convCastFilterY->SetInput(convolveFilterY->GetOutput());
	//convCastFilterY->SetOutputScalarTypeToUnsignedChar();
	//convCastFilterY->Update();
	//vtkImageData* out = convCastFilterY->GetOutput();
	//colorMap2->SetInput((vtkDataObject *)out);
	//mfcWinSlice2->RedrawWindow();
}

void CBttmTwoView::EdgeDetection()
{
	/*vtkSmartPointer<vtkImageGradient> gradientFilter =  
		vtkSmartPointer<vtkImageGradient>::New();  
	gradientFilter->SetInput((vtkDataObject *)planeWight2->GetResliceOutput());  
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
	colorMap2->SetInput((vtkDataObject *)out);
	mfcWinSlice2->RedrawWindow();	*/
}


void CBttmTwoView::WriteBmpY(CString FolderName,CString FileName,int RangeMin,int RangeMax)	
{
	//vtkBMPWriter* writer  = vtkBMPWriter::New();
	//if(RangeMax>SliceYNum)
	//	RangeMax = SliceYNum;
	//for(int i=RangeMin;i<=RangeMax;i++)
	//{
	//	planeWight2->SetSliceIndex(i);
	//	vtkImageData* out1= planeWight2->GetResliceOutput();	
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

void CBttmTwoView::HistormY()
{
	/*double range[2];
	vtkImageData* pImg = (vtkImageData*)planeWight2->GetResliceOutput();
	pImg->Update();
	pImg->GetScalarRange(range);

	vtkImageAccumulate* pHistgram = vtkImageAccumulate::New();
	pHistgram->SetInput((vtkDataObject*)planeWight2->GetResliceOutput());
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
	plot->SetXValuesToValue();	*/	

	//vtkRenderer* pRender = vtkRenderer::New();
	//pRender->AddActor(plot);
	//vtkRenderWindow* pRenWnd = vtkRenderWindow::New();
	//pRenWnd->AddRenderer(pRender);
	//pRenWnd->SetSize(512, 512);	
	//vtkRenderWindowInteractor* pRenWndInact = vtkRenderWindowInteractor::New();
	//pRenWndInact->SetRenderWindow(pRenWnd);
	//pRenWndInact->Initialize();
	//pRenWndInact->Start();

}

void CBttmTwoView::Capture(CString path,CString name)
{
	//vtkWindowToImageFilter * wif = vtkWindowToImageFilter::New();
	//vtkBMPWriter *bmpw = vtkBMPWriter::New();
	//wif->SetInput(mfcWinSlice2->GetRenderWindow());
	//bmpw->SetInput(wif->GetOutput());
	//CString savepath = path + "\\" + name +".bmp";
	//bmpw->SetFileName(savepath);
	//bmpw->Write();
}

void CBttmTwoView::BinaryY(int value)
{
	/*vtkSmartPointer<vtkImageThreshold> thresholdFilter =
		vtkSmartPointer<vtkImageThreshold>::New();
	thresholdFilter->SetInput(planeWight2->GetResliceOutput());
	thresholdFilter->ThresholdByUpper(value);
	thresholdFilter->SetInValue(255);
	thresholdFilter->SetOutValue(0);
	vtkImageData* out = thresholdFilter->GetOutput();
	colorMap2->SetInput((vtkDataObject *)out);
	mfcWinSlice2->RedrawWindow();*/
}