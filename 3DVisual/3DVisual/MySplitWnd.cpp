// MySplitWnd.cpp : 实现文件
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



// CMySplitWnd 消息处理程序




void CMySplitWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
}


void CMySplitWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
}
