// SimulatorDlg.cpp : implementation file
// Download by http://down.liehuo.net

#include "stdafx.h"
#include "Pipeline.h"

#include "SimulatorDlg.h"

#include "AsmEditDoc.h"
#include "MIPSSimulator.h"
#include "SimConfigDlg.h"
#include "CycleDlg.h"
#include "TraceDlg.h"
#include "ResetDlg.h"
#include "StatDlg.h"
#include "MIPSPipelineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDlg dialog

UINT CSimulatorDlg::m_UserMsg = RegisterWindowMessage( ASMEDITMSG );
UINT CSimulatorDlg::m_msgPipelineDlg = RegisterWindowMessage( MIPSPipelineDlgMsg );

CSimulatorDlg::CSimulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimulatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimulatorDlg)
	//}}AFX_DATA_INIT
	m_pMIPSPipelineDlg = NULL;
}

void CSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimulatorDlg)
	DDX_Control(pDX, IDC_BTN_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BTN_STAT, m_btnStat);
	DDX_Control(pDX, IDC_BTN_TRACE, m_btnTrace);
	DDX_Control(pDX, IDC_BTN_RESET, m_btnReset);
	DDX_Control(pDX, IDC_BTN_GO, m_btnGo);
	DDX_Control(pDX, IDC_BTN_PREVIOUS_CYCLE, m_btnPreCycle);
	DDX_Control(pDX, IDC_BTN_NEXT_CYCLE, m_btnNextCycle);
	DDX_Control(pDX, IDC_BTN_STEP_FORWARD, m_btnStepForward);
	DDX_Control(pDX, IDC_BTN_STEP_BACK, m_btnStepBack);
	DDX_Control(pDX, IDC_BTN_LOAD, m_btnLoad);
	DDX_Control(pDX, IDC_BTN_CONFIGURE, m_btnConfigure);
	DDX_Control(pDX, IDC_BTN_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTN_QUIT, m_btnQuit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimulatorDlg, CDialog)
	//{{AFX_MSG_MAP(CSimulatorDlg)
	ON_BN_CLICKED(IDC_BTN_QUIT, OnBtnQuit)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BTN_LOAD, OnBtnLoad)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_CONFIGURE, OnBtnConfigure)
	ON_BN_CLICKED(IDC_BTN_NEXT_CYCLE, OnBtnNextCycle)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_PREVIOUS_CYCLE, OnBtnPreviousCycle)
	ON_BN_CLICKED(IDC_BTN_STEP_FORWARD, OnBtnStepForward)
	ON_BN_CLICKED(IDC_BTN_STEP_BACK, OnBtnStepBack)
	ON_BN_CLICKED(IDC_BTN_GO, OnBtnGo)
	ON_BN_CLICKED(IDC_BTN_TRACE, OnBtnTrace)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	ON_BN_CLICKED(IDC_BTN_STAT, OnBtnStat)
	ON_BN_CLICKED(IDCANCEL, OnBtnQuit)
	ON_BN_CLICKED(IDOK, OnBtnConfigure)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(CSimulatorDlg::m_UserMsg, AsmEditMsgHandler)
	ON_REGISTERED_MESSAGE(CSimulatorDlg::m_msgPipelineDlg, PipelineDlgMsgHandler)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDlg message handlers

void CSimulatorDlg::PostNcDestroy() 
{
	delete this;
	CDialog::PostNcDestroy();
}

LRESULT CSimulatorDlg::AsmEditMsgHandler(WPARAM wParam, LPARAM lParam)
{
	switch( wParam ) {
	case ML_CLOSED:
		CButton* cb = (CButton*)GetDlgItem(IDC_BTN_EDIT);
		cb->EnableWindow(TRUE);
		break;
	}

	return TRUE;
}

LRESULT CSimulatorDlg::PipelineDlgMsgHandler(WPARAM wParam, LPARAM lParam)
{
	switch( wParam ) {
	case ML_RESET:
		simulator.Reset();
		m_textCtrl.Reset();
		m_textCtrl.UpdateAll();
		if( m_pMIPSPipelineDlg )
			m_pMIPSPipelineDlg->ResetAndUpdate();
		// set button enable
		m_btnLoad.EnableWindow( FALSE );
		m_btnReset.EnableWindow( FALSE );
		m_btnStepForward.EnableWindow( FALSE );
		m_btnStepBack.EnableWindow( FALSE );
		m_btnNextCycle.EnableWindow( FALSE );
		m_btnPreCycle.EnableWindow( FALSE );
		m_btnGo.EnableWindow( FALSE );
		m_btnStat.EnableWindow( FALSE );
		m_btnTrace.EnableWindow( FALSE );
		break;
	}

	return TRUE;
}

