#if !defined(AFX_TRACEDLG_H__452ED1CD_3875_4F69_892D_06FD054678A8__INCLUDED_)
#define AFX_TRACEDLG_H__452ED1CD_3875_4F69_892D_06FD054678A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TraceDlg.h : header file
//

#include "XPButton.h"

/////////////////////////////////////////////////////////////////////////////
// CTraceDlg dialog

class CTraceDlg : public CDialog
{
// Construction
public:
	CTraceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTraceDlg)
	enum { IDD = IDD_TRACE };
	CXPButton	m_btnCancel;
	CXPButton	m_btnOK;
	CString		m_edit;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTraceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTraceDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACEDLG_H__452ED1CD_3875_4F69_892D_06FD054678A8__INCLUDED_)
