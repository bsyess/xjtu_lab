#if !defined(AFX_ASMEDITFRAME_H__94E7E76E_85ED_4E7E_BC72_C2AF3F9D7F94__INCLUDED_)
#define AFX_ASMEDITFRAME_H__94E7E76E_85ED_4E7E_BC72_C2AF3F9D7F94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AsmEditFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAsmEditFrame frame

class CAsmEditFrame : public CFrameWnd
{
public:
	CAsmEditFrame();

protected:
	DECLARE_DYNCREATE(CAsmEditFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsmEditFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAsmEditFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CAsmEditFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASMEDITFRAME_H__94E7E76E_85ED_4E7E_BC72_C2AF3F9D7F94__INCLUDED_)
