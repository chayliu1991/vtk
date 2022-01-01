
// 3DVisualView.cpp : CMy3DVisualView 类的实现
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


#include "vtkClipPolyData.h"
#include "vtkPlane.h"
#include "vtkRenderWindowInteractor.h"
#include "DlgCaptureSet.h"
#include "vtkWindowToImageFilter.h"


#include "vtkSTLWriter.h"
#include "vtkPolyDataReader.h"
#include "vtkTriangleFilter.h"
#include "vtkDecimatePro.h"
#include "vtkSmoothPolyDataFilter.h"
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkNIFTIImageReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkimagedata.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkMultiVolume.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkNamedColors.h>
#include <vtkImageAccumulate.h>
#include <vtkVolumeMapper.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkSTLWriter.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkImageMathematics.h>
#include <vtkImageShiftScale.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkOpenGLGPUVolumeRayCastMapper.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




////////////////全局变量
extern UINT data_fg ;
extern int m_VRAlgorithmType;

// CMy3DVisualView

IMPLEMENT_DYNCREATE(CMy3DVisualView, CView)

BEGIN_MESSAGE_MAP(CMy3DVisualView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy3DVisualView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()		
END_MESSAGE_MAP()

// CMy3DVisualView 构造/析构

CMy3DVisualView::CMy3DVisualView()
{
	// TODO: 在此处添加构造代码	
	//共用变量初始化
	m_backgroundColor = RGB(0, 0, 0);
	m_frontgroundColor = RGB(255,0, 0);
	mfcWin = NULL;
	style =	vtkInteractorStyleTrackballCamera::New();	
	//MC算法初始化对象
	m_McRender = vtkRenderer::New();//创建绘制者
	m_McSkinExtractor = vtkMarchingCubes::New();//创建Marching Cubes 算法的对象
	m_McSkinStripper = vtkStripper::New();//建立三角带对象
	m_McMapper = vtkPolyDataMapper::New();//建立一个数据映射对象
	m_McActor = vtkActor::New();//建立一个代表皮肤的演员
	m_Bmpsample = vtkImageResample::New();	
	m_Binsample = vtkImageResample::New();
	//VR算法初始化对象
	m_VrRender = vtkRenderer::New();
	opacityTransferFunction = vtkPiecewiseFunction::New();
	colorTransferFunction = vtkColorTransferFunction::New();
	volumeProperty = vtkVolumeProperty::New();	
	volumeMapper = vtkPolyDataMapper::New(); //体绘制器	
	volume = vtkVolume::New();//表示透示图中的一组三维数据
	readerImageCast = vtkImageCast::New();//数据类型转换
	gradientTransferFunction = vtkPiecewiseFunction::New();

	volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();
	volumeGradientOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeScalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volume_render = vtkSmartPointer<vtkRenderer>::New();
	origin_data = vtkSmartPointer<vtkImageData>::New();
}

CMy3DVisualView::~CMy3DVisualView()
{
	if (mfcWin)
		delete mfcWin;
}

BOOL CMy3DVisualView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy3DVisualView 绘制

void CMy3DVisualView::OnDraw(CDC* pDC)
{
	CMy3DVisualDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	CRect rc;
	GetClientRect(&rc);
	CBrush br(m_backgroundColor);
	pDC->FillRect(&rc,&br);	
	pDC->Draw3dRect(rc, m_frontgroundColor, m_frontgroundColor);
	rc.DeflateRect(1, 1);
	pDC->Draw3dRect(rc, m_frontgroundColor, m_frontgroundColor);
}


// CMy3DVisualView 打印


void CMy3DVisualView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy3DVisualView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy3DVisualView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy3DVisualView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMy3DVisualView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy3DVisualView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy3DVisualView 诊断

#ifdef _DEBUG
void CMy3DVisualView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DVisualView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DVisualDoc* CMy3DVisualView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DVisualDoc)));
	return (CMy3DVisualDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DVisualView 消息处理程序


void CMy3DVisualView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//创建VtkMFCWindow,并制定renderwindow的大小，为了使边框颜色能够显示出来
	//使其略小于Client的大小即可。
	mfcWin = new vtkMFCWindow(this);	
	(mfcWin->GetRenderWindow())->SetPosition(2,2);
	CRect rect;
	GetClientRect(&rect);
	(mfcWin->GetRenderWindow())->SetSize(rect.Width()-4,rect.Height()-4);
}