void CSimulatorDlg::UpdateTextCtrl()
{
	if( simulator.m_pInsts ) {
		m_textCtrl.Reset();
		POSITION pos = simulator.m_pInsts->m_instList.GetHeadPosition();
		while( pos ) {
			CAsmInstruction* pInst = simulator.m_pInsts->m_instList.GetNext(pos);
			m_textCtrl.AddItem( pInst->InstWithLabelAddress() );
		}
		m_textCtrl.UpdateAll();
	}
}

// Button message handler
void CSimulatorDlg::OnBtnQuit() 
{
	AfxGetMainWnd()->PostMessage(WM_CLOSE);	
}

void CSimulatorDlg::OnBtnEdit() 
{
	CPipelineApp* pApp = (CPipelineApp*)AfxGetApp();
	pApp->CreateEditView();

	CButton* cb = (CButton*)GetDlgItem(IDC_BTN_EDIT);
	cb->EnableWindow(FALSE);
}

void CSimulatorDlg::OnBtnLoad() 
{
	// construct a file box to open files
	BOOL bOpenFileDialog = TRUE;
	CFileDialog *pDlg = new CFileDialog(bOpenFileDialog, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"MIPS»ã±àÎÄ¼þ (*.mips)|*.mips||");
	pDlg->m_ofn.lpstrTitle = "Load MIPS ASM File";

	if( (pDlg->DoModal() == IDOK) ){
		CString lpszPathName = pDlg->GetPathName();
		if( simulator.LoadInstFromFile(lpszPathName) ) {
			m_textCtrl.Reset();
			POSITION pos = simulator.m_pInsts->m_instList.GetHeadPosition();
			while( pos ) {
				CAsmInstruction* pInst = simulator.m_pInsts->m_instList.GetNext(pos);
				m_textCtrl.AddItem( pInst->InstWithLabelAddress() );
			}
			m_textCtrl.UpdateAll();

			m_btnLoad.EnableWindow( FALSE );
			m_btnReset.EnableWindow( TRUE );
			m_btnStepForward.EnableWindow( TRUE );
			m_btnStepBack.EnableWindow( TRUE );
			m_btnNextCycle.EnableWindow( TRUE );
			m_btnPreCycle.EnableWindow( TRUE );
			m_btnGo.EnableWindow( TRUE );
			m_btnStat.EnableWindow( TRUE );
			m_btnTrace.EnableWindow( TRUE );
		}
	}
}

BOOL CSimulatorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//create text control
	CRect rect;
	GetDlgItem(IDC_ASM_TEXT)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_textCtrl.Create(WS_CHILD|WS_VISIBLE,rect,this);

	m_bThreadStarted = FALSE;
	m_bThreadStop = FALSE;

	m_btnLoad.EnableWindow( FALSE );
	m_btnReset.EnableWindow( FALSE );
	m_btnStepForward.EnableWindow( FALSE );
	m_btnStepBack.EnableWindow( FALSE );
	m_btnNextCycle.EnableWindow( FALSE );
	m_btnPreCycle.EnableWindow( FALSE );
	m_btnGo.EnableWindow( FALSE );
	m_btnStat.EnableWindow( FALSE );
	m_btnTrace.EnableWindow( FALSE );

//	m_btnStop.EnableWindow( FALSE );
	m_btnStop.ShowWindow( SW_HIDE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSimulatorDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect( rect );
	dc.FillSolidRect( rect, RGB( 225,255,255 ) );
}

void CSimulatorDlg::OnBtnConfigure() 
{
	CSimConfigDlg dlg;
	if( dlg.DoModal() == IDOK ) {
		if( !simulator.m_pInsts )
			m_btnLoad.EnableWindow( TRUE );
		else
			m_btnLoad.EnableWindow( FALSE );

		// Create MIPS Pipeline dialog
		if( m_pMIPSPipelineDlg == NULL ) {
			m_pMIPSPipelineDlg = new CMIPSPipelineDlg();
			m_pMIPSPipelineDlg->Create(IDD_MIPS_PIPELINE);
		}
		m_pMIPSPipelineDlg->ShowWindow(SW_SHOW);
		this->SetActiveWindow();
	}
}

void CSimulatorDlg::OnClose() 
{
	AfxGetMainWnd()->PostMessage(WM_CLOSE);	

	CDialog::OnClose();
}

