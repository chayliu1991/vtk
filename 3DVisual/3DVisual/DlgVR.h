#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxcolorbutton.h"
#include "btnst.h"
#include "DlgSaveSet.h"


// CDlgVR 对话框

class CDlgVR : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVR)

public:
	CDlgVR(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVR();

// 对话框数据
	enum { IDD = IDD_DLG_VR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDeltaposSlicespinx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSlicespiny(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSlicespinz(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	CSliderCtrl m_SliderSliceX;
	CSliderCtrl m_SliderSliceY;
	CSliderCtrl m_SliderSliceZ;
	void SetSliceX(int sliceindex);
	void SetSliceY(int sliceindex);
	void SetSliceZ(int sliceindex);	
	afx_msg void OnBnClickedSliceplaybtn();	
	CComboBox m_SlicePlayComb;	
	bool m_Playfg;
	float InitSlice;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SetXYZWindow(double window,double level);
	CSliderCtrl m_WindowSlider;
	CSliderCtrl m_LevelSlider;
	afx_msg void OnBnClickedResetwinwdowlevelbtn();
	afx_msg void OnBnClickedSetwinwdowlevelbtn();
	CMFCColorButton m_SliceXBKColor;
	CMFCColorButton m_SliceYBKColor;
	CMFCColorButton m_SliceZBKColor;
	afx_msg void OnBnClickedBkcolorslicex();
	afx_msg void OnBnClickedBkcolorslicey();
	afx_msg void OnBnClickedBkcolorslicez();
	COLORREF SLiceXBkRGB;
	COLORREF SLiceYBkRGB;
	COLORREF SLiceZBkRGB;
	int m_PicMAinpulateRadioBtn;
	afx_msg void OnBnClickedZxmainpulateradio();
	afx_msg void OnBnClickedYzmainpulateradio();
	afx_msg void OnBnClickedXymainpulateradio();
	afx_msg void OnBnClickedLeftrotation();
	afx_msg void OnBnClickedRightrotation();
	afx_msg void OnBnClickedHorimirror();
	afx_msg void OnBnClickedVertimirror();
	CButtonST m_SlicePlayBtn,m_VerticalMirrorBtn,m_HorizontalMirrorBtn,m_TurnLeftBtn,m_TurnRightBtn
		,m_AnistropyFilterBtn,m_MedianFilterBtn,m_GaussSmoothBtn,m_TemplateSetBtn,m_MeanFilterBtn
		,m_EdgeDetectionBtn,m_SaveBmpBtn,m_binBtn,m_CaptureBtn,m_SetWindowBtn,m_ResetWindowBtn;	
	afx_msg void OnBnClickedAnisotropyfilter();	
	afx_msg void OnBnClickedGauss();
	afx_msg void OnBnClickedTemplate();	
	afx_msg void OnBnClickedMeanfilter();
	afx_msg void OnBnClickedEdgedetection();
	afx_msg void OnBnClickedSavebmp();	
	CString m_SaveFolderName;
	CString m_SaveFileName;
	int m_SaveFileRangeMin;
	int m_SaveFileRangeMax;		
	afx_msg void OnBnClickedBinary();	
	CString m_captureFolder;
	CString m_CaptureName;
	afx_msg void OnBnClickedCapture();
	
};