void CMy3DVisualView::OnDestroy()
{
	CView::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	//销毁MC算法中的相关资源
	//if(m_McRender)
	//	m_McRender->Delete();
	//if(m_McSkinExtractor)
	//	m_McSkinExtractor->Delete();
	//if(m_McSkinStripper)
	//	m_McSkinStripper->Delete();
	//if(m_McMapper)
	//	m_McMapper->Delete();
	//if(m_McActor)
	//	m_McActor->Delete();
	//if(style)
	//	style->Delete();
	//if(opacityTransferFunction)
	//	opacityTransferFunction->Delete();
	//if(colorTransferFunction)
	//	colorTransferFunction->Delete();	
	//if(volumeProperty)
	//	volumeProperty->Delete();	
	//if(volumeMapper)
	//	volumeMapper->Delete();	
	//if(volume)
	//	volume->Delete();	
	//if(readerImageCast)
	//	readerImageCast->Delete();
	//if(gradientTransferFunction)
	//	gradientTransferFunction->Delete();	
	
}


BOOL CMy3DVisualView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return FALSE;
}

///////////////////////////////////////
//Marching Cubes实现
//////////////////////////////////////
void CMy3DVisualView::MarchingCubes()
{
	if(data_fg == 1)
	{
		CMy3DVisualDoc* pDoc = GetDocument();
		pDoc->Dicomreader->Update();
		m_McSkinExtractor->SetInputConnection(pDoc->Dicomreader->GetOutputPort());
	}
	if(data_fg ==2)
	{
		CMy3DVisualDoc* pDoc = GetDocument();
		pDoc->Bmpreader->Update();		
		m_Bmpsample->SetAxisMagnificationFactor(0,pDoc->samplevalue);
		m_Bmpsample->SetAxisMagnificationFactor(1,pDoc->samplevalue);
		m_Bmpsample->SetAxisMagnificationFactor(2,pDoc->samplevalue);
		m_Bmpsample->SetInputConnection(pDoc->Bmpreader->GetOutputPort());
		m_Bmpsample->Update();
		m_McSkinExtractor->SetInputConnection(m_Bmpsample->GetOutputPort()); 
	}
	m_McSkinExtractor->SetValue(0, 50);
	////////////////////
	//vtkDecimatePro *deciFilter = vtkDecimatePro::New();
	//deciFilter->SetInputConnection(m_McSkinExtractor->GetOutputPort());
	//deciFilter->SetTargetReduction(0.3); //简化为原来的10%
	//deciFilter->PreserveTopologyOn();//保持原始网格拓扑结构	
	////做平滑	
	//vtkSmoothPolyDataFilter *smoothFilter = vtkSmoothPolyDataFilter::New();
	//smoothFilter->SetInputConnection(deciFilter->GetOutputPort());	
	//smoothFilter->SetNumberOfIterations(10);//设置平滑的次数
	//smoothFilter->FeatureEdgeSmoothingOn();	//开启尖锐特征平滑

	//m_McSkinStripper->SetInputConnection(m_McSkinExtractor->GetOutputPort());

	m_McSkinStripper->SetInputConnection(m_McSkinExtractor->GetOutputPort());

	m_McMapper->ScalarVisibilityOff();
	m_McMapper->SetInputData(m_McSkinStripper->GetOutput());
	m_McActor->GetProperty()->SetDiffuseColor(0,1,0);
	m_McActor->GetProperty()->SetSpecular(0.3);     //设置反射率
	m_McActor->GetProperty()->SetSpecularPower(100); //设置反射光强度 
	m_McActor->SetMapper(m_McMapper);
	m_McActor->GetProperty()->SetOpacity(1);
	m_McRender->AddActor(m_McActor);
	m_McRender->SetBackground(0,0,0);		
	mfcWin->GetInteractor()->SetInteractorStyle(style);	
	mfcWin->GetRenderWindow()->AddRenderer(m_McRender);		
}
//更改等值点
void CMy3DVisualView::ChangeSkinValue(UINT SkinValue)
{
	m_McSkinExtractor->SetValue(0, SkinValue);
	m_McRender->Render();	
	mfcWin->RedrawWindow();
}
//更改背景色
void CMy3DVisualView::ChangeMCBkColor(float r,float g,float b)
{
	// TODO: 在此添加命令处理程序代码
	m_McRender->SetBackground(r,g,b);
	m_McRender->Render();
	mfcWin->RedrawWindow();
}
//更改透明度
void CMy3DVisualView::ChangeMCOpacity(float opacity)
{
	m_McActor->GetProperty()->SetOpacity(opacity);
	mfcWin->RedrawWindow();
}

