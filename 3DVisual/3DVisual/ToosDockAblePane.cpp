// ToosDockAblePane.cpp : ʵ���ļ�
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



// CToosDockAblePane ��Ϣ�������




int CToosDockAblePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_paneDlg.Create(IDD_DLG_PANE, this);
	m_paneDlg.ShowWindow(SW_SHOW);
	return 0;
}


void CToosDockAblePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}


void CToosDockAblePane::OnDestroy()
{
	CDockablePane::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	m_paneDlg.DestroyWindow();
}
