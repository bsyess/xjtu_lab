#if !defined(AFX_MIPSPIPELINEDLG_H__0EF22ECF_2F19_4C3B_BCBA_8E3E5B00EF59__INCLUDED_)
#define AFX_MIPSPIPELINEDLG_H__0EF22ECF_2F19_4C3B_BCBA_8E3E5B00EF59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MIPSPipelineDlg.h : header file
//

#include "ExecInstCtrl.h"
#include "IntegerDatapathCtrl.h"
//CJ60LIB
#include "hyperlink.h"

#define MIPSPipelineDlgMsg	"MIPSPipelineDlgMsg"
#define ML_RESET			1

/////////////////////////////////////////////////////////////////////////////
// CMIPSPipelineDlg dialog

class CMIPSPipelineDlg : public CDialog
{
// Construction
public:
	CMIPSPipelineDlg(CWnd* pParent = NULL);   // standard constructor

// Attributes
public:
	UINT					m_msgPipelineDlg;

	CExecInstCtrl			m_ExecInstCtrl;
	CIntegerDatapathCtrl	m_DatapathCtrl;

// Operations
public:
	void ResetAndUpdate();
	void Reset();
	void NextCycle( BOOL bRedraw = TRUE );

// Dialog Data
	//{{AFX_DATA(CMIPSPipelineDlg)
	enum { IDD = IDD_MIPS_PIPELINE };
	CHyperLink	m_staticCopyRight;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMIPSPipelineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMIPSPipelineDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void DoNothing();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIPSPIPELINEDLG_H__0EF22ECF_2F19_4C3B_BCBA_8E3E5B00EF59__INCLUDED_)
