
// 3DVisualView.cpp : CMy3DVisualView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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




////////////////ȫ�ֱ���
extern UINT data_fg ;
extern int m_VRAlgorithmType;

// CMy3DVisualView

IMPLEMENT_DYNCREATE(CMy3DVisualView, CView)

BEGIN_MESSAGE_MAP(CMy3DVisualView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy3DVisualView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()		
END_MESSAGE_MAP()

// CMy3DVisualView ����/����

CMy3DVisualView::CMy3DVisualView()
{
	// TODO: �ڴ˴���ӹ������	
	//���ñ�����ʼ��
	m_backgroundColor = RGB(0, 0, 0);
	m_frontgroundColor = RGB(255,0, 0);
	mfcWin = NULL;
	style =	vtkInteractorStyleTrackballCamera::New();	
	//MC�㷨��ʼ������
	m_McRender = vtkRenderer::New();//����������
	m_McSkinExtractor = vtkMarchingCubes::New();//����Marching Cubes �㷨�Ķ���
	m_McSkinStripper = vtkStripper::New();//�������Ǵ�����
	m_McMapper = vtkPolyDataMapper::New();//����һ������ӳ�����
	m_McActor = vtkActor::New();//����һ������Ƥ������Ա
	m_Bmpsample = vtkImageResample::New();	
	m_Binsample = vtkImageResample::New();
	//VR�㷨��ʼ������
	m_VrRender = vtkRenderer::New();
	opacityTransferFunction = vtkPiecewiseFunction::New();
	colorTransferFunction = vtkColorTransferFunction::New();
	volumeProperty = vtkVolumeProperty::New();	
	volumeMapper = vtkPolyDataMapper::New(); //�������	
	volume = vtkVolume::New();//��ʾ͸ʾͼ�е�һ����ά����
	readerImageCast = vtkImageCast::New();//��������ת��
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy3DVisualView ����

void CMy3DVisualView::OnDraw(CDC* pDC)
{
	CMy3DVisualDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rc;
	GetClientRect(&rc);
	CBrush br(m_backgroundColor);
	pDC->FillRect(&rc,&br);	
	pDC->Draw3dRect(rc, m_frontgroundColor, m_frontgroundColor);
	rc.DeflateRect(1, 1);
	pDC->Draw3dRect(rc, m_frontgroundColor, m_frontgroundColor);
}


// CMy3DVisualView ��ӡ


void CMy3DVisualView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy3DVisualView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy3DVisualView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy3DVisualView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CMy3DVisualView ���

#ifdef _DEBUG
void CMy3DVisualView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DVisualView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DVisualDoc* CMy3DVisualView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DVisualDoc)));
	return (CMy3DVisualDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DVisualView ��Ϣ�������


void CMy3DVisualView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//����VtkMFCWindow,���ƶ�renderwindow�Ĵ�С��Ϊ��ʹ�߿���ɫ�ܹ���ʾ����
	//ʹ����С��Client�Ĵ�С���ɡ�
	mfcWin = new vtkMFCWindow(this);	
	(mfcWin->GetRenderWindow())->SetPosition(2,2);
	CRect rect;
	GetClientRect(&rect);
	(mfcWin->GetRenderWindow())->SetSize(rect.Width()-4,rect.Height()-4);
}


void CMy3DVisualView::OnDestroy()
{
	CView::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
	//����MC�㷨�е������Դ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return FALSE;
}