void CSimulatorDlg::OnBtnNextCycle() 
{
	if( simulator.m_nState == CMIPSSimulator::kComplete ) return;
	if( simulator.m_nState == CMIPSSimulator::kNone ) {
		CCycleDlg dlg;
		if( dlg.DoModal() == IDCANCEL ) return;
		simulator.Start();
	}
	simulator.NextCycle();

	m_pMIPSPipelineDlg->NextCycle();
	m_textCtrl.FocusItem( simulator.FindIndexFromAddress(simulator.m_nLastPC) );
}

void CSimulatorDlg::OnBtnPreviousCycle() 
{
	if( simulator.m_nState == CMIPSSimulator::kNone ) return;

	int prevCycle = simulator.GetCurCycle();
	if( prevCycle == 1 ) return;
	prevCycle -= 1;

	// don't trace
	BOOL bTrace = simulator.m_bTrace;
	simulator.m_bTrace = FALSE;//
	simulator.RollBackToStartState();
	m_pMIPSPipelineDlg->Reset();
	while( simulator.GetCurCycle() < prevCycle ) {
		//OnBtnNextCycle();
		simulator.NextCycle();
		m_pMIPSPipelineDlg->m_ExecInstCtrl.NextCycle( FALSE );
	}
	
	m_pMIPSPipelineDlg->m_ExecInstCtrl.DrawAll();
	m_pMIPSPipelineDlg->m_DatapathCtrl.NextCycle();
	m_textCtrl.FocusItem( simulator.FindIndexFromAddress(simulator.m_nLastPC) );

	simulator.m_bTrace = bTrace;// restore
}

void CSimulatorDlg::OnBtnStepForward() 
{
	if( simulator.m_nState == CMIPSSimulator::kComplete ) return;
	if( simulator.m_nState == CMIPSSimulator::kNone ) {
		CCycleDlg dlg;
		if( dlg.DoModal() == IDCANCEL ) return;
		simulator.Start();
		simulator.NextCycle();
		m_pMIPSPipelineDlg->NextCycle();
	} else 
		while( TRUE ) {
			simulator.NextCycle();
			m_pMIPSPipelineDlg->NextCycle();
			if( simulator.IsExecComplete() ) break;
			if( simulator.HasNewStep() )
				if( simulator.GetNewExecInst()->pInst->m_key == IDLE_INST )
					continue;
				else
					break;
		}

	m_textCtrl.FocusItem( simulator.FindIndexFromAddress(simulator.m_nLastPC) );
}

void CSimulatorDlg::OnBtnStepBack() 
{
	if( simulator.m_nState == CMIPSSimulator::kNone ) return;

	int prevStep = simulator.GetCurStep();
	if( prevStep == 1 ) return;
	prevStep -= 1;

	// don't trace
	BOOL bTrace = simulator.m_bTrace;
	simulator.m_bTrace = FALSE;//
	simulator.RollBackToStartState();
	m_pMIPSPipelineDlg->Reset();
	simulator.NextCycle();
	m_pMIPSPipelineDlg->NextCycle();
	while( simulator.GetCurStep() < prevStep ) {
		//OnBtnStepForward();
		while( TRUE ) {
			simulator.NextCycle();
			m_pMIPSPipelineDlg->m_ExecInstCtrl.NextCycle( FALSE );
			if( simulator.IsExecComplete() ) break;
			if( simulator.HasNewStep() )
				if( simulator.GetNewExecInst()->pInst->m_key == IDLE_INST )	continue;
				else break;
		}
	}

	m_pMIPSPipelineDlg->m_ExecInstCtrl.DrawAll();
	m_pMIPSPipelineDlg->m_DatapathCtrl.NextCycle();
	m_textCtrl.FocusItem( simulator.FindIndexFromAddress(simulator.m_nLastPC) );

	simulator.m_bTrace = bTrace;// restore
}

// button command: go
void CSimulatorDlg::EnableButton( BOOL enable )
{
	m_btnConfigure.EnableWindow( enable );
	m_btnLoad.EnableWindow( enable );
	m_btnReset.EnableWindow( enable );
	m_btnStepForward.EnableWindow( enable );
	m_btnStepBack.EnableWindow( enable );
	m_btnNextCycle.EnableWindow( enable );
	m_btnPreCycle.EnableWindow( enable );
	m_btnStat.EnableWindow( enable );
	m_btnTrace.EnableWindow( enable );
}

