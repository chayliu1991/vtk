// BttmView.cpp : 实现文件
//

#include "stdafx.h"
#include "3DVisual.h"
#include "BttmView.h"
#include "BttmOneView.h"
#include "BttmTwoView.h"
#include "BttmThreeView.h"


// CBttmView

IMPLEMENT_DYNCREATE(CBttmView, CView)

CBttmView::CBttmView()
{

}

CBttmView::~CBttmView()
{
}

BEGIN_MESSAGE_MAP(CBttmView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CBttmView 绘图

void CBttmView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CBttmView 诊断

#ifdef _DEBUG
void CBttmView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBttmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBttmView 消息处理程序


int CBttmView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rect;
	GetClientRect(&rect); // 获得窗口的创建信息指针
	CCreateContext *pContext=(CCreateContext *)lpCreateStruct->lpCreateParams;
	m_splitWnd2.CreateStatic(this,1,3); //产生第二次的静态分割
	m_splitWnd2.CreateView(0,0,RUNTIME_CLASS(CBttmOneView),CSize(rect.Width()/3 ,rect.Height()),pContext);
	m_splitWnd2.CreateView(0,1,RUNTIME_CLASS(CBttmTwoView),CSize(rect.Width()/3 ,rect.Height()),pContext);
	m_splitWnd2.CreateView(0,2,RUNTIME_CLASS(CBttmThreeView),CSize(rect.Width()/3 ,rect.Height()),pContext);	
	return 0;
}


void CBttmView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(&rect);
	int x=rect.Width();
	int y=rect.Height();
	m_splitWnd2.MoveWindow(0,0,x,y+3);
	m_splitWnd2.SetColumnInfo(0,x/3,0); 
	m_splitWnd2.SetColumnInfo(1,x/3,0); 
	m_splitWnd2.SetColumnInfo(2,x/3,0); 
	m_splitWnd2.RecalcLayout();
}