///////////////////////////////////////
//Marching Cubesʵ��
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
	//deciFilter->SetTargetReduction(0.3); //��Ϊԭ����10%
	//deciFilter->PreserveTopologyOn();//����ԭʼ�������˽ṹ	
	////��ƽ��	
	//vtkSmoothPolyDataFilter *smoothFilter = vtkSmoothPolyDataFilter::New();
	//smoothFilter->SetInputConnection(deciFilter->GetOutputPort());	
	//smoothFilter->SetNumberOfIterations(10);//����ƽ���Ĵ���
	//smoothFilter->FeatureEdgeSmoothingOn();	//������������ƽ��

	//m_McSkinStripper->SetInputConnection(m_McSkinExtractor->GetOutputPort());

	m_McSkinStripper->SetInputConnection(m_McSkinExtractor->GetOutputPort());

	m_McMapper->ScalarVisibilityOff();
	m_McMapper->SetInputData(m_McSkinStripper->GetOutput());
	m_McActor->GetProperty()->SetDiffuseColor(0,1,0);
	m_McActor->GetProperty()->SetSpecular(0.3);     //���÷�����
	m_McActor->GetProperty()->SetSpecularPower(100); //���÷����ǿ�� 
	m_McActor->SetMapper(m_McMapper);
	m_McActor->GetProperty()->SetOpacity(1);
	m_McRender->AddActor(m_McActor);
	m_McRender->SetBackground(0,0,0);		
	mfcWin->GetInteractor()->SetInteractorStyle(style);	
	mfcWin->GetRenderWindow()->AddRenderer(m_McRender);		
}
//���ĵ�ֵ��
void CMy3DVisualView::ChangeSkinValue(UINT SkinValue)
{
	m_McSkinExtractor->SetValue(0, SkinValue);
	m_McRender->Render();	
	mfcWin->RedrawWindow();
}
//���ı���ɫ
void CMy3DVisualView::ChangeMCBkColor(float r,float g,float b)
{
	// TODO: �ڴ���������������
	m_McRender->SetBackground(r,g,b);
	m_McRender->Render();
	mfcWin->RedrawWindow();
}
//����͸����
void CMy3DVisualView::ChangeMCOpacity(float opacity)
{
	m_McActor->GetProperty()->SetOpacity(opacity);
	mfcWin->RedrawWindow();
}

//������������ɫ
void CMy3DVisualView::ChangeMCSkinColor(float r,float g,float b)
{
	// TODO: �ڴ���������������
	m_McActor->GetProperty()->SetDiffuseColor(r,g,b);	
	m_McRender->Render();
	mfcWin->RedrawWindow();
}
//����������ǿ��
void CMy3DVisualView::ChangeMCDiffuse(double diffuse)
{
	// TODO: �ڴ���������������
	m_McActor->GetProperty()->SetDiffuse(diffuse);	
	mfcWin->RedrawWindow();
}
//���Ļ�����ɫ
void CMy3DVisualView::ChangeMCAmbientColor(float r,float g,float b)
{
	// TODO: �ڴ���������������
	m_McActor->GetProperty()->SetAmbientColor(r,g,b);
	mfcWin->RedrawWindow();
}

//���Ļ���ǿ��
void CMy3DVisualView::ChangeMCAmbient(double ambient)
{
	// TODO: �ڴ���������������
	m_McActor->GetProperty()->SetAmbient(ambient);
	mfcWin->RedrawWindow();
}

//���ľ��淴����ɫ
void CMy3DVisualView::ChangeMCSpecularColor(float r,float g,float b)
{
	// TODO: �ڴ���������������
	m_McActor->GetProperty()->SetSpecularColor(r,g,b);
	mfcWin->RedrawWindow();
}

//���ľ��淴��ǿ��
void CMy3DVisualView::ChangeMCSpecular(double specular)
{
	m_McActor->GetProperty()->SetSpecular(specular);
	mfcWin->RedrawWindow();
}


