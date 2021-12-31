#pragma once
#include "MySplitWnd.h"

// CBttmView 视图

class CBttmView : public CView
{
	DECLARE_DYNCREATE(CBttmView)

protected:
	CBttmView();           // 动态创建所使用的受保护的构造函数
	virtual ~CBttmView();

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
	CMySplitWnd m_splitWnd2;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


