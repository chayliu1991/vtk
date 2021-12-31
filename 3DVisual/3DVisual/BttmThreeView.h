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

#include "vtkImageHybridMedian2D.h"
#include <vtkImageImport.h>
#include <vtkBMPWriter.h>
#include <vtkBMPReader.h>
#include "vtkImageThreshold.h"
// CBttmThreeView 视图

class CBttmThreeView : public CView
{
	DECLARE_DYNCREATE(CBttmThreeView)

protected:
	CBttmThreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~CBttmThreeView();

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
	vtkRenderer* m_SliceRender3;
	vtkMFCWindow* mfcWinSlice3;
	vtkImageActor* m_SliceActor3;
	vtkImageMapToColors *colorMap3;
	vtkImagePlaneWidget *planeWight3;
	vtkProperty *ipwProp3;
	vtkTextProperty * sliceZTextProp;	
	vtkTextMapper *sliceZTextMapper1;
	vtkActor2D* sliceZTextActor1;
	vtkTextMapper *sliceZTextMapper2;
	vtkActor2D* sliceZTextActor2;
	

	vtkImageHybridMedian2D* hybridMedian;
public:
	void DisplaySlice3(vtkDataSet* input);	
	void SetSliceZ(int SliceIndex);
	vtkImageData * imageData ;
	void ChangeWindowLevel(double window, double level);
	void ChangeZBkColor(float r,float g,float b);
	void SetLayerText(int index);
	void LeftRotation();
	void RightRotation();
	void HoriMirror();
	void VertiMirror();
	void MeanFilter();
	void AnisotropyFilter(int InteraNum,double DiffThread);
	void MeDianFilter();	
	void GaussSmooth(int GaussTemplateSize, float GaussTempltateSd);
	void Binaryzation();
	void EdgeDetection();
	void WriteBmpZ(CString FolderName,CString FileName,int RangeMin,int RangeMax);
	void HistormZ();
	void Capture(CString path,CString name);
	void BinaryZ(int value);
	
};


