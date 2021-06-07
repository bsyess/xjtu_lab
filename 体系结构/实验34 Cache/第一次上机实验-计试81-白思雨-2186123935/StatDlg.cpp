// StatDlg.cpp : implementation file
//

#include "stdafx.h"

#include "pipeline.h"
#include "StatDlg.h"
#include "MIPSSimulator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatDlg dialog


CStatDlg::CStatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatDlg)
	//}}AFX_DATA_INIT
}

void CStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatDlg)
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_STAT, m_GridCtrl);
}

BEGIN_MESSAGE_MAP(CStatDlg, CDialog)
	//{{AFX_MSG_MAP(CStatDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatDlg message handlers

BOOL CStatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UINT COUNT[19];
	CString LABEL_MAP[] = {
		"", "LW", "SW", "ADD", "SUB", "MUL", "DIV", "AND", "OR", "XOR",
		"BEQZ", "BNEZ", "J", "JR", "TOTAL", "TYPE", "TYPE R", "TYPE I", "TYPE J"
	};

	COUNT[1] = simulator.STAT.nLW;
	COUNT[2] = simulator.STAT.nSW;
	COUNT[3] = simulator.STAT.nADD + simulator.STAT.nADDI;
	COUNT[4] = simulator.STAT.nSUB + simulator.STAT.nSUBI;
	COUNT[5] = simulator.STAT.nMUL + simulator.STAT.nMUT + simulator.STAT.nMULI + simulator.STAT.nMUTI;
	COUNT[6] = simulator.STAT.nDIV + simulator.STAT.nDIVI;
	COUNT[7] = simulator.STAT.nAND + simulator.STAT.nANDI;
	COUNT[8] = simulator.STAT.nOR + simulator.STAT.nORI;
	COUNT[9] = simulator.STAT.nXOR + simulator.STAT.nXORI;
	COUNT[10] = simulator.STAT.nBEQZ;
	COUNT[11] = simulator.STAT.nBNEZ;
	COUNT[12] = simulator.STAT.nJ;
	COUNT[13] = simulator.STAT.nJR;
	COUNT[16] = simulator.STAT.nADD + simulator.STAT.nSUB + simulator.STAT.nMUL +
		simulator.STAT.nMUT + simulator.STAT.nDIV + simulator.STAT.nAND +
		simulator.STAT.nOR + simulator.STAT.nXOR;
	COUNT[17] = simulator.STAT.nLW + simulator.STAT.nSW + simulator.STAT.nADDI +
		simulator.STAT.nSUBI + simulator.STAT.nMULI + simulator.STAT.nMUTI +
		simulator.STAT.nDIVI + simulator.STAT.nANDI + simulator.STAT.nORI +
		simulator.STAT.nXORI + simulator.STAT.nBEQZ + simulator.STAT.nBNEZ +
		simulator.STAT.nJR;
	COUNT[18] = simulator.STAT.nJ;
	COUNT[14] = COUNT[16] + COUNT[17] + COUNT[18];
	COUNT[0] = COUNT[14];
	if( COUNT[0] <= 0 ) COUNT[0] = 1;

	m_GridCtrl.SetRowCount( 19 );
    m_GridCtrl.SetFixedRowCount( 1 );
    m_GridCtrl.SetColumnCount( 3 );
    m_GridCtrl.SetFixedColumnCount( 1 );
	m_GridCtrl.SetRowResize( FALSE );
	m_GridCtrl.SetColumnResize( FALSE );
	m_GridCtrl.SetEditable( FALSE );

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.row = 0;
	Item.col = 0;
	Item.szText = _T("          ");
	m_GridCtrl.SetItem( &Item );
	Item.col = 1;
	Item.szText = _T("  Counts  ");
	m_GridCtrl.SetItem( &Item );
	Item.col = 2;
	Item.szText = _T("Percentage");
	m_GridCtrl.SetItem( &Item );
	for( int row = 1; row < m_GridCtrl.GetRowCount(); row++ ) {
		Item.row = row;
		if( row == 15 ) {
			Item.col = 0;
			Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
			Item.szText = _T("TYPES");
			m_GridCtrl.SetItem( &Item );
			continue;
		}
		for( int col = 0; col < m_GridCtrl.GetColumnCount(); col++ ) {
			Item.col = col;
			if( col == 0 ) {
				Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				Item.szText = LABEL_MAP[row];
			} else {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				if( col == 1 )
					Item.szText.Format( "%d", COUNT[row] );
				else {
					Item.szText.Format( "%4.2f", (float)COUNT[row]/COUNT[0]*100 );
					Item.szText += "%";
				}
			}
			m_GridCtrl.SetItem( &Item );
		}
	}

	for( int col = 0; col < m_GridCtrl.GetColumnCount(); col++ ) {
		m_GridCtrl.SetItemBkColour( 14, col, RGB(236,233,216) );
		m_GridCtrl.SetItemBkColour( 15, col, RGB(217,233,192) );
		m_GridCtrl.SetItemBkColour( 16, col, RGB(217,233,192) );
		m_GridCtrl.SetItemBkColour( 17, col, RGB(217,233,192) );
		m_GridCtrl.SetItemBkColour( 18, col, RGB(217,233,192) );
	}

	m_GridCtrl.AutoSize();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
