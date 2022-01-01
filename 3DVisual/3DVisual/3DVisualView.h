
// 3DVisualView.h : CMy3DVisualView 类的接口
//

#pragma once
#include <vtkRenderer.h>
#include <vtkMarchingCubes.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkDICOMImageReader.h>
#include "vtkMFCWindow.h"
#include <vtkProperty.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
//#include "vtkVolumeRayCastCompositeFunction.h"
//#include "vtkVolumeRayCastMapper.h"
#include "vtkVolume.h"
#include "vtkImageCast.h"
//#include "vtkVolumeRayCastMIPFunction.h"
#include "vtkPiecewiseFunction.h"
//#include "vtkVolumeRayCastIsosurfaceFunction.h"


#include "vtkCommand.h"
#include "vtkBoxWidget.h"
#include "vtkPlanes.h"
//#include "vtkVolumeRayCastMapper.h"
//#include "vtkImplicitPlaneWidget.h"
#include "vtkPlane.h"
#include "vtkVolume.h"


class CMy3DVisualView : public CView
{
protected: // 仅从序列化创建
	CMy3DVisualView();
	DECLARE_DYNCREATE(CMy3DVisualView)

// 特性
public:
	CMy3DVisualDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy3DVisualView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	COLORREF m_backgroundColor;
	COLORREF m_frontgroundColor;	
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);


public:
	//面绘制与体绘制共用的变量
	vtkMFCWindow* mfcWin;
	vtkInteractorStyleTrackballCamera *style;
public:
	//面绘制Marchingcubes算法
	void MarchingCubes();
	vtkRenderer* m_McRender;
	vtkMarchingCubes *m_McSkinExtractor;
	vtkStripper* m_McSkinStripper;
	vtkPolyDataMapper* m_McMapper;
	vtkActor* m_McActor;	
	vtkImageResample* m_Bmpsample;
	vtkImageResample* m_Binsample;
public:
	void ChangeSkinValue(UINT SkinValue);
	void ChangeMCBkColor(float r,float g,float b);
	void ChangeMCSkinColor(float r,float g,float b);
	void ChangeMCDiffuse(double diffuse);
	void ChangeMCAmbientColor(float r,float g,float b);
	void ChangeMCAmbient(double ambient);
	void ChangeMCOpacity(float opacity);
	void ChangeMCSpecular(double specular);	
	void ChangeMCSpecularColor(float r,float g,float b);
public:
	//体绘制RayCasting算法
	vtkSmartPointer<vtkColorTransferFunction> volumeColor;
	vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity;
	vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity;
	vtkSmartPointer<vtkRenderer> volume_render;
	vtkSmartPointer<vtkImageData> origin_data;

	void RayCasting();
	vtkRenderer* m_VrRender;
	vtkPiecewiseFunction *opacityTransferFunction;
	vtkColorTransferFunction *colorTransferFunction;
	vtkVolumeProperty *volumeProperty ;	
	vtkPolyDataMapper *volumeMapper ;

	vtkVolume *volume;
	vtkImageCast *readerImageCast;
	vtkPiecewiseFunction *gradientTransferFunction;
	void ReSetISOValue(int isovalue);
	void ChangeVRBkColor(float r,float g,float b);
	void ReSetOPACITY(int gray1,int gray2,int gray3,float level1,float level2,float level3);
	void ReSetColor(int gray1,int gray2,int gray3,int gray4,
		COLORREF ref1,COLORREF ref2,COLORREF ref3,COLORREF ref4);
	vtkBoxWidget *boxWidget;
	void VRVolumeCut();
	void VRVolumeCutCancel();	
	void MCVolumeCut();
	void MCVolumeCutCancel();
	void Capture(CString path,CString name);
	CString m_captureFolder;
	CString m_CaptureName;		
	void SaveStl(CString folder,CString name);
};


#ifndef _DEBUG  // 3DVisualView.cpp 中的调试版本
inline CMy3DVisualDoc* CMy3DVisualView::GetDocument() const
{ return reinterpret_cast<CMy3DVisualDoc*>(m_pDocument); }
#endif



class vtkMCBoxWidgetCallback : public vtkCommand
{
public:
	static vtkMCBoxWidgetCallback *New()
	{ return new vtkMCBoxWidgetCallback ; }
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkBoxWidget *boxWidget =
			reinterpret_cast<vtkBoxWidget*>(caller);
		boxWidget->GetPlanes(planes);
		this->volumeMapper->RemoveAllClippingPlanes();
		planes->GetPlane(0,plane0);
		planes->GetPlane(1,plane1);
		planes->GetPlane(2,plane2);
		planes->GetPlane(3,plane3);
		planes->GetPlane(4,plane4);
		planes->GetPlane(5,plane5);
		volumeMapper->AddClippingPlane(plane0);
		volumeMapper->AddClippingPlane(plane1);
		volumeMapper->AddClippingPlane(plane2);
		volumeMapper->AddClippingPlane(plane3);
		volumeMapper->AddClippingPlane(plane4);
		volumeMapper->AddClippingPlane(plane5);

	};
	vtkPolyDataMapper* volumeMapper;
	vtkMCBoxWidgetCallback (void)
	{
		this->planes = vtkPlanes::New();
		this->plane0 = vtkPlane::New();
		this->plane1 = vtkPlane::New();
		this->plane2 = vtkPlane::New();
		this->plane3 = vtkPlane::New();
		this->plane4 = vtkPlane::New();
		this->plane5 = vtkPlane::New();
	}
protected:
	vtkPlanes *planes;
	vtkPlane  *plane0;
	vtkPlane  *plane1;
	vtkPlane  *plane2;
	vtkPlane  *plane3;
	vtkPlane  *plane4;
	vtkPlane  *plane5;
};


class vtkVRBoxWidgetCallback : public vtkCommand
{
public:
	static vtkVRBoxWidgetCallback *New()
	{ return new vtkVRBoxWidgetCallback ; }
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkBoxWidget *boxWidget =
			reinterpret_cast<vtkBoxWidget*>(caller);
		boxWidget->GetPlanes(planes);
		//this->volumeMapper->RemoveAllClippingPlanes();
		planes->GetPlane(0,plane0);
		planes->GetPlane(1,plane1);
		planes->GetPlane(2,plane2);
		planes->GetPlane(3,plane3);
		planes->GetPlane(4,plane4);
		planes->GetPlane(5,plane5);
		//volumeMapper->AddClippingPlane(plane0);
		//volumeMapper->AddClippingPlane(plane1);
		//volumeMapper->AddClippingPlane(plane2);
		//volumeMapper->AddClippingPlane(plane3);
		//volumeMapper->AddClippingPlane(plane4);
		//volumeMapper->AddClippingPlane(plane5);

	};

//vtkVolumeRayCastMapper* volumeMapper;

	vtkVRBoxWidgetCallback (void)
	{
		this->planes = vtkPlanes::New();
		this->plane0 = vtkPlane::New();
		this->plane1 = vtkPlane::New();
		this->plane2 = vtkPlane::New();
		this->plane3 = vtkPlane::New();
		this->plane4 = vtkPlane::New();
		this->plane5 = vtkPlane::New();
	}
protected:
	vtkPlanes *planes;
	vtkPlane  *plane0;
	vtkPlane  *plane1;
	vtkPlane  *plane2;
	vtkPlane  *plane3;
	vtkPlane  *plane4;
	vtkPlane  *plane5;
};

