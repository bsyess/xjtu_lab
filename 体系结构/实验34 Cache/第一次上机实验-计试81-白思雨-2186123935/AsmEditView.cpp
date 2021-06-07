// AsmEditView.cpp : implementation file
//

#include "stdafx.h"
#include "Pipeline.h"

#include "AsmEditView.h"
#include "AsmEditDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsmEditView

IMPLEMENT_DYNCREATE(CAsmEditView, CCrystalEditView)

BEGIN_MESSAGE_MAP(CAsmEditView, CCrystalEditView)
	//{{AFX_MSG_MAP(CMiniSQLView)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CCrystalEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAsmEditView construction/destruction

CAsmEditView::CAsmEditView()
{
}

CAsmEditView::~CAsmEditView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CAsmEditView message handlers
CCrystalTextBuffer* CAsmEditView::LocateTextBuffer()
{
	return &((CAsmEditDoc*)GetDocument())->m_TextBuffer;
}

void CAsmEditView::OnInitialUpdate()
{
	CCrystalEditView::OnInitialUpdate();

	CCrystalEditView::SetFont(((CAsmEditDoc*)GetDocument())->m_lf);
}

void CAsmEditView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	ClientToScreen( &point );

	CMenu menu;
	VERIFY( menu.LoadMenu( IDR_CRYSTAL ) );
	CMenu* pPop = menu.GetSubMenu( 0 );
	ASSERT( pPop );

	CWnd* pWndPopupOwner = this;
		
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
		
	pPop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);

	CCrystalEditView::OnRButtonUp(nFlags, point);
}
