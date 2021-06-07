#if !defined(AFX_MEMDLG_H__47464B91_6AA4_4725_B482_0CA9502FAA2F__INCLUDED_)
#define AFX_MEMDLG_H__47464B91_6AA4_4725_B482_0CA9502FAA2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MemDlg.h : header file
//

#include "GridCtrl/GridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CMemDlg dialog

class CMemDlg : public CDialog
{
// Construction
public:
	CMemDlg(CWnd* pParent = NULL);   // standard constructor
	~CMemDlg();

// Operations
public:
	void InitGrid();
	void ResetGrid();
	void UpdateMem();
	void EnableEdit(BOOL flag = TRUE);

// Attributes
public:
	CGridCtrl m_GridCtrl;
	BOOL	  m_bEditable;
	BOOL	  m_bInputFault;
	int*	  data;

// Dialog Data
	//{{AFX_DATA(CMemDlg)
	enum { IDD = IDD_MEMDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CButton	  m_RadioBig;
	CButton	  m_RadioLittle;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMemDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnRadioBigending();
	afx_msg void OnRadioLittleending();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMDLG_H__47464B91_6AA4_4725_B482_0CA9502FAA2F__INCLUDED_)