//更改漫反射颜色
void CMy3DVisualView::ChangeMCSkinColor(float r,float g,float b)
{
	// TODO: 在此添加命令处理程序代码
	m_McActor->GetProperty()->SetDiffuseColor(r,g,b);	
	m_McRender->Render();
	mfcWin->RedrawWindow();
}
//更改漫反射强度
void CMy3DVisualView::ChangeMCDiffuse(double diffuse)
{
	// TODO: 在此添加命令处理程序代码
	m_McActor->GetProperty()->SetDiffuse(diffuse);	
	mfcWin->RedrawWindow();
}
//更改环境颜色
void CMy3DVisualView::ChangeMCAmbientColor(float r,float g,float b)
{
	// TODO: 在此添加命令处理程序代码
	m_McActor->GetProperty()->SetAmbientColor(r,g,b);
	mfcWin->RedrawWindow();
}

//更改环境强度
void CMy3DVisualView::ChangeMCAmbient(double ambient)
{
	// TODO: 在此添加命令处理程序代码
	m_McActor->GetProperty()->SetAmbient(ambient);
	mfcWin->RedrawWindow();
}

//更改镜面反射颜色
void CMy3DVisualView::ChangeMCSpecularColor(float r,float g,float b)
{
	// TODO: 在此添加命令处理程序代码
	m_McActor->GetProperty()->SetSpecularColor(r,g,b);
	mfcWin->RedrawWindow();
}

//更改镜面反射强度
void CMy3DVisualView::ChangeMCSpecular(double specular)
{
	m_McActor->GetProperty()->SetSpecular(specular);
	mfcWin->RedrawWindow();
}


///////////////////////////////////////
//RayCasting实现
//////////////////////////////////////


