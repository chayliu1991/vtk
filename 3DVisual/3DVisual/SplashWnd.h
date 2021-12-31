#pragma once


// SplashWnd

class SplashWnd : public CWnd
{
	DECLARE_DYNAMIC(SplashWnd)

public:
	SplashWnd();
	virtual ~SplashWnd();
	void ShowSplashWnd(CWnd * parentWnd);

protected:
	DECLARE_MESSAGE_MAP()
private:
	CBitmap m_bitmap;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


