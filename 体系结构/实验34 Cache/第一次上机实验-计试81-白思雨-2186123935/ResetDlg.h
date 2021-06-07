#if !defined(AFX_RESETDLG_H__47EF9F93_582C_4EA5_98EC_FC000BD0E4BE__INCLUDED_)
#define AFX_RESETDLG_H__47EF9F93_582C_4EA5_98EC_FC000BD0E4BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResetDlg.h : header file
//

#include "XPButton.h"

/////////////////////////////////////////////////////////////////////////////
// CResetDlg dialog

class CResetDlg : public CDialog
{
// Construction
public:
	CResetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResetDlg)
	enum { IDD = IDD_RESET };
	CXPButton	m_btnRestart;
	CXPButton	m_btnCancel;
	CXPButton	m_btnProgram;
	CXPButton	m_btnConfig;
	CXPButton	m_btnAll;
	//}}AFX_DATA
	enum {
		kCancel, kNewProgram, kNewConfig, kAll, kRestart
	} m_nSelState;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResetDlg)
	afx_msg void OnBtnAll();
	afx_msg void OnBtnConfig();
	afx_msg void OnBtnProgram();
	afx_msg void OnBtnRestart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESETDLG_H__47EF9F93_582C_4EA5_98EC_FC000BD0E4BE__INCLUDED_)