void CMy3DVisualView::RayCasting()
{
	/*if(data_fg==1)
	{
		CMy3DVisualDoc* pDoc = GetDocument();
		pDoc->Dicomreader->Update();
		readerImageCast->SetInputConnection(pDoc->Dicomreader->GetOutputPort());		
	}
	if(data_fg ==2)
	{
		CMy3DVisualDoc* pDoc = GetDocument();
		pDoc->Bmpreader->Update();		
		m_Bmpsample->SetAxisMagnificationFactor(0,pDoc->samplevalue);
		m_Bmpsample->SetAxisMagnificationFactor(1,pDoc->samplevalue);
		m_Bmpsample->SetAxisMagnificationFactor(2,pDoc->samplevalue);
		m_Bmpsample->SetInputConnection(pDoc->Bmpreader->GetOutputPort());
		m_Bmpsample->Update();
		readerImageCast->SetInputConnection(m_Bmpsample->GetOutputPort());
	}	
	if(data_fg ==3)
	{
		CMy3DVisualDoc* pDoc = GetDocument();
		pDoc->Binreader->Update();		
		m_Binsample->SetAxisMagnificationFactor(0,pDoc->samplevalue);
		m_Binsample->SetAxisMagnificationFactor(1,pDoc->samplevalue);
		m_Binsample->SetAxisMagnificationFactor(2,pDoc->samplevalue);
		m_Binsample->SetInputConnection(pDoc->Binreader->GetOutputPort());
		m_Binsample->Update();		
		readerImageCast->SetInputConnection(m_Binsample->GetOutputPort());
	}
*/
	CMy3DVisualDoc* pDoc = GetDocument();
	pDoc->Dicomreader->Update();
	origin_data = pDoc->Dicomreader->GetOutput();

	vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper> RcGpuMapper = vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper>::New();
	RcGpuMapper->SetInputData(origin_data);

	int imageDims[3];
	origin_data->GetDimensions(imageDims);
	cout << "dimension[] :" << imageDims[0] << " " << imageDims[1] << " " << imageDims[2] << endl;
	if (imageDims[0] == 0 || imageDims[1] == 0 || imageDims[2] == 0)
		return;

	////Mapper
	//vtkSmartPointer<vtkGPUVolumeRayCastMapper> RcGpuMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	//RcGpuMapper->SetInputData(origin_data);

	//vtkVolumeProperty
	volumeProperty->RemoveAllObservers();
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();
	volumeProperty->SetAmbient(0.1);
	volumeProperty->SetDiffuse(0.9);
	volumeProperty->SetSpecular(0.2);
	volumeProperty->SetSpecularPower(10.0);

	opacityTransferFunction->AddPoint(50, 0.0);
	opacityTransferFunction->AddPoint(120, 0.5);
	opacityTransferFunction->AddPoint(200, 1.0);
	volumeProperty->SetScalarOpacity(opacityTransferFunction);//不透明度

	colorTransferFunction->AddRGBPoint(0.0, 0.5, 0.5, 0.5);//添加色彩点（第一个参数索引）
	colorTransferFunction->AddRGBPoint(60.0, 0, 1.0, 0.0);
	colorTransferFunction->AddRGBPoint(150.0, 0, 0, 1);
	colorTransferFunction->AddRGBPoint(200, 0.8, 0.8, 0.8);	
	volumeProperty->SetColor(colorTransferFunction);

	//gradientTransferFunction->AddPoint(30, 2.0);
	//gradientTransferFunction->AddPoint(60, 2.0);
	//gradientTransferFunction->AddSegment (128, 0.73, 900, 0.9);
	//gradientTransferFunction->AddPoint(255, 0.1);

	gradientTransferFunction->AddPoint(1, 0.0);
	gradientTransferFunction->AddPoint(70, 0.5);
	gradientTransferFunction->AddPoint(130, 1.0);

	volumeProperty->SetGradientOpacity(gradientTransferFunction);

	//volumeProperty->SetScalarOpacity(volumeScalarOpacity);

	//volume
	volume->RemoveAllObservers();
	volume->SetMapper(RcGpuMapper);
	volume->SetProperty(volumeProperty);

	//render
	volume_render->AddViewProp(volume);
	mfcWin->GetRenderWindow()->AddRenderer(volume_render);
	mfcWin->GetRenderWindow()->Render();


		
	//readerImageCast->SetOutputScalarTypeToUnsignedChar();//SetOutputScalarTypeToUnsignedShort ();
	//readerImageCast->ClampOverflowOn();//阀值	
	////设置不透明度传递函数
	//opacityTransferFunction->AddPoint(30, 0.0);
	//opacityTransferFunction->AddPoint(100, 0.2);
	//opacityTransferFunction->AddPoint(220, 0.8);
	////设置颜色传递函数//该函数确定体绘像素的颜色值或者灰度值
	//colorTransferFunction->AddRGBPoint(0.0, 0.5, 0.5, 0.5);//添加色彩点（第一个参数索引）
	//colorTransferFunction->AddRGBPoint(60.0, 0, 1.0, 0.0);
	//colorTransferFunction->AddRGBPoint(150.0, 0, 0, 1);
	//colorTransferFunction->AddRGBPoint(200, 0.8, 0.8, 0.8);	
	////设置梯度传递函数	
	//gradientTransferFunction->AddPoint(0, 2.0);
	//gradientTransferFunction->AddPoint(60, 2.0);
	//gradientTransferFunction-> AddSegment (128, 0.73, 900, 0.9);
	//gradientTransferFunction->AddPoint(255, 0.1);

	////设定一个体绘容器的属性
	//volumeProperty->SetColor(colorTransferFunction);//设置颜色
	//volumeProperty->SetScalarOpacity(opacityTransferFunction);//不透明度
	//volumeProperty->SetGradientOpacity(gradientTransferFunction);//梯度设置
	//volumeProperty->ShadeOn();//影阴
	//volumeProperty->SetInterpolationTypeToLinear();//直线与样条插值之间逐发函数
	//volumeProperty->SetAmbient(0.2);//环境光系数
	//volumeProperty->SetDiffuse(0.9);//漫反射
	//volumeProperty->SetSpecular(0.2);//高光系数
	//volumeProperty->SetSpecularPower(10); //高光强度
		
	//if(m_VRAlgorithmType==0)
	//{
	//	//RC算法，合成光线投射算法
	//	vtkSmartPointer<vtkVolumeRayCastCompositeFunction> rc =  vtkVolumeRayCastCompositeFunction::New();
	//	volumeMapper->SetVolumeRayCastFunction(rc); 	
	//}
	//else if(m_VRAlgorithmType==1)
	//{
	//	//MIP算法,最大密度投影算法
	//	vtkSmartPointer<vtkVolumeRayCastMIPFunction> mip = vtkSmartPointer<vtkVolumeRayCastMIPFunction> ::New();
	//	mip->SetMaximizeMethodToOpacity();
	//	volumeMapper->SetVolumeRayCastFunction(mip); 		
	//}
	//else	
	//{
	//	//ISO算法，等值面光线投射绘制
	//	vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction> iso =  vtkVolumeRayCastIsosurfaceFunction::New();	
	//	iso->SetIsoValue(50);
	//	volumeMapper->SetVolumeRayCastFunction(iso); 
	//}


	//	
	//volumeMapper->SetInputConnection(readerImageCast->GetOutputPort());//图像数据输入
	//volumeMapper->SetNumberOfThreads(3);

	//volume->SetMapper(volumeMapper);
	//volume->SetProperty(volumeProperty);//设置体属性
	//m_VrRender->AddVolume(volume);//将Volume装载到绘制类中
	//mfcWin->GetInteractor()->SetInteractorStyle(style);	
	//mfcWin->GetRenderWindow()->AddRenderer(m_VrRender);		
}


