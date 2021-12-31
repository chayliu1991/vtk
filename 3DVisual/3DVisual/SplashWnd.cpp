// SplashWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "3DVisual.h"
#include "SplashWnd.h"


// SplashWnd

IMPLEMENT_DYNAMIC(SplashWnd, CWnd)

SplashWnd::SplashWnd()
{

}

SplashWnd::~SplashWnd()
{
}


BEGIN_MESSAGE_MAP(SplashWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// SplashWnd 消息处理程序




int SplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CenterWindow();
	SetTimer(2,3000,NULL);
	return 0;
}


void SplashWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()	
	CDC bitdc;
	bitdc.CreateCompatibleDC(&dc);
	bitdc.SelectObject(m_bitmap);
	BITMAP bitmap;
	m_bitmap.GetBitmap(&bitmap);
	dc.BitBlt(0,0,bitmap.bmWidth,bitmap.bmHeight
		,&bitdc,0,0,SRCCOPY);
}


void SplashWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
	CWnd::OnTimer(nIDEvent);
}


void SplashWnd::ShowSplashWnd(CWnd * parentWnd)
{
	m_bitmap.LoadBitmapA(IDB_SPALSH);
	BITMAP bitmap;
	m_bitmap.GetBitmap(&bitmap);
	CreateEx(0,AfxRegisterWndClass(0),NULL,
		WS_POPUP | WS_VISIBLE,0,0,bitmap.bmWidth,
		bitmap.bmHeight,parentWnd->GetSafeHwnd(),NULL);
	UpdateWindow();
}