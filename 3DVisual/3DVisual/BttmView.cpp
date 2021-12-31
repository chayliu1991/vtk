// BttmView.cpp : ʵ���ļ�
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


// CBttmView ��ͼ

void CBttmView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CBttmView ���

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


// CBttmView ��Ϣ�������


int CBttmView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rect;
	GetClientRect(&rect); // ��ô��ڵĴ�����Ϣָ��
	CCreateContext *pContext=(CCreateContext *)lpCreateStruct->lpCreateParams;
	m_splitWnd2.CreateStatic(this,1,3); //�����ڶ��εľ�̬�ָ�
	m_splitWnd2.CreateView(0,0,RUNTIME_CLASS(CBttmOneView),CSize(rect.Width()/3 ,rect.Height()),pContext);
	m_splitWnd2.CreateView(0,1,RUNTIME_CLASS(CBttmTwoView),CSize(rect.Width()/3 ,rect.Height()),pContext);
	m_splitWnd2.CreateView(0,2,RUNTIME_CLASS(CBttmThreeView),CSize(rect.Width()/3 ,rect.Height()),pContext);	
	return 0;
}


void CBttmView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
