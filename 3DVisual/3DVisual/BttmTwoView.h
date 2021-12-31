#pragma once


// CBttmTwoView 视图
#include <vtkRenderer.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include "vtkMFCWindow.h"
#include <vtkProperty.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkImageMapToColors.h"
#include "vtkImagePlaneWidget.h"
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include "vtkTextProperty.h"
#include "vtkTextMapper.h"
#include "vtkActor2D.h"

class CBttmTwoView : public CView
{
	DECLARE_DYNCREATE(CBttmTwoView)

protected:
	CBttmTwoView();           // 动态创建所使用的受保护的构造函数
	virtual ~CBttmTwoView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:		
	COLORREF m_backgroundColor;	
	COLORREF m_frontgroundColor;
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
public:
	vtkRenderer* m_SliceRender2;
	vtkMFCWindow* mfcWinSlice2;
	vtkImageActor* m_SliceActor2;
	vtkImageMapToColors *colorMap2;
	vtkImagePlaneWidget *planeWight2;
	vtkProperty *ipwProp2;
	vtkTextProperty * sliceYTextProp;	
	vtkTextMapper *sliceYTextMapper1;
	vtkActor2D* sliceYTextActor1;
	vtkTextMapper *sliceYTextMapper2;
	vtkActor2D* sliceYTextActor2;
public:
	void DisplaySlice2(vtkDataSet* input);	
	void SetSliceY(int SliceIndex);
	vtkImageData * imageData ;
	void ChangeWindowLevel(double window, double level);
	void ChangeYBkColor(float r,float g,float b);
	void SetLayerText(int index);
	void LeftRotation();
	void RightRotation();
	void HoriMirror();
	void VertiMirror();
	void AnisotropyFilter(int InteraNum,double DiffThread);
	void MeDianFilter();
	void GaussSmooth(int GaussTemplateSize, float GaussTempltateSd);
	void MeanFilter();
	void EdgeDetection();
	void WriteBmpY(CString FolderName,CString FileName,int RangeMin,int RangeMax);
	void HistormY();
	void Capture(CString path,CString name);
	void BinaryY(int value);
};

