#if !defined(AFX_CYCLEDLG_H__4419A453_B36B_49EB_B396_15DC76E9574D__INCLUDED_)
#define AFX_CYCLEDLG_H__4419A453_B36B_49EB_B396_15DC76E9574D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CycleDlg.h : header file
//

#include "XPButton.h"

/////////////////////////////////////////////////////////////////////////////
// CCycleDlg dialog

class CCycleDlg : public CDialog
{
// Construction
public:
	CCycleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCycleDlg)
	enum { IDD = IDD_CYCLE_FROM };
	CXPButton	m_btnOK;
	CXPButton	m_btnCancel;
	CXPButton	m_btnDefault;
	UINT		m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCycleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCycleDlg)
	virtual void OnOK();
	afx_msg void OnBtnDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CYCLEDLG_H__4419A453_B36B_49EB_B396_15DC76E9574D__INCLUDED_)
