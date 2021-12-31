
// 3DVisualDoc.h : CMy3DVisualDoc ��Ľӿ�
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
protected: // �������л�����
	CMy3DVisualDoc();
	DECLARE_DYNCREATE(CMy3DVisualDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMy3DVisualDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	vtkSmartPointer<vtkDICOMImageReader> Dicomreader;//Dicom�ļ�ָ��
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
