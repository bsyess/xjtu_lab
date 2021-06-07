// Pipeline.h : main header file for the PIPELINE application
//

#if !defined(AFX_PIPELINE_H__F74AB06E_1EA6_461A_A2BA_77726EAEA26F__INCLUDED_)
#define AFX_PIPELINE_H__F74AB06E_1EA6_461A_A2BA_77726EAEA26F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "SimulatorDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CPipelineApp:
// See Pipeline.cpp for the implementation of this class
//

class CPipelineApp : public CWinApp
{
public:
	void CreateEditView();
	CPipelineApp();

	CMultiDocTemplate* m_pConsoleDocTemplate;
	CMultiDocTemplate* m_pAsmEditDocTemplate;

	CSimulatorDlg* m_pSimulatorDlg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPipelineApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPipelineApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIPELINE_H__F74AB06E_1EA6_461A_A2BA_77726EAEA26F__INCLUDED_)
