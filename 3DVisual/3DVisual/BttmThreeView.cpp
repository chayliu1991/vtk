// BttmThreeView.cpp : 实现文件
//

#include "stdafx.h"
#include "3DVisual.h"
#include "BttmThreeView.h"
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
#include "vtkImageThreshold.h"
#include "vtkImageGradient.h"
#include "vtkImageMagnitude.h"
#include "vtkImageShiftScale.h"
#include "vtkImageAccumulate.h"
#include "vtkXYPlotActor.h"
#include "vtkWindowToImageFilter.h"
#include "vtkImageThreshold.h"



//////////////////
int SliceZNum = 0;
// CBttmThreeView

IMPLEMENT_DYNCREATE(CBttmThreeView, CView)

CBttmThreeView::CBttmThreeView()
{
	m_backgroundColor = RGB(0, 0, 0);
	m_frontgroundColor = RGB(0,0, 255);
	mfcWinSlice3 = NULL;
	m_SliceRender3 = vtkRenderer::New();//创建绘制者		
	m_SliceActor3 = vtkImageActor::New();//建立一个代表皮肤的演员
	colorMap3= vtkImageMapToColors::New();
	planeWight3 = vtkImagePlaneWidget::New();
	ipwProp3 = vtkProperty::New();
	planeWight3->SetKeyPressActivationValue('x');
	planeWight3->RestrictPlaneToVolumeOn();
	planeWight3->GetPlaneProperty()->SetColor(1,0,0);
	planeWight3->SetTexturePlaneProperty(ipwProp3);
	planeWight3->SetResliceInterpolateToNearestNeighbour();	
	planeWight3->DisplayTextOn();
	colorMap3->PassAlphaToOutputOff();
	colorMap3->SetActiveComponent(0);
	colorMap3->SetOutputFormatToLuminance();
	sliceZTextProp = vtkTextProperty::New();
	sliceZTextProp->SetFontFamilyToCourier();
	sliceZTextProp->SetFontSize(16);
	sliceZTextProp->SetVerticalJustificationToBottom();
	sliceZTextProp->SetJustificationToLeft();
	sliceZTextMapper1 = vtkTextMapper::New();	
	sliceZTextMapper1->SetTextProperty(sliceZTextProp);
	sliceZTextActor1 = vtkActor2D::New();
	sliceZTextActor1->SetMapper(sliceZTextMapper1);
	sliceZTextActor1->SetPosition(5,25);
	sliceZTextMapper2 = vtkTextMapper::New();	
	sliceZTextMapper2->SetTextProperty(sliceZTextProp);
	sliceZTextActor2 = vtkActor2D::New();
	sliceZTextActor2->SetMapper(sliceZTextMapper2);
	sliceZTextActor2->SetPosition(5, 5);
	
}

CBttmThreeView::~CBttmThreeView()
{
	if (mfcWinSlice3)
		delete mfcWinSlice3;
}

BEGIN_MESSAGE_MAP(CBttmThreeView, CView)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CBttmThreeView 绘图

void CBttmThreeView::OnDraw(CDC* pDC)
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


// CBttmThreeView 诊断

#ifdef _DEBUG
void CBttmThreeView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBttmThreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBttmThreeView 消息处理程序


void CBttmThreeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	mfcWinSlice3 = new vtkMFCWindow(this);
	mfcWinSlice3->SetXYZ();
	(mfcWinSlice3->GetRenderWindow())->SetPosition(2,2);
	CRect rect;
	GetClientRect(&rect);
	(mfcWinSlice3->GetRenderWindow())->SetSize(rect.Width()-5,rect.Height()-5);
	mfcWinSlice3->GetRenderWindow()->AddRenderer(m_SliceRender3);
}

void CBttmThreeView::OnDestroy()
{
	CView::OnDestroy();
	// TODO: Add your message handler code here
	if(m_SliceRender3)
		m_SliceRender3->Delete();
	if(m_SliceActor3)
		m_SliceActor3->Delete();
	if(colorMap3)
		colorMap3->Delete();	
	if(planeWight3)
		planeWight3->Delete();	
	if(ipwProp3)
		ipwProp3->Delete();
}

