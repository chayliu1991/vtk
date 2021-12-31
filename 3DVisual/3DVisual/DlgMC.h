#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "btnst.h"
#include "afxcolorbutton.h"

// CDlgMC 对话框

class CDlgMC : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMC)

public:
	CDlgMC(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMC();

// 对话框数据
	enum { IDD = IDD_DLG_MC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedStartmc();
	afx_msg void OnBnClickedBtnsetskinvalue();
	afx_msg void OnBnClickedMcbkcolor();
	afx_msg void OnBnClickedMcskincolor();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	virtual BOOL OnInitDialog();
	
	CMFCColorButton m_MCBkColor;
	COLORREF MCBkRGB;	
	UINT m_McSkinValue;
	CMFCColorButton m_MCSkinColor;
	COLORREF MCSKinRGB;	
	CSliderCtrl m_MCOpacity;	
	CSliderCtrl m_MCSpecular;
	int m_McOpacity;	
	int m_McSpecular;
	CButtonST m_McStartBtn,m_ResetSurfaceBtn,m_VrBtn,m_VRIsoValueBtn,m_SetColorBtn,m_VrOpacitySetBtn
		,m_3DCutBtn,m_3DCutCancelBtn,m_SaveStlBtn,m_AmbientSetBtn,m_DiffuseSetBtn,m_OpacitySetBtn,m_McdiffuseSet;	
	afx_msg void OnBnClickedStartvr();		
	CComboBox m_VrAlgorithm;
	afx_msg void OnCbnSelchangeVralgorithmcom();	
	LRESULT CheckAlgorithm(WPARAM wParam, LPARAM lParam) ;
	afx_msg void OnBnClickedResetvrisovalue();
	int m_IsoValue;	
	CSliderCtrl m_OpcitySlider1;
	CSliderCtrl m_OpcitySlider2;
	CSliderCtrl m_OpcitySlider3;
	float m_fOpacityValue1;
	float m_fOpacityValue2;
	float m_fOpacityValue3;
	afx_msg void OnDeltaposOpacityspin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposOpacityspin2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposOpacityspin3(NMHDR *pNMHDR, LRESULT *pResult);
	int m_nOpacity1;
	int m_nOpacity2;
	int m_nOpacity3;
	afx_msg void OnBnClickedSetvropacity();
	int m_nGray1;
	int m_nGray2;
	int m_nGray3;
	int m_nGray4;	
	COLORREF m_colorValue1;
	COLORREF m_colorValue2;
	COLORREF m_colorValue3;
	COLORREF m_colorValue4;
	afx_msg void OnBnClickedSetvrcolor();
	CMFCColorButton m_VrColorCtr1;
	CMFCColorButton m_VrColorCtr2;
	CMFCColorButton m_VrColorCtr3;
	CMFCColorButton m_VrColorCtr4;
	afx_msg void OnBnClickedMfccolorbutton1();
	afx_msg void OnBnClickedMfccolorbutton2();
	afx_msg void OnBnClickedMfccolorbutton3();
	afx_msg void OnBnClickedMfccolorbutton4();		
	void EnableVRDialog(BOOL flag);
	void EnableMCDialog(BOOL flag);
	afx_msg LRESULT OnCbnSelchangeVralgorithmcom(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClicked3dcut();
	afx_msg void OnBnClickedButton4();	
	afx_msg void OnBnClickedSavestl();
	CString m_stlFileFolder,m_stlfileName;	
	CSliderCtrl m_MCDiffuse;
	int m_McDiffuse;	
	afx_msg void OnBnClickedMcdiffuseset();
	afx_msg void OnBnClickedMcambientcolor();
	CMFCColorButton m_MCAmbientColor;
	COLORREF MCAmbientRGB;
	CSliderCtrl m_MCAmbient;
	int m_McAmbient;
	afx_msg void OnBnClickedMcambientset();
	CMFCColorButton m_MCSpecularColor;
	COLORREF MCSpecularRGB;
	afx_msg void OnBnClickedMcspecularcolor();
	afx_msg void OnBnClickedMcspecularset();
	afx_msg void OnBnClickedMcopacityuset();	
};