void CMy3DVisualView::ReSetISOValue(int isovalue)
{
	/*vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction> iso =  vtkVolumeRayCastIsosurfaceFunction::New();	
	iso->SetIsoValue(isovalue);
	volumeMapper->SetVolumeRayCastFunction(iso); 
	mfcWin->RedrawWindow();*/
}

void CMy3DVisualView::ChangeVRBkColor(float r,float g,float b)
{
	// TODO: 在此添加命令处理程序代码
	m_VrRender->SetBackground(r,g,b);
	m_VrRender->Render();
	mfcWin->RedrawWindow();
}

void CMy3DVisualView::ReSetOPACITY(int gray1,int gray2,int gray3,float level1,float level2,float level3)
{
	opacityTransferFunction->RemoveAllPoints();
	opacityTransferFunction->AddPoint(gray1, level1);
	opacityTransferFunction->AddPoint(gray2, level2);
	opacityTransferFunction->AddPoint(gray3, level3);
	mfcWin->RedrawWindow();
}

void CMy3DVisualView::ReSetColor(int gray1,int gray2,int gray3,int gray4,
	COLORREF ref1,COLORREF ref2,COLORREF ref3,COLORREF ref4)
{
	colorTransferFunction->RemoveAllPoints();
	BYTE r = GetRValue(ref1);
	BYTE g = GetGValue(ref1);
	BYTE b = GetBValue(ref1);
	float R = (float)r / 255.0;
	float G  = (float)g / 255.0;
	float B  = (float)b / 255.0;
	colorTransferFunction->AddRGBPoint(gray1, R, G, B);
	BYTE rr = GetRValue(ref2);
	BYTE gg = GetGValue(ref2);
	BYTE bb = GetBValue(ref2);
	float RR = (float)rr / 255.0;
	float GG  = (float)gg / 255.0;
	float BB  = (float)bb / 255.0;
	colorTransferFunction->AddRGBPoint(gray2, RR, GG, BB);
	BYTE rrr = GetRValue(ref2);
	BYTE ggg = GetGValue(ref2);
	BYTE bbb = GetBValue(ref2);
	float RRR = (float)rrr / 255.0;
	float GGG  = (float)ggg / 255.0;
	float BBB  = (float)bbb / 255.0;
	colorTransferFunction->AddRGBPoint(gray3, RRR, GGG, BBB);
	BYTE rrrr = GetRValue(ref2);
	BYTE gggg = GetGValue(ref2);
	BYTE bbbb = GetBValue(ref2);
	float RRRR = (float)rrrr / 255.0;
	float GGGR  = (float)gggg / 255.0;
	float BBBB  = (float)bbbb / 255.0;
	colorTransferFunction->AddRGBPoint(gray4, RRRR, GGGR, BBBB);		
	mfcWin->RedrawWindow();
}