void CBttmThreeView::DisplaySlice3(vtkDataSet* input)
{
	//planeWight3->SetInput(input);
	//planeWight3->SetPlaneOrientation(2);
	//colorMap3->SetInput((vtkDataObject *)planeWight3->GetResliceOutput());
	//colorMap3->SetLookupTable(planeWight3->GetLookupTable());
	//vtkImageData * imageData =
	//	vtkImageData::SafeDownCast(planeWight3->GetInput());
	//int extent[6];
	//imageData->GetExtent(extent);
	//int min = extent[2 *2],max = extent[2 *2 + 1];
	//SliceZNum = max;
	//planeWight3->SetSliceIndex(SliceZNum/2);
	///////////////添加显示文字
	//int length =  extent[0 *2 + 1]+1;
	//int width =  extent[1*2 + 1]+1;	
	//char buf1[100],buf2[100];
	//sprintf(buf1,"%d*%d",length,width);
	//sliceZTextMapper1->SetInput(buf1);
	//m_SliceRender3->AddActor2D(sliceZTextActor1);
	//sprintf(buf2,"%d/%d",SliceZNum/2,SliceZNum);
	//sliceZTextMapper2->SetInput(buf2);	
	//m_SliceRender3->AddActor2D(sliceZTextActor2);	
	/////////////////////////////////////////////

	//m_SliceActor3->SetInput(colorMap3->GetOutput());
	//m_SliceRender3->AddActor(m_SliceActor3);	
	//m_SliceRender3->ResetCamera();
	//vtkInteractorStyleImage* style = vtkInteractorStyleImage::New();
	//mfcWinSlice3->GetInteractor()->SetInteractorStyle(style);
	//mfcWinSlice3->RedrawWindow();
}

void CBttmThreeView::SetSliceZ(int SliceIndex)
{
	if(SliceIndex>=0 && SliceZNum)
		planeWight3->SetSliceIndex(SliceIndex);
	mfcWinSlice3->RedrawWindow();
}

void CBttmThreeView::ChangeWindowLevel(double window, double level)
{
	planeWight3->SetWindowLevel(window,level);
	mfcWinSlice3->RedrawWindow();
}

void CBttmThreeView::ChangeZBkColor(float r,float g,float b)
{
	m_SliceRender3->SetBackground(r,g,b);
	m_SliceRender3->Render();
	mfcWinSlice3->RedrawWindow();
}

void CBttmThreeView::SetLayerText(int index)
{
	char buf[100];
	sprintf(buf,"%d/%d",index,SliceZNum);
	sliceZTextMapper2->SetInput(buf);	
	m_SliceRender3->AddActor2D(sliceZTextActor2);
	mfcWinSlice3->RedrawWindow();
}

void CBttmThreeView::LeftRotation()
{
	m_SliceActor3->SetOrigin( m_SliceActor3->GetCenter() );  
	m_SliceActor3->RotateZ(90); 
	mfcWinSlice3->RedrawWindow();
}

void CBttmThreeView::RightRotation()
{
	m_SliceActor3->SetOrigin( m_SliceActor3->GetCenter() );  
	m_SliceActor3->RotateZ(270); 
	mfcWinSlice3->RedrawWindow();
}

void CBttmThreeView::HoriMirror()
{
	m_SliceActor3->SetOrigin( m_SliceActor3->GetCenter() );  
	m_SliceActor3->RotateX(180); 
	mfcWinSlice3->RedrawWindow();
}

void CBttmThreeView::VertiMirror()
{
	m_SliceActor3->SetOrigin( m_SliceActor3->GetCenter() );  
	m_SliceActor3->RotateY(180); 
	mfcWinSlice3->RedrawWindow();
}



void CBttmThreeView::AnisotropyFilter(int InteraNum,double DiffThread)
{
	/*vtkSmartPointer<vtkImageAnisotropicDiffusion2D> diffusionZ =
		vtkSmartPointer<vtkImageAnisotropicDiffusion2D>::New();
	diffusionZ->SetInput((vtkDataObject *)planeWight3->GetResliceOutput());
	diffusionZ->SetNumberOfIterations(InteraNum);
	diffusionZ->SetDiffusionThreshold(DiffThread);
	diffusionZ->Update();
	vtkImageData* out = diffusionZ->GetOutput();
	colorMap3->SetInput((vtkDataObject *)out);
	mfcWinSlice3->RedrawWindow();*/	
}

void CBttmThreeView::MeDianFilter()
{
	//vtkSmartPointer<vtkImageHybridMedian2D>hybridMedianZ =
	//	vtkSmartPointer<vtkImageHybridMedian2D>::New();
	//hybridMedianZ->SetInput((vtkDataObject *)planeWight3->GetResliceOutput());
	//hybridMedianZ->Update();
	//vtkImageData* out = hybridMedianZ->GetOutput();
	//colorMap3->SetInput((vtkDataObject *)out);
	//mfcWinSlice3->RedrawWindow();	
}

