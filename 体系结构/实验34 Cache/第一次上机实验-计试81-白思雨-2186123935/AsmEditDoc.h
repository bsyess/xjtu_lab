#if !defined(AFX_ASMEDITDOC_H__3A456FE3_F7EF_43C8_AC6A_2C1EB247AB4B__INCLUDED_)
#define AFX_ASMEDITDOC_H__3A456FE3_F7EF_43C8_AC6A_2C1EB247AB4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AsmEditDoc.h : header file
//

#include "Crystal\CCrystalTextBuffer.h"

#define ASMEDITMSG "AsmEditMsg"
#define ML_CLOSED	1

class CAsmEditDoc : public CDocument
{
protected:
	CAsmEditDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAsmEditDoc)

// Attributes
public:
	UINT	m_UserMsg;
	CString lpszPathName;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsmEditDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	virtual void OnCloseDocument();
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAsmEditDoc();

	LOGFONT m_lf;
	CCrystalTextBuffer m_TextBuffer;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAsmEditDoc)
	afx_msg void OnAsmFileOpen();
	afx_msg void OnAsmFileNew();
	afx_msg void OnAsmFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASMEDITDOC_H__3A456FE3_F7EF_43C8_AC6A_2C1EB247AB4B__INCLUDED_)
