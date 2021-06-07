#if !defined(AFX_SIMCONFIGDLG_H__B34720A0_1BC0_45A7_974F_866DD7FE27DF__INCLUDED_)
#define AFX_SIMCONFIGDLG_H__B34720A0_1BC0_45A7_974F_866DD7FE27DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimConfigDlg.h : header file
//

#include "XPButton.h"

/////////////////////////////////////////////////////////////////////////////
// CSimConfigDlg dialog

class CSimConfigDlg : public CDialog
{
// Construction
public:
	CSimConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSimConfigDlg)
	enum { IDD = IDD_SIM_CONFIG };
	CXPButton	m_btnReg;
	CXPButton	m_btnMem;
	CXPButton	m_btnOK;
	CXPButton	m_btnCancel;
	CSliderCtrl	m_SliderMem;
	CSliderCtrl	m_SliderDiv;
	CSliderCtrl	m_SliderMul;
	CString		m_edit1;
	CString		m_edit2;
	CString		m_edit3;
	//}}AFX_DATA

	CButton		m_RadioFreeze;
	CButton		m_RadioPredictToken;
	CButton		m_RadioRredictNotToken;
	CButton		m_RadioDelayedBranch;

	CButton		m_RadioForwarding;
	CButton		m_RadioNotForwarding;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetRadioCheck();
	void UpdateSliderData();

	// Generated message map functions
	//{{AFX_MSG(CSimConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioFreeze();
	afx_msg void OnRadioPredictToken();
	afx_msg void OnRadioPredictNotToken();
	afx_msg void OnRadioDelayedBranch();
	afx_msg void OnRadioForwarding();
	afx_msg void OnRadioNotForwarding();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	afx_msg void OnBtnMem();
	afx_msg void OnBtnReg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	UINT m_nBranchMethod;
	BOOL m_bForwardingEnable;

	UINT m_nMulDelay;
	UINT m_nDivDelay;
	UINT m_nDataSize;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMCONFIGDLG_H__B34720A0_1BC0_45A7_974F_866DD7FE27DF__INCLUDED_)
