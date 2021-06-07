#if !defined(AFX_STATDLG_H__1B4A8779_F15F_4944_8FC8_F548A52C2EE1__INCLUDED_)
#define AFX_STATDLG_H__1B4A8779_F15F_4944_8FC8_F548A52C2EE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatDlg.h : header file
//

#include "GridCtrl/GridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CStatDlg dialog

class CStatDlg : public CDialog
{
// Construction
public:
	CStatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatDlg)
	enum { IDD = IDD_STAT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CGridCtrl m_GridCtrl;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATDLG_H__1B4A8779_F15F_4944_8FC8_F548A52C2EE1__INCLUDED_)
