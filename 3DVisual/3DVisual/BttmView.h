#pragma once
#include "MySplitWnd.h"

// CBttmView ��ͼ

class CBttmView : public CView
{
	DECLARE_DYNCREATE(CBttmView)

protected:
	CBttmView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBttmView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	CMySplitWnd m_splitWnd2;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


