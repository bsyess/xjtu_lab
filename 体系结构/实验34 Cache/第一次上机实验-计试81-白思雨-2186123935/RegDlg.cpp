// RegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pipeline.h"
#include "RegDlg.h"
#include "MIPSSimulator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog

CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegDlg)
	//}}AFX_DATA_INIT
	m_bEditable = TRUE;
	m_bInputFault = FALSE;
	mode = kHex;
}

void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDlg)
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_REG_GRID, m_GridCtrl);
}

BEGIN_MESSAGE_MAP(CRegDlg, CDialog)
	//{{AFX_MSG_MAP(CRegDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_HEX, OnRadioHex)
	ON_BN_CLICKED(IDC_RADIO_DEC, OnRadioDec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers

BOOL CRegDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitGrid();

	m_RadioHex.SubclassDlgItem(IDC_RADIO_HEX, this);
	m_RadioHex.SetCheck(mode == kHex);

	m_RadioDec.SubclassDlgItem(IDC_RADIO_DEC, this);
	m_RadioDec.SetCheck(mode == kDec);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRegDlg::InitGrid()
{
	UINT nMaxCol = 32;
	UINT nMaxRow = 1;
	for( int i = 0; i < 32; i++ )
		reg[i] = simulator.reg[i].content;

    m_GridCtrl.SetRowCount( nMaxRow + 1 );
    m_GridCtrl.SetFixedRowCount( 1 );
    m_GridCtrl.SetColumnCount( nMaxCol + 1 );
    m_GridCtrl.SetFixedColumnCount( 1 );
	m_GridCtrl.SetRowResize( FALSE );
	m_GridCtrl.SetColumnResize( FALSE );
	m_GridCtrl.SetEditable( m_bEditable );
	
	for( int row = 0; row < m_GridCtrl.GetRowCount(); row++ )
		for( int col = 0; col < m_GridCtrl.GetColumnCount(); col++ )
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			if( row == 0 && col == 0 ) {
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.szText = _T("Register");
			} else if( row < m_GridCtrl.GetFixedRowCount() ) {
				Item.nFormat = DT_CENTER|DT_WORDBREAK;
				Item.szText.Format( _T("%.2d"), col-1 );
			} else if( col < m_GridCtrl.GetFixedColumnCount() ) {
				Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				Item.szText = _T("Content");
			} else {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				if( mode == kHex )
					Item.szText.Format( _T("%.8X"),(UINT)reg[col-1] );
				else
					Item.szText.Format( _T("%d"), reg[col-1] );
			}
			m_GridCtrl.SetItem( &Item );
		}

	m_GridCtrl.SetItemState( 1, 1, m_GridCtrl.GetItemState(1, 1)|GVIS_READONLY );
	m_GridCtrl.AutoSize();
}

void CRegDlg::ResetGrid()
{
	for( int col = 1; col < m_GridCtrl.GetColumnCount(); col++ )
	{ 
		CString temp;
		if( mode == kHex )
			temp.Format( "%.8X", (UINT)reg[col-1] );
		else 
			temp.Format( "%d", reg[col-1] );
		m_GridCtrl.SetItemText(1, col, (LPCTSTR)temp);
	}
	m_GridCtrl.RedrawRow( 1 );
}

// updata data in CRegDlg, not updata to simulator
void CRegDlg::UpdateReg()
{
	m_GridCtrl.SetFocus();
	for( int col = 1; col < m_GridCtrl.GetColumnCount(); col++ ) {
		if( mode == kHex ) {
			if( ::sscanf(m_GridCtrl.GetItemText(1, col), "%x", &reg[col-1]) != 1 ) {
				m_bInputFault = TRUE;
				break;
			}
		} else {
			if( ::sscanf(m_GridCtrl.GetItemText(1, col), "%d", &reg[col-1]) != 1 ) {
				m_bInputFault = TRUE;
				break;
			}
		}
	}
	if( m_bInputFault )
		for( int i = 0; i < 32; i++ ) reg[i] = simulator.reg[i].content;
}

void CRegDlg::EnableEdit( BOOL flag )
{
	m_bEditable = flag;
}

void CRegDlg::OnClose() 
{
	if( m_bEditable ) {
		UpdateReg();
		if( m_bInputFault )
			MessageBox( "输入错误！\n回滚原始寄存器数据。", "警告！", MB_ICONSTOP );
		else {
			BOOL bChanged = FALSE;
			int i;
			for( i = 0; i < 32; i++ ) 
				if( reg[i] != simulator.reg[i].content ) {
					bChanged = TRUE;
					break;
				}
			if( bChanged ) 
				if( MessageBox("请确认是否更新寄存器数据？", "请注意！",
					MB_YESNO | MB_ICONQUESTION) == IDYES )
					for( i = 0; i < 32; i++ ) simulator.reg[i].content = reg[i];
		}
	}
	
	CDialog::OnClose();
}

void CRegDlg::OnRadioHex() 
{
	if( mode == kHex ) return;
	if( m_bEditable ) {
		UpdateReg();
		if( m_bInputFault ) {
			MessageBox( "输入错误！\n回滚原始寄存器数据。", "警告！",
				MB_ICONINFORMATION );
			m_bInputFault = FALSE;
		}
	}
	mode = kHex;
	ResetGrid();
}

void CRegDlg::OnRadioDec() 
{
	if( mode == kDec ) return;
	if( m_bEditable ) {
		UpdateReg();
		if( m_bInputFault ) {
			MessageBox( "输入错误！\n回滚原始寄存器数据。", "警告！",
				MB_ICONINFORMATION );
			m_bInputFault = FALSE;
		}
	}
	mode = kDec;
	ResetGrid();
}
