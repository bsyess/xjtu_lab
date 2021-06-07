// SimConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pipeline.h"
#include "SimConfigDlg.h"
#include "MIPSSimulator.h"
#include "MemDlg.h"
#include "RegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimConfigDlg dialog

CSimConfigDlg::CSimConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimulatorDlg)
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	//}}AFX_DATA_INIT
}

void CSimConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimConfigDlg)
	DDX_Control(pDX, ID_BTN_REG, m_btnReg);
	DDX_Control(pDX, ID_BTN_MEM, m_btnMem);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_SLIDER3, m_SliderMem);
	DDX_Control(pDX, IDC_SLIDER2, m_SliderDiv);
	DDX_Control(pDX, IDC_SLIDER1, m_SliderMul);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CSimConfigDlg)
	ON_BN_CLICKED(IDC_RADIO_FREEZE, OnRadioFreeze)
	ON_BN_CLICKED(IDC_RADIO_PREDICT_TOKEN, OnRadioPredictToken)
	ON_BN_CLICKED(IDC_RADIO_PREDICT_NOT_TOKEN, OnRadioPredictNotToken)
	ON_BN_CLICKED(IDC_RADIO_DELAYED_BRANCH, OnRadioDelayedBranch)
	ON_BN_CLICKED(IDC_RADIO_FORWARDING, OnRadioForwarding)
	ON_BN_CLICKED(IDC_RADIO_NOT_FORWARDING, OnRadioNotForwarding)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(ID_BTN_MEM, OnBtnMem)
	ON_BN_CLICKED(ID_BTN_REG, OnBtnReg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimConfigDlg message handlers

BOOL CSimConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_nBranchMethod = simulator.m_nBranchMethod;
	m_bForwardingEnable = simulator.m_bForwardingEnable;

	m_nMulDelay = simulator.m_nMulDelay;
	m_nDivDelay = simulator.m_nDivDelay;
	m_nDataSize = simulator.m_nDataSize;

	m_RadioFreeze.SubclassDlgItem(IDC_RADIO_FREEZE, this);
	m_RadioPredictToken.SubclassDlgItem(IDC_RADIO_PREDICT_TOKEN, this);
	m_RadioRredictNotToken.SubclassDlgItem(IDC_RADIO_PREDICT_NOT_TOKEN, this);
	m_RadioDelayedBranch.SubclassDlgItem(IDC_RADIO_DELAYED_BRANCH, this);

	m_RadioForwarding.SubclassDlgItem(IDC_RADIO_FORWARDING, this);
	m_RadioNotForwarding.SubclassDlgItem(IDC_RADIO_NOT_FORWARDING, this);

	SetRadioCheck();

	m_edit1.Format( "%d", m_nMulDelay );
	m_SliderMul.SetRange(1, 10, TRUE);
	m_SliderMul.SetPos( m_nMulDelay );

	m_edit2.Format( "%d", m_nDivDelay );
	m_SliderDiv.SetRange(1, 50, TRUE);
	m_SliderDiv.SetPos( m_nDivDelay );

	m_edit3.Format( "%d", m_nDataSize );
	m_SliderMem.SetRange(1, 16, TRUE);
	m_SliderMem.SetPos( m_nDataSize / 256 );

	UpdateData(FALSE);

	if( simulator.m_nState != CMIPSSimulator::kNone )
		m_SliderMem.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSimConfigDlg::SetRadioCheck()
{
	m_RadioFreeze.SetCheck( m_nBranchMethod == CMIPSSimulator::kFreeze );
	m_RadioPredictToken.SetCheck( m_nBranchMethod == CMIPSSimulator::kPredictedTaken );
	m_RadioRredictNotToken.SetCheck( m_nBranchMethod == CMIPSSimulator::kPredictedNotTaken );
	m_RadioDelayedBranch.SetCheck( m_nBranchMethod == CMIPSSimulator::kDelayedBranch );

	m_RadioForwarding.SetCheck( m_bForwardingEnable );
	m_RadioNotForwarding.SetCheck( !m_bForwardingEnable );
}

void CSimConfigDlg::OnRadioFreeze() 
{
	m_nBranchMethod = CMIPSSimulator::kFreeze;
	SetRadioCheck();
}

void CSimConfigDlg::OnRadioPredictToken() 
{
	m_nBranchMethod = CMIPSSimulator::kPredictedTaken;
	SetRadioCheck();
}

void CSimConfigDlg::OnRadioPredictNotToken() 
{
	m_nBranchMethod = CMIPSSimulator::kPredictedNotTaken;
	SetRadioCheck();
}

void CSimConfigDlg::OnRadioDelayedBranch() 
{
	m_nBranchMethod = CMIPSSimulator::kDelayedBranch;
	SetRadioCheck();
}

void CSimConfigDlg::OnRadioForwarding() 
{
	m_bForwardingEnable = TRUE;
	SetRadioCheck();
}

void CSimConfigDlg::OnRadioNotForwarding() 
{
	m_bForwardingEnable = FALSE;
	SetRadioCheck();
}

void CSimConfigDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	UpdateSliderData();
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSimConfigDlg::UpdateSliderData()
{
	m_nMulDelay = m_SliderMul.GetPos();
	m_nDivDelay = m_SliderDiv.GetPos();
	m_nDataSize = m_SliderMem.GetPos() * 256;

	m_edit1.Format( "%d", m_nMulDelay );
	m_edit2.Format( "%d", m_nDivDelay );
	m_edit3.Format( "%d", m_nDataSize );

	UpdateData(FALSE);
}

void CSimConfigDlg::OnOK() 
{
	simulator.m_nBranchMethod = m_nBranchMethod;
	simulator.m_bForwardingEnable = m_bForwardingEnable;

	simulator.m_nMulDelay = m_nMulDelay;
	simulator.m_nDivDelay = m_nDivDelay;
	simulator.m_nDataSize = m_nDataSize;
	simulator.CreateDataMem();

	if( simulator.m_pInsts ) {
		// update Simulator Dialog
		CPipelineApp* pApp = (CPipelineApp*)AfxGetApp();
		pApp->m_pSimulatorDlg->UpdateTextCtrl();
	}
	
	CDialog::OnOK();
}

void CSimConfigDlg::OnBtnMem() 
{
	if( m_nDataSize != simulator.m_nDataSize ) {
		if( AfxMessageBox("更新MIPS数据段大小？",
			MB_YESNO | MB_ICONQUESTION) == IDYES )
			simulator.m_nDataSize = m_nDataSize;
		else {
			m_nDataSize = simulator.m_nDataSize;
			m_edit3.Format( "%d", m_nDataSize );
			m_SliderMem.SetPos( m_nDataSize / 256 );
			UpdateData(FALSE);
		}
	}

	simulator.CreateDataMem();
	CMemDlg dlg;
	dlg.DoModal();
}

void CSimConfigDlg::OnBtnReg() 
{
	CRegDlg dlg;
	dlg.DoModal();
}