UINT threadBtnGo( LPVOID pParam )
{
	CSimulatorDlg* pDlg = (CSimulatorDlg*)pParam;

	pDlg->EnableButton( FALSE );
	pDlg->m_btnGo.ShowWindow( SW_HIDE );
	pDlg->m_btnStop.ShowWindow( SW_SHOW );

	pDlg->m_bThreadStarted = TRUE;

	do {
		simulator.NextCycle();
		pDlg->m_pMIPSPipelineDlg->m_ExecInstCtrl.NextCycle( FALSE );
	} while( !simulator.IsExecComplete() && !pDlg->m_bThreadStop );

	pDlg->m_pMIPSPipelineDlg->m_ExecInstCtrl.DrawAll();
	pDlg->m_pMIPSPipelineDlg->m_DatapathCtrl.NextCycle();
	// this will cause problems, no idea
//	pDlg->m_textCtrl.FocusItem( simulator.FindIndexFromAddress(simulator.m_nLastPC) );

	pDlg->m_bThreadStop = FALSE;
	pDlg->m_bThreadStarted = FALSE;

	pDlg->m_btnStop.ShowWindow( SW_HIDE );
	pDlg->m_btnGo.ShowWindow( SW_SHOW );
	pDlg->EnableButton( TRUE );

	return 0;
}

// execute all the instructions
void CSimulatorDlg::OnBtnGo() 
{
	if( simulator.m_nState == CMIPSSimulator::kComplete ) return;
	if( simulator.m_nState == CMIPSSimulator::kNone ) {
		CCycleDlg dlg;
		if( dlg.DoModal() == IDCANCEL ) return;
		simulator.Start();
	}

	AfxBeginThread( threadBtnGo, (LPVOID)this );

/*	do {
		simulator.NextCycle();

		m_pMIPSPipelineDlg->NextCycle();
		m_textCtrl.FocusItem( simulator.FindIndexFromAddress(simulator.m_nLastPC) );
	} while( !simulator.IsExecComplete() );*/
}

void CSimulatorDlg::OnBtnStop() 
{
	m_bThreadStop = TRUE;
}

void CSimulatorDlg::OnBtnTrace() 
{
	if( simulator.m_bTrace ) {
		CString temp;
		temp.Format( "In trace: %s\nSTOP TRACE?", (LPCTSTR)simulator.m_TraceFile.GetFilePath() );
		if( AfxMessageBox(temp, MB_YESNO | MB_ICONQUESTION ) == IDYES )
			simulator.StopTrace();
		return;
	}
	CTraceDlg dlg;
	if( dlg.DoModal() == IDOK ) 
		AfxMessageBox( "Start tracing instructions..." );
}

void CSimulatorDlg::OnBtnReset() 
{
	CResetDlg dlg;
	if( dlg.DoModal() == IDOK )
		switch( dlg.m_nSelState ) {
		case CResetDlg::kAll:
			simulator.Reset();
			m_textCtrl.Reset();
			m_textCtrl.UpdateAll();
			if( m_pMIPSPipelineDlg )
				m_pMIPSPipelineDlg->ResetAndUpdate();
			// set button enable
			m_btnLoad.EnableWindow( FALSE );
			m_btnReset.EnableWindow( FALSE );
			m_btnStepForward.EnableWindow( FALSE );
			m_btnStepBack.EnableWindow( FALSE );
			m_btnNextCycle.EnableWindow( FALSE );
			m_btnPreCycle.EnableWindow( FALSE );
			m_btnGo.EnableWindow( FALSE );
			m_btnStat.EnableWindow( FALSE );
			m_btnTrace.EnableWindow( FALSE );
			break;

		case CResetDlg::kNewProgram:
			simulator.ResetProgram();
			m_textCtrl.Reset();
			m_textCtrl.UpdateAll();
			if( m_pMIPSPipelineDlg )
				m_pMIPSPipelineDlg->ResetAndUpdate();
			// set button enable
			m_btnLoad.EnableWindow( TRUE );
			m_btnReset.EnableWindow( FALSE );
			m_btnStepForward.EnableWindow( FALSE );
			m_btnStepBack.EnableWindow( FALSE );
			m_btnNextCycle.EnableWindow( FALSE );
			m_btnPreCycle.EnableWindow( FALSE );
			m_btnGo.EnableWindow( FALSE );
			m_btnStat.EnableWindow( FALSE );
			m_btnTrace.EnableWindow( FALSE );

			OnBtnLoad();
			break;

		case CResetDlg::kNewConfig:
			OnBtnConfigure();
			break;

		case CResetDlg::kRestart:
			simulator.RollBackToStartState();
			m_textCtrl.FocusItem( simulator.FindIndexFromAddress(simulator.PC) );
			//m_textCtrl.Reset();
			//m_textCtrl.UpdateAll();
			if( m_pMIPSPipelineDlg )
				m_pMIPSPipelineDlg->ResetAndUpdate();
		}
}

void CSimulatorDlg::OnBtnStat() 
{
	CStatDlg dlg;
	dlg.DoModal();
}

