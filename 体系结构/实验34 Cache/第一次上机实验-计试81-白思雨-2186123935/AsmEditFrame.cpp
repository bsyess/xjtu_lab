// AsmEditFrame.cpp : implementation file
//

#include "stdafx.h"
#include "pipeline.h"

#include "AsmEditFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsmEditFrame

IMPLEMENT_DYNCREATE(CAsmEditFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CAsmEditFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CAsmEditFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CAsmEditFrame construction/destruction

CAsmEditFrame::CAsmEditFrame()
{
}

CAsmEditFrame::~CAsmEditFrame()
{
}

int CAsmEditFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_ASMTYPE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CAsmEditFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAsmEditFrame diagnostics

#ifdef _DEBUG
void CAsmEditFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CAsmEditFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAsmEditFrame message handlers
BOOL CAsmEditFrame::LoadFrame(UINT nIDResource,
							  DWORD dwDefaultStyle/*= WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE*/,
							  CWnd* pParentWnd/*= NULL*/,
							  CCreateContext* pContext/*= NULL*/) 
{
	// base class does the real work
	if (!CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle,
		pParentWnd, pContext)) {
		return FALSE;
	}

	// test for main-ness
	CWinApp* pApp = AfxGetApp();
	if (pApp->m_pMainWnd == NULL)
		pApp->m_pMainWnd = this;

	return TRUE;
}
