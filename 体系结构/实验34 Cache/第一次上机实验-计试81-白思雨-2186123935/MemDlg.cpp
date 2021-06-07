// MemDlg.cpp : implementation file
//

#include "stdafx.h"

#include "pipeline.h"
#include "MemDlg.h"
#include "MIPSSimulator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemDlg dialog

CMemDlg::CMemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMemDlg)
	//}}AFX_DATA_INIT
	m_bEditable = TRUE;
	m_bInputFault = FALSE;
	data = NULL;
}

CMemDlg::~CMemDlg()
{
	if( data ) free( data );
}

void CMemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemDlg)
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_MEM_GRID, m_GridCtrl);
}

BEGIN_MESSAGE_MAP(CMemDlg, CDialog)
	//{{AFX_MSG_MAP(CMemDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_BIGENDING, OnRadioBigending)
	ON_BN_CLICKED(IDC_RADIO_LITTLEENDING, OnRadioLittleending)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemDlg message handlers

BOOL CMemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitGrid();

	m_RadioBig.SubclassDlgItem(IDC_RADIO_BIGENDING, this);
	m_RadioBig.SetCheck(simulator.m_bBigEnding);

	m_RadioLittle.SubclassDlgItem(IDC_RADIO_LITTLEENDING, this);
	m_RadioLittle.SetCheck(!simulator.m_bBigEnding);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMemDlg::InitGrid()
{
	UINT nMaxCol = 16;
	UINT nMaxRow = simulator.m_nDataSize / nMaxCol;
	if( data ) free( data );
	data = (int*)malloc( simulator.m_nDataSize );
	::memcpy( data, simulator.data, simulator.m_nDataSize );

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
			if( row == 0 && col == 0 )
				continue;
			if( row < m_GridCtrl.GetFixedRowCount() ) {
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.szText.Format( _T("%.2d"), col-1 );
				m_GridCtrl.SetItem( &Item );
			} else if( col < m_GridCtrl.GetFixedColumnCount() ) {
				Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				Item.szText.Format( _T("0x%.3X0"),row-1 );
				m_GridCtrl.SetItem( &Item );
			} else {
				unsigned char bytes[4];
				*(int*)&bytes[0] = data[(row-1)*4 + (col-1)/4];
				if( simulator.m_bBigEnding ) {
					char c;
					c = bytes[0]; bytes[0] = bytes[3]; bytes[3] = c;
					c = bytes[1]; bytes[1] = bytes[2]; bytes[2] = c;
				}
				for( int i = 0; i < 4; i++ ) {
					Item.col = col + i;
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					Item.szText.Format( _T("%.2X"),(UINT)bytes[i] );
					m_GridCtrl.SetItem( &Item );
				}
				col += 3;
			}
		}

	m_GridCtrl.AutoSize();
}

void CMemDlg::ResetGrid()
{
	for( int row = 1; row < m_GridCtrl.GetRowCount(); row++ ) {
		for( int col = 1; col < m_GridCtrl.GetColumnCount(); col += 4 ) { 
			unsigned char bytes[4];
			*(int*)&bytes[0] = data[(row-1)*4 + (col-1)/4];
			if( simulator.m_bBigEnding ) {
				char c;
				c = bytes[0]; bytes[0] = bytes[3]; bytes[3] = c;
				c = bytes[1]; bytes[1] = bytes[2]; bytes[2] = c;
			}
			for( int i = 0; i < 4; i++ ) {
				CString temp;
				temp.Format( _T("%.2X"),(UINT)bytes[i] );
				m_GridCtrl.SetItemText(row, col+i, (LPCTSTR)temp );
			}
		}
		m_GridCtrl.RedrawRow( row );
	}
}

// updata data in CMemDlg, not updata to simulator
void CMemDlg::UpdateMem()
{
	ASSERT( data );

	m_GridCtrl.SetFocus();
	for( int row = 1; row < m_GridCtrl.GetRowCount(); row++ ) {
		for( int col = 1; col < m_GridCtrl.GetColumnCount(); col += 4 ) {
			unsigned char bytes[4];
			for( int i = 0; i < 4; i++ ) {
				UINT temp = 0xFFFFFFFF;
				::sscanf( m_GridCtrl.GetItemText(row, col+i), "%x", &temp );
				if( temp > 255 ) { m_bInputFault = TRUE; break; }
				bytes[i] = (unsigned char)temp;
			}
			if( m_bInputFault ) break;
			if( simulator.m_bBigEnding ) {
				char c;
				c = bytes[0]; bytes[0] = bytes[3]; bytes[3] = c;
				c = bytes[1]; bytes[1] = bytes[2]; bytes[2] = c;
			}
			data[(row-1)*4 + (col-1)/4] = *(int*)&bytes[0];
		}
		if( m_bInputFault ) break;
	}
	if( m_bInputFault )
		memcpy( data, simulator.data, simulator.m_nDataSize );
}

void CMemDlg::EnableEdit( BOOL flag )
{
	m_bEditable = flag;
}

void CMemDlg::OnClose() 
{
	ASSERT( data );

	if( m_bEditable ) {
		UpdateMem();
		if( m_bInputFault )
			MessageBox( "输入错误！\n回滚原始内存数据。", "警告！", MB_ICONSTOP );
		else if( ::memcmp(data, simulator.data, simulator.m_nDataSize) != 0 )
			if( MessageBox("请确认是否更新内存数据？", "请注意！",
				MB_YESNO | MB_ICONQUESTION) == IDYES )
				::memcpy( simulator.data, data, simulator.m_nDataSize );
	}

	CDialog::OnClose();
}

void CMemDlg::OnRadioBigending() 
{
	if( simulator.m_bBigEnding )
		return;
	if( m_bEditable ) {
		UpdateMem();
		if( m_bInputFault ) {
			MessageBox( "输入错误！\n回滚原始内存数据。", "警告！",
				MB_ICONINFORMATION );
			m_bInputFault = FALSE;
		}
	}
	simulator.m_bBigEnding = TRUE;
	ResetGrid();
}

void CMemDlg::OnRadioLittleending() 
{
	if( !simulator.m_bBigEnding )
		return;
	if( m_bEditable ) {
		UpdateMem();
		if( m_bInputFault ) {
			MessageBox( "输入错误！\n回滚原始内存数据。", "警告！",
				MB_ICONINFORMATION );
			m_bInputFault = FALSE;
		}
	}
	simulator.m_bBigEnding = FALSE;
	ResetGrid();
}