void CMy3DVisualView::Capture(CString path,CString name)
{
	/*vtkWindowToImageFilter * wif = vtkWindowToImageFilter::New();
	vtkBMPWriter *bmpw = vtkBMPWriter::New();
	wif->SetInput(mfcWin->GetRenderWindow());
	bmpw->SetInput(wif->GetOutput());
	CString savepath = path + "\\" + name +".bmp";
	bmpw->SetFileName(savepath);
	bmpw->Write();*/
}


void CMy3DVisualView::VRVolumeCut()
{
	//vtkVRBoxWidgetCallback * callback = vtkVRBoxWidgetCallback::New();
	//callback->volumeMapper = volumeMapper;	
	//boxWidget = vtkBoxWidget::New();
	//boxWidget->SetInteractor(mfcWin->GetRenderWindow()->GetInteractor());
	//boxWidget->SetPlaceFactor(0.75);
	//boxWidget->SetInput((vtkDataSet*)readerImageCast->GetOutput());
	//boxWidget->PlaceWidget();
	//boxWidget->InsideOutOn();
	//boxWidget->SetInsideOut(1);
	//boxWidget->GetOutlineProperty()->SetRepresentationToSurface();
	//boxWidget->GetOutlineProperty()->SetOpacity(0.1);
	//boxWidget->On();
	//boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
	
}

void CMy3DVisualView::VRVolumeCutCancel()
{
	if(boxWidget)
		boxWidget->Off();	
}


void CMy3DVisualView::MCVolumeCut()
{
	/*vtkMCBoxWidgetCallback * callback = vtkMCBoxWidgetCallback::New();
	callback->volumeMapper = m_McMapper;	
	boxWidget = vtkBoxWidget::New();
	boxWidget->SetInteractor(mfcWin->GetRenderWindow()->GetInteractor());
	boxWidget->SetPlaceFactor(0.75);
	boxWidget->SetInput((vtkDataSet*)readerImageCast->GetOutput());
	boxWidget->PlaceWidget();
	boxWidget->InsideOutOn();
	boxWidget->SetInsideOut(1);
	boxWidget->GetOutlineProperty()->SetRepresentationToSurface();
	boxWidget->GetOutlineProperty()->SetOpacity(0.1);
	boxWidget->On();
	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);*/
	return;
}

void CMy3DVisualView::MCVolumeCutCancel()
{
	/*if(boxWidget)
	boxWidget->Off();*/
	return;
}


void CMy3DVisualView::SaveStl(CString folder,CString name)
{
	//vtkTriangleFilter *triangleFilter = vtkTriangleFilter::New();	
	//triangleFilter->SetInput(m_McSkinStripper->GetOutput());
	////做简化
	//vtkDecimatePro *deciFilter = vtkDecimatePro::New();
	//deciFilter->SetInputConnection(triangleFilter->GetOutputPort());
	//deciFilter->SetTargetReduction(0.1); //简化为原来的10%
	//deciFilter->PreserveTopologyOn();//保持原始网格拓扑结构	
	////做平滑	
	//vtkSmoothPolyDataFilter *smoothFilter = vtkSmoothPolyDataFilter::New();
	//smoothFilter->SetInputConnection(deciFilter->GetOutputPort());	
	//smoothFilter->SetNumberOfIterations(100);//设置平滑的次数
	//smoothFilter->FeatureEdgeSmoothingOn();	//开启尖锐特征平滑
	//vtkSmartPointer<vtkSTLWriter> stlWriter =
	//	vtkSmartPointer<vtkSTLWriter>::New();
	//CString savepath = folder + "\\" + name +".stl";
	//stlWriter->SetFileName(savepath);
	//stlWriter->SetInputConnection(smoothFilter->GetOutputPort());	
	//stlWriter->Write();
}
