// MySplitWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DVisual.h"
#include "MySplitWnd.h"


// CMySplitWnd

IMPLEMENT_DYNAMIC(CMySplitWnd, CSplitterWnd)

CMySplitWnd::CMySplitWnd()
{

}

CMySplitWnd::~CMySplitWnd()
{
}


BEGIN_MESSAGE_MAP(CMySplitWnd, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMySplitWnd ��Ϣ�������




void CMySplitWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
}


void CMySplitWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
}
