// PipelineView.cpp : implementation of the CPipelineView class
// Download by http://down.liehuo.net

#include "stdafx.h"
#include "Pipeline.h"

#include "PipelineDoc.h"
#include "CntrItem.h"
#include "PipelineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPipelineView

IMPLEMENT_DYNCREATE(CPipelineView, CRichEditView)

BEGIN_MESSAGE_MAP(CPipelineView, CRichEditView)
	//{{AFX_MSG_MAP(CPipelineView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPipelineView construction/destruction

CPipelineView::CPipelineView()
{
	// TODO: add construction code here

}

CPipelineView::~CPipelineView()
{
}

BOOL CPipelineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CPipelineView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	CRichEditCtrl& pCtrl = GetRichEditCtrl();
	pCtrl.SetReadOnly();

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CPipelineView printing

BOOL CPipelineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CPipelineView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CPipelineView diagnostics

#ifdef _DEBUG
void CPipelineView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CPipelineView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CPipelineDoc* CPipelineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPipelineDoc)));
	return (CPipelineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPipelineView message handlers
