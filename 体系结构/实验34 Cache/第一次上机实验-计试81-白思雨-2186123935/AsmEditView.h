#if !defined(AFX_ASMEDITVIEW_H__301C0948_D219_4CF4_8EC2_2438A39B07A5__INCLUDED_)
#define AFX_ASMEDITVIEW_H__301C0948_D219_4CF4_8EC2_2438A39B07A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AsmEditView.h : header file
//

#include "Crystal\CCrystalEditView.h"

class CAsmEditView : public CCrystalEditView
{
protected:// create from serialization only
	virtual CCrystalTextBuffer* LocateTextBuffer();
	CAsmEditView();
	virtual ~CAsmEditView();	

	void SetSelection(const CPoint &ptStart, const CPoint &ptEnd)
	{
		CCrystalTextView::SetSelection(ptStart,ptEnd);
	}

protected:
	virtual DWORD ParseLine(DWORD dwCookie, int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems);
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleView)
	public:
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

	DECLARE_DYNCREATE(CAsmEditView)

// Generated message map functions
protected:
	//{{AFX_MSG(CMiniSQLView)
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASMEDITVIEW_H__301C0948_D219_4CF4_8EC2_2438A39B07A5__INCLUDED_)
