#pragma once
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

// CBttmOneView 视图

class CBttmOneView : public CView
{
	DECLARE_DYNCREATE(CBttmOneView)

public:
	CBttmOneView();           // 动态创建所使用的受保护的构造函数
	virtual ~CBttmOneView();

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
	vtkRenderer* m_SliceRender1;
	vtkMFCWindow* mfcWinSlice1;
	vtkImageActor* m_SliceActor1;
	vtkImageMapToColors *colorMap1;
	vtkImagePlaneWidget *planeWight1;
	vtkProperty *ipwProp1;
	vtkTextProperty * sliceXTextProp;	
	vtkTextMapper *sliceXTextMapper1;
	vtkActor2D* sliceXTextActor1;
	vtkTextMapper *sliceXTextMapper2;
	vtkActor2D* sliceXTextActor2;
public:	
	void DisplaySlice1(vtkDataSet* input);	
	void SetSliceX(int SliceIndex);
	vtkImageData * imageData ;
	void ChangeWindowLevel(double window, double level);
	void ChangeXBkColor(float r,float g,float b);
	void SetLayerText(int index);
	void LeftRotation();
	void RightRotation();
	void HoriMirror();
	void VertiMirror();
	void MeanFilter();	
	void AnisotropyFilter(int InteraNum,double DiffThread);
	void MeDianFilter();
	void GaussSmooth(int GaussTemplateSize, float GaussTempltateSd);
	void EdgeDetection();
	void WriteBmpX(CString FolderName,CString FileName,int RangeMin,int RangeMax);	
	void HistormX();
	CString m_captureFolder;
	CString m_CaptureName;	
	afx_msg void OnZoxcapture();
	void Capture(CString path,CString name);
	void BinaryX(int value);
};


