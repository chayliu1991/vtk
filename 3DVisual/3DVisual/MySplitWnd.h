#pragma once


// CMySplitWnd

class CMySplitWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CMySplitWnd)

public:
	CMySplitWnd();
	virtual ~CMySplitWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


