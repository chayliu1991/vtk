
// 3DVisualDoc.h : CMy3DVisualDoc 类的接口
//


#pragma once
#include "vtkSmartPointer.h"
#include <vtkDICOMImageReader.h>
#include "vtkBMPReader.h"
#include "vtkImageResample.h"


#include "BttmView.h"
#include "BttmOneView.h"
#include "BttmTwoView.h"
#include "BttmThreeView.h"

class CMy3DVisualDoc : public CDocument
{
protected: // 仅从序列化创建
	CMy3DVisualDoc();
	DECLARE_DYNCREATE(CMy3DVisualDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMy3DVisualDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	vtkSmartPointer<vtkDICOMImageReader> Dicomreader;//Dicom文件指针
	vtkSmartPointer<vtkBMPReader> Bmpreader;	
	afx_msg void OnDicomopen();
	void SetDicomSlice();
	afx_msg void OnBmpopen();	
	void SetBmpSlice();
	void InitSliceDlg();
	float samplevalue ;
	afx_msg void OnBinopen();
	vtkImageReader *Binreader;
};
