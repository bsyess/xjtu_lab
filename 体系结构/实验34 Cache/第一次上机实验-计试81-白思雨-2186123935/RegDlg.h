#if !defined(AFX_REGDLG_H__B622B532_30C5_4BFB_BD4C_72E7582A8FB3__INCLUDED_)
#define AFX_REGDLG_H__B622B532_30C5_4BFB_BD4C_72E7582A8FB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegDlg.h : header file
//

#include "GridCtrl/GridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog

class CRegDlg : public CDialog
{
// Construction
public:
	CRegDlg(CWnd* pParent = NULL);// standard constructor

// Operations
public:
	void InitGrid();
	void ResetGrid();
	void UpdateReg();
	void EnableEdit(BOOL flag = TRUE);

// Attributes
public:
	CGridCtrl m_GridCtrl;
	BOOL	  m_bEditable;
	BOOL	  m_bInputFault;
	enum {
		kHex, kDec
	} mode;
	int		  reg[32];

// Dialog Data
	//{{AFX_DATA(CRegDlg)
	enum { IDD = IDD_REGDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CButton	  m_RadioHex;
	CButton   m_RadioDec;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnRadioHex();
	afx_msg void OnRadioDec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGDLG_H__B622B532_30C5_4BFB_BD4C_72E7582A8FB3__INCLUDED_)