///////////////////////////////////////
//RayCastingʵ��
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
	volumeProperty->SetScalarOpacity(opacityTransferFunction);//��͸����

	colorTransferFunction->AddRGBPoint(0.0, 0.5, 0.5, 0.5);//���ɫ�ʵ㣨��һ������������
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
	//readerImageCast->ClampOverflowOn();//��ֵ	
	////���ò�͸���ȴ��ݺ���
	//opacityTransferFunction->AddPoint(30, 0.0);
	//opacityTransferFunction->AddPoint(100, 0.2);
	//opacityTransferFunction->AddPoint(220, 0.8);
	////������ɫ���ݺ���//�ú���ȷ��������ص���ɫֵ���߻Ҷ�ֵ
	//colorTransferFunction->AddRGBPoint(0.0, 0.5, 0.5, 0.5);//���ɫ�ʵ㣨��һ������������
	//colorTransferFunction->AddRGBPoint(60.0, 0, 1.0, 0.0);
	//colorTransferFunction->AddRGBPoint(150.0, 0, 0, 1);
	//colorTransferFunction->AddRGBPoint(200, 0.8, 0.8, 0.8);	
	////�����ݶȴ��ݺ���	
	//gradientTransferFunction->AddPoint(0, 2.0);
	//gradientTransferFunction->AddPoint(60, 2.0);
	//gradientTransferFunction-> AddSegment (128, 0.73, 900, 0.9);
	//gradientTransferFunction->AddPoint(255, 0.1);

	////�趨һ���������������
	//volumeProperty->SetColor(colorTransferFunction);//������ɫ
	//volumeProperty->SetScalarOpacity(opacityTransferFunction);//��͸����
	//volumeProperty->SetGradientOpacity(gradientTransferFunction);//�ݶ�����
	//volumeProperty->ShadeOn();//Ӱ��
	//volumeProperty->SetInterpolationTypeToLinear();//ֱ����������ֵ֮���𷢺���
	//volumeProperty->SetAmbient(0.2);//������ϵ��
	//volumeProperty->SetDiffuse(0.9);//������
	//volumeProperty->SetSpecular(0.2);//�߹�ϵ��
	//volumeProperty->SetSpecularPower(10); //�߹�ǿ��
		
	//if(m_VRAlgorithmType==0)
	//{
	//	//RC�㷨���ϳɹ���Ͷ���㷨
	//	vtkSmartPointer<vtkVolumeRayCastCompositeFunction> rc =  vtkVolumeRayCastCompositeFunction::New();
	//	volumeMapper->SetVolumeRayCastFunction(rc); 	
	//}
	//else if(m_VRAlgorithmType==1)
	//{
	//	//MIP�㷨,����ܶ�ͶӰ�㷨
	//	vtkSmartPointer<vtkVolumeRayCastMIPFunction> mip = vtkSmartPointer<vtkVolumeRayCastMIPFunction> ::New();
	//	mip->SetMaximizeMethodToOpacity();
	//	volumeMapper->SetVolumeRayCastFunction(mip); 		
	//}
	//else	
	//{
	//	//ISO�㷨����ֵ�����Ͷ�����
	//	vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction> iso =  vtkVolumeRayCastIsosurfaceFunction::New();	
	//	iso->SetIsoValue(50);
	//	volumeMapper->SetVolumeRayCastFunction(iso); 
	//}


	//	
	//volumeMapper->SetInputConnection(readerImageCast->GetOutputPort());//ͼ����������
	//volumeMapper->SetNumberOfThreads(3);

	//volume->SetMapper(volumeMapper);
	//volume->SetProperty(volumeProperty);//����������
	//m_VrRender->AddVolume(volume);//��Volumeװ�ص���������
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
	// TODO: �ڴ���������������
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
	////����
	//vtkDecimatePro *deciFilter = vtkDecimatePro::New();
	//deciFilter->SetInputConnection(triangleFilter->GetOutputPort());
	//deciFilter->SetTargetReduction(0.1); //��Ϊԭ����10%
	//deciFilter->PreserveTopologyOn();//����ԭʼ�������˽ṹ	
	////��ƽ��	
	//vtkSmoothPolyDataFilter *smoothFilter = vtkSmoothPolyDataFilter::New();
	//smoothFilter->SetInputConnection(deciFilter->GetOutputPort());	
	//smoothFilter->SetNumberOfIterations(100);//����ƽ���Ĵ���
	//smoothFilter->FeatureEdgeSmoothingOn();	//������������ƽ��
	//vtkSmartPointer<vtkSTLWriter> stlWriter =
	//	vtkSmartPointer<vtkSTLWriter>::New();
	//CString savepath = folder + "\\" + name +".stl";
	//stlWriter->SetFileName(savepath);
	//stlWriter->SetInputConnection(smoothFilter->GetOutputPort());	
	//stlWriter->Write();
}
