// ResetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pipeline.h"
#include "ResetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResetDlg dialog


CResetDlg::CResetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nSelState = kCancel;
}


void CResetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResetDlg)
	DDX_Control(pDX, ID_BTN_RESTART, m_btnRestart);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, ID_BTN_PROGRAM, m_btnProgram);
	DDX_Control(pDX, ID_BTN_CONFIG, m_btnConfig);
	DDX_Control(pDX, ID_BTN_ALL, m_btnAll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResetDlg, CDialog)
	//{{AFX_MSG_MAP(CResetDlg)
	ON_BN_CLICKED(ID_BTN_ALL, OnBtnAll)
	ON_BN_CLICKED(ID_BTN_CONFIG, OnBtnConfig)
	ON_BN_CLICKED(ID_BTN_PROGRAM, OnBtnProgram)
	ON_BN_CLICKED(ID_BTN_RESTART, OnBtnRestart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResetDlg message handlers

void CResetDlg::OnBtnAll() 
{
	m_nSelState = kAll;
	CDialog::OnOK();
}

void CResetDlg::OnBtnConfig() 
{
	m_nSelState = kNewConfig;
	CDialog::OnOK();
}

void CResetDlg::OnBtnProgram() 
{
	m_nSelState = kNewProgram;
	CDialog::OnOK();
}

void CResetDlg::OnBtnRestart() 
{
	m_nSelState = kRestart;
	CDialog::OnOK();
}
