// CntrItem.h : interface of the CPipelineCntrItem class
//

#if !defined(AFX_CNTRITEM_H__1CC7EF57_79AF_422B_A5E5_FCB77F9178AE__INCLUDED_)
#define AFX_CNTRITEM_H__1CC7EF57_79AF_422B_A5E5_FCB77F9178AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPipelineDoc;
class CPipelineView;

class CPipelineCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CPipelineCntrItem)

// Constructors
public:
	CPipelineCntrItem(REOBJECT* preo = NULL, CPipelineDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CPipelineDoc* GetDocument()
		{ return (CPipelineDoc*)CRichEditCntrItem::GetDocument(); }
	CPipelineView* GetActiveView()
		{ return (CPipelineView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPipelineCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CPipelineCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__1CC7EF57_79AF_422B_A5E5_FCB77F9178AE__INCLUDED_)
