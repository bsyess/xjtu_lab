// MIPSPipelineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pipeline.h"
#include "MIPSPipelineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMIPSPipelineDlg dialog

CMIPSPipelineDlg::CMIPSPipelineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMIPSPipelineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMIPSPipelineDlg)
	//}}AFX_DATA_INIT
	m_msgPipelineDlg = RegisterWindowMessage( MIPSPipelineDlgMsg );
}


void CMIPSPipelineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMIPSPipelineDlg)
	DDX_Control(pDX, IDC_COPYRIGHT, m_staticCopyRight);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMIPSPipelineDlg, CDialog)
	//{{AFX_MSG_MAP(CMIPSPipelineDlg)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, DoNothing)
	ON_BN_CLICKED(IDOK, DoNothing)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMIPSPipelineDlg message handlers

BOOL CMIPSPipelineDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// show copyright
	m_staticCopyRight.SetURL( _T("mailto:bsyess@bsyess.top") );
	m_staticCopyRight.SetUnderline( FALSE );

	CRect rect;
	GetDlgItem( IDC_EXECINST_CTRL )->GetWindowRect( rect );
	ScreenToClient( rect );
	m_ExecInstCtrl.Create( WS_CHILD | WS_VISIBLE, rect, this );

	GetDlgItem( IDC_DATAPATH )->GetWindowRect( rect );
	ScreenToClient( rect );
	m_DatapathCtrl.Create( WS_CHILD | WS_VISIBLE, rect, this );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMIPSPipelineDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect( rect );
	dc.FillSolidRect( rect, RGB(225,255,255) );
}

void CMIPSPipelineDlg::NextCycle( BOOL bRedraw )
{
	m_ExecInstCtrl.NextCycle( bRedraw );
	m_DatapathCtrl.NextCycle( bRedraw );
}

void CMIPSPipelineDlg::Reset()
{
	m_ExecInstCtrl.Reset();
}

void CMIPSPipelineDlg::ResetAndUpdate()
{
	m_ExecInstCtrl.Reset();
	m_ExecInstCtrl.DrawAll();
	m_DatapathCtrl.Reset();
}

void CMIPSPipelineDlg::OnClose() 
{
	if( MessageBox("请确认是否重置所有数据？", "请注意！", MB_YESNO | MB_ICONQUESTION) == IDYES ) {
		CPipelineApp* pApp = (CPipelineApp*)AfxGetApp();
		pApp->m_pSimulatorDlg->PostMessage( m_msgPipelineDlg, ML_RESET );

		this->ShowWindow( SW_HIDE );
	}
}

void CMIPSPipelineDlg::DoNothing()
{
	return;
}