void CBttmThreeView::GaussSmooth(int GaussTemplateSize, float GaussTempltateSd)
{
	
	/*vtkSmartPointer<vtkImageGaussianSmooth> gaussianSmoothFilterZ =
		vtkSmartPointer<vtkImageGaussianSmooth>::New();
	gaussianSmoothFilterZ->SetInput((vtkDataObject *)planeWight3->GetResliceOutput());
	gaussianSmoothFilterZ->SetDimensionality(2);
	gaussianSmoothFilterZ->SetRadiusFactor(GaussTemplateSize);
	gaussianSmoothFilterZ->SetStandardDeviation(GaussTempltateSd);
	gaussianSmoothFilterZ->Update();
	vtkImageData* out = gaussianSmoothFilterZ->GetOutput();
	colorMap3->SetInput((vtkDataObject *)out);
	mfcWinSlice3->RedrawWindow();*/
}

void CBttmThreeView::MeanFilter()
{
	//vtkSmartPointer<vtkImageConvolve> convolveFilterZ =
	//	vtkSmartPointer<vtkImageConvolve>::New();
	//convolveFilterZ->SetInput((vtkDataObject *)planeWight3->GetResliceOutput());
	//double kernel[25] ={0.04,0.04,0.04,0.04,0.04,
	//	0.04,0.04,0.04,0.04,0.04,
	//	0.04,0.04,0.04,0.04,0.04,
	//	0.04,0.04,0.04,0.04,0.04,
	//	0.04,0.04,0.04,0.04,0.04};
	//convolveFilterZ->SetKernel5x5(kernel);
	//convolveFilterZ->Update();
	//vtkSmartPointer<vtkImageCast>convCastFilterZ= vtkSmartPointer<vtkImageCast>::New();
	//convCastFilterZ->SetInput(convolveFilterZ->GetOutput());
	//convCastFilterZ->SetOutputScalarTypeToUnsignedChar();
	//convCastFilterZ->Update();
	//vtkImageData* out = convCastFilterZ->GetOutput();
	//colorMap3->SetInput((vtkDataObject *)out);
	//mfcWinSlice3->RedrawWindow();

}

void CBttmThreeView::Binaryzation()
{
	/*vtkSmartPointer<vtkImageThreshold> BinaryZ =
	vtkSmartPointer<vtkImageThreshold>::New();
	BinaryZ->ThresholdByUpper(50);
	BinaryZ->SetInValue(255);  
	BinaryZ->SetOutValue(0);
	BinaryZ->SetInput((vtkDataObject *)planeWight3->GetResliceOutput());
	BinaryZ->Update();
	vtkImageData* out = BinaryZ->GetOutput();
	colorMap3->SetInput((vtkDataObject *)out);
	mfcWinSlice3->RedrawWindow();	*/
	
}


void CBttmThreeView::EdgeDetection()
{
	/*vtkSmartPointer<vtkImageGradient> gradientFilter =  
		vtkSmartPointer<vtkImageGradient>::New();  
	gradientFilter->SetInput((vtkDataObject *)planeWight3->GetResliceOutput());  
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
	colorMap3->SetInput((vtkDataObject *)out);
	mfcWinSlice3->RedrawWindow();	*/
}

void CBttmThreeView::WriteBmpZ(CString FolderName,CString FileName,int RangeMin,int RangeMax)	
{
	//vtkBMPWriter* writer  = vtkBMPWriter::New();	
	//if(RangeMax>SliceZNum)
	//	RangeMax = SliceZNum;
	//for(int i=RangeMin;i<=RangeMax;i++)
	//{
	//	planeWight3->SetSliceIndex(i);
	//	vtkImageData* out1= planeWight3->GetResliceOutput();	
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

void CBttmThreeView::HistormZ()
{
	/*double range[2];
	vtkImageData* pImg = (vtkImageData*)planeWight3->GetResliceOutput();
	pImg->Update();
	pImg->GetScalarRange(range);

	vtkImageAccumulate* pHistgram = vtkImageAccumulate::New();
	pHistgram->SetInput((vtkDataObject*)planeWight3->GetResliceOutput());
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

void CBttmThreeView::Capture(CString path,CString name)
{
	/*vtkWindowToImageFilter * wif = vtkWindowToImageFilter::New();
	vtkBMPWriter *bmpw = vtkBMPWriter::New();
	wif->SetInput(mfcWinSlice3->GetRenderWindow());
	bmpw->SetInput(wif->GetOutput());
	CString savepath = path + "\\" + name +".bmp";
	bmpw->SetFileName(savepath);
	bmpw->Write();*/
}


void CBttmThreeView::BinaryZ(int value)
{
	//vtkSmartPointer<vtkImageThreshold> thresholdFilter =
	//	vtkSmartPointer<vtkImageThreshold>::New();
	//thresholdFilter->SetInput(planeWight3->GetResliceOutput());
	//thresholdFilter->ThresholdByUpper(value);
	//thresholdFilter->SetInValue(255);
	//thresholdFilter->SetOutValue(0);
	//vtkImageData* out = thresholdFilter->GetOutput();
	//colorMap3->SetInput((vtkDataObject *)out);
	//mfcWinSlice3->RedrawWindow();
}