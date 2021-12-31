// ToosDockAblePane.cpp : 实现文件
//

#include "stdafx.h"
#include "3DVisual.h"
#include "ToosDockAblePane.h"


// CToosDockAblePane

IMPLEMENT_DYNAMIC(CToosDockAblePane, CDockablePane)

CToosDockAblePane::CToosDockAblePane()
{

}

CToosDockAblePane::~CToosDockAblePane()
{
}


BEGIN_MESSAGE_MAP(CToosDockAblePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CToosDockAblePane 消息处理程序




int CToosDockAblePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_paneDlg.Create(IDD_DLG_PANE, this);
	m_paneDlg.ShowWindow(SW_SHOW);
	return 0;
}


void CToosDockAblePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}


void CToosDockAblePane::OnDestroy()
{
	CDockablePane::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	m_paneDlg.DestroyWindow();
}
