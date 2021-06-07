#if !defined(AFX_SIMULATORDLG_H__3481D1A2_F917_4875_A55A_FCD52C42CD3E__INCLUDED_)
#define AFX_SIMULATORDLG_H__3481D1A2_F917_4875_A55A_FCD52C42CD3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimulatorDlg.h : header file
//

#include "XPButton.h"
#include "TextCtrl.h"
#include "MIPSPipelineDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDlg dialog

class CSimulatorDlg : public CDialog
{
// Construction
public:
	CSimulatorDlg(CWnd* pParent = NULL);   // standard constructor

// Attributes
public:
	static UINT m_UserMsg;
	static UINT	m_msgPipelineDlg;
	CTextCtrl	m_textCtrl;
	CMIPSPipelineDlg* m_pMIPSPipelineDlg;

	BOOL		m_bThreadStarted;// for threadBtnGo() thread
	BOOL		m_bThreadStop;// force threadBtnGo() thread to stop

// Operations
public:
	void UpdateTextCtrl();

	void EnableButton( BOOL enable = TRUE );// enable button, excluding go and stop

// Dialog Data
	//{{AFX_DATA(CSimulatorDlg)
	enum { IDD = IDD_SIM_DLG };
	CXPButton	m_btnStop;
	CXPButton	m_btnStat;
	CXPButton	m_btnTrace;
	CXPButton	m_btnReset;
	CXPButton	m_btnGo;
	CXPButton	m_btnPreCycle;
	CXPButton	m_btnNextCycle;
	CXPButton	m_btnStepForward;
	CXPButton	m_btnStepBack;
	CXPButton	m_btnLoad;
	CXPButton	m_btnConfigure;
	CXPButton	m_btnEdit;
	CXPButton	m_btnQuit;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimulatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSimulatorDlg)
	afx_msg void OnBtnQuit();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnLoad();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBtnConfigure();
	afx_msg void OnBtnNextCycle();
	afx_msg void OnClose();
	afx_msg void OnBtnPreviousCycle();
	afx_msg void OnBtnStepForward();
	afx_msg void OnBtnStepBack();
	afx_msg void OnBtnGo();
	afx_msg void OnBtnTrace();
	afx_msg void OnBtnReset();
	afx_msg void OnBtnStat();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	afx_msg LRESULT AsmEditMsgHandler(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT PipelineDlgMsgHandler(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMULATORDLG_H__3481D1A2_F917_4875_A55A_FCD52C42CD3E__INCLUDED_)
