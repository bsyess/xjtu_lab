// CycleDlg.cpp : implementation file
// Download by http://down.liehuo.net

#include "stdafx.h"
#include "pipeline.h"
#include "CycleDlg.h"
#include "MIPSSimulator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCycleDlg dialog

CCycleDlg::CCycleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCycleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCycleDlg)
	m_edit = 0;
	//}}AFX_DATA_INIT
}

void CCycleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCycleDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, ID_BTN_DEFAULT, m_btnDefault);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDV_MinMaxUInt(pDX, m_edit, 0, 4096);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCycleDlg, CDialog)
	//{{AFX_MSG_MAP(CCycleDlg)
	ON_BN_CLICKED(ID_BTN_DEFAULT, OnBtnDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCycleDlg message handlers

void CCycleDlg::OnOK() 
{
	UpdateData();
	if( simulator.FindIndexFromAddress(m_edit) < 0 ) {
		CString temp;
		temp.Format( "Address %d is out of program addresses' range!", m_edit );
		AfxMessageBox( temp, MB_OK | MB_ICONSTOP );
		CDialog::OnCancel();
	} else {
		simulator.PC = m_edit;
		CDialog::OnOK();
	}
}

void CCycleDlg::OnBtnDefault() 
{
	simulator.PC = simulator.m_nDataSize;
	CDialog::OnOK();
}
