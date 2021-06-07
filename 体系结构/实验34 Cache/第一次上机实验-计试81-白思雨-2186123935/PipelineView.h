// PipelineView.h : interface of the CPipelineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIPELINEVIEW_H__31395D09_53CB_4233_9ECA_6EDC61942B05__INCLUDED_)
#define AFX_PIPELINEVIEW_H__31395D09_53CB_4233_9ECA_6EDC61942B05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPipelineCntrItem;

class CPipelineView : public CRichEditView
{
protected: // create from serialization only
	CPipelineView();
	DECLARE_DYNCREATE(CPipelineView)

// Attributes
public:
	CPipelineDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPipelineView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPipelineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPipelineView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PipelineView.cpp
inline CPipelineDoc* CPipelineView::GetDocument()
   { return (CPipelineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIPELINEVIEW_H__31395D09_53CB_4233_9ECA_6EDC61942B05__INCLUDED_)
