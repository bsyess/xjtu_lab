// ExecInstCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "pipeline.h"
#include "ExecInstCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExecInstCtrl

CExecInstCtrl::CExecInstCtrl()
{
	Reset();
}

CExecInstCtrl::~CExecInstCtrl()
{
	if(memDC.GetSafeHdc() != NULL)
	{
		memDC.SelectObject( m_pOldBitmap );
		if( m_pBitmap != NULL )
			delete m_pBitmap;

		memDC.SelectObject( m_pOldFont );
	}
	if( !m_rowList.IsEmpty() ) {
		ITEM_ROW* row = m_rowList.RemoveHead();
		delete row;
	}
}

BEGIN_MESSAGE_MAP(CExecInstCtrl, CWnd)
	//{{AFX_MSG_MAP(CExecInstCtrl)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExecInstCtrl message handlers

BOOL CExecInstCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd)
{
	m_pParentWnd = pParentWnd;
	scrollbar_width = GetSystemMetrics(SM_CXVSCROLL);

	// create window
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	BOOL ret = CWnd::CreateEx( 0/*WS_EX_CLIENTEDGE*/, className, NULL, dwStyle, 
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		pParentWnd->GetSafeHwnd(), 0);
	// init virtual screen
	GetClientRect( rcClient );
	CClientDC dc( this );
	if( memDC.GetSafeHdc() == NULL ) {
		memDC.CreateCompatibleDC( &dc );

		if( (m_pBitmap = new CBitmap()) == NULL ) return FALSE;
		m_pBitmap->CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() );	
		m_pOldBitmap = memDC.SelectObject( m_pBitmap );

		CFont NewFont;
		NewFont.CreateFont( -13, 0, 0, 0, FW_MEDIUM, 0, 0,
			0, 134, 3, 2, 1, 2, "Courier New" );
		m_pOldFont = memDC.SelectObject( &NewFont );
		memDC.SetBkMode( TRANSPARENT );
	}
	memDC.FillSolidRect( &rcClient, m_BkColor );

	return ret;
}

void CExecInstCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if( memDC.GetSafeHdc() != NULL )
		dc.BitBlt( 0, 0, rcClient.Width(), rcClient.Height(), &memDC, 0, 0, SRCCOPY );
}

void CExecInstCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(pScrollBar == GetScrollBarCtrl(SB_HORZ))
	{
		if(nSBCode == SB_LEFT || nSBCode == SB_LINELEFT || nSBCode == SB_PAGELEFT)
			x_offset -= m_nColWidth;
		if(nSBCode == SB_RIGHT || nSBCode == SB_LINERIGHT || nSBCode == SB_PAGERIGHT)
			x_offset += m_nColWidth;
		if(nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
			x_offset = nPos * m_nColWidth;
		if(x_offset < 0)
			x_offset = 0;
		if(x_offset / m_nColWidth > m_nMaxCol - 2)
			x_offset = (m_nMaxCol - 2) * m_nColWidth;
		SetScrollPos(SB_HORZ, x_offset / m_nColWidth, TRUE);
		DrawAll();
	}
}

void CExecInstCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(pScrollBar == GetScrollBarCtrl(SB_VERT))
	{
		if(nSBCode == SB_TOP || nSBCode == SB_LINEUP || nSBCode == SB_PAGEUP) {
			y_offset -= m_nRowHeight;
		} else if(nSBCode == SB_BOTTOM || nSBCode == SB_LINEDOWN ||	nSBCode == SB_PAGEDOWN) {
			y_offset += m_nRowHeight;
		} else if(nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) {
			y_offset = nPos * m_nRowHeight;
		}
		if( y_offset < 0 ) y_offset = 0;
		if( y_offset / m_nRowHeight > m_nMaxRow - 2 )
			y_offset = (m_nMaxRow - 2) * m_nRowHeight;
		SetScrollPos(SB_VERT, y_offset / m_nRowHeight, TRUE);
		DrawAll();
	}
}

void CExecInstCtrl::NextCycle( BOOL bRedraw )
{
	if( m_nState == kComplete || simulator.m_nState == CMIPSSimulator::kComplete )
		return;

	// add new instructions
	if( m_nState == kNone || simulator.HasNewStep() ) {
		m_nState = kRun;
		CExecInst* pExecInst = simulator.GetNewExecInst();
		ASSERT( pExecInst );
		int address = pExecInst->pInst->m_nAddress;
		COLORREF textColor = pExecInst->color;
		CString instString = pExecInst->pInst->InstString();
		int StartCycle = simulator.GetCurCycle();
		UINT_ARRAY StageArray;
		simulator.GetStageArray(pExecInst, StageArray);
		AddExecInst( address, textColor, instString, StartCycle, StageArray );
	}
	m_nCurCycle++;

	// remove completed instructions
	if( m_bInstComplete )
		for( int i = 0; i < addressArray.GetSize(); i++ )
			RemoveExecInst( addressArray[i] );
	if( m_bIdleInstComplete )
		RemoveExecInst( -1 );
	m_bInstComplete = simulator.HasInstComplete( addressArray );
	m_bIdleInstComplete = simulator.HasIdleInstComplete();

	if( simulator.IsExecComplete() ) m_nState = kComplete;

	if( bRedraw ) DrawAll();
}

void CExecInstCtrl::Reset()
{
	image_size = CSize(0,0);
	x_offset = 0;
	y_offset = 0;

	m_BkColor = RGB( 135,206,250 );
	defaultTextBkColor = RGB( 135,206,250 );
	defaultTextFgColor = RGB(0,0,0);

	while( !m_rowList.IsEmpty() ) {
		ITEM_ROW* row = m_rowList.RemoveHead();
		delete row;
	}
	m_nMaxRow = 0;
	m_nMaxCol = 0;
	m_nStartCycle = 0;
	m_nCurCycle = -1;
	m_bInstComplete = FALSE;
	m_bIdleInstComplete = FALSE;

	m_nState = kNone;
}

void CExecInstCtrl::ResetAndUpdate()
{
	Reset();
//	UpdateAll();
}

BOOL CExecInstCtrl::SetBackColor(COLORREF color)
{
	m_BkColor = color;
	return TRUE;
}

BOOL CExecInstCtrl::SetFont(CFont* pFont, BOOL bRedraw/*= TRUE*/)
{
	memDC.SelectObject( pFont );
	if( bRedraw ) Invalidate();
	return TRUE;
}

void CExecInstCtrl::AddExecInst( int address, COLORREF textColor,
	CString& instString, int StartCycle, UINT_ARRAY& StageArray )
{
	if( m_nMaxRow == 0 ) {
		m_nMaxRow = 1;
		m_nStartCycle = StartCycle;
		m_nCurCycle = StartCycle - 1;
		// add fixed row
		ITEM_ROW* row = new ITEM_ROW;
		row->m_nAddress = -1;
		m_rowList.AddHead( row );
	}
	m_nMaxRow += 1;
	UINT offset = StartCycle - m_nStartCycle + 1;
	UINT num = offset + StageArray.GetSize();
	if( m_nMaxCol < num ) {
		m_nMaxCol = num;
		AdjustFixRow();
	}
	// add row
	ITEM_ROW* row = new ITEM_ROW;
	row->m_nAddress = address;
	row->m_nStartCycle = StartCycle;
	// adjust this row
	ITEM item;
	item.row = m_nMaxRow - 1;
	item.m_TextBkColor = defaultTextBkColor;
	for( UINT col = 0; col < num; col++ ) {
		item.col = col;
		item.m_TextFgColor = defaultTextFgColor;
		if( col == 0 ) {
			item.szText = CString(_T(" ")) + instString;
			item.m_TextFgColor = textColor;
		} else if( col < offset )
			item.szText = _T("");
		else
			item.szText = MIPSStage[ StageArray[col-offset] ];
		row->m_itemList.AddTail( item );
	}
	m_rowList.AddTail( row );

	AdjustClientArea();
}

void CExecInstCtrl::RemoveExecInst( int address )
{
	int  index = 1;
	BOOL found = FALSE;
	ITEM_ROW* remove = NULL;
	POSITION pos = m_rowList.GetHeadPosition();
	m_rowList.GetNext( pos );// fix row
	while( pos ) {
		remove = m_rowList.GetNext( pos );
		if( remove->m_nAddress == address ) {
			found = TRUE; break;
		}
		index++;
	}
	// This inst should be existed
	if( !found ) {
#ifdef _DEBUG
		AfxMessageBox( "CExecInstCtrl::RemoveExecInst() error." );
#endif //_DEBUG
		return;
	}
	if( index == 1 && pos ) {
		// need to adjust following rows
		ITEM_ROW* next = m_rowList.GetNext( pos );
		UINT offset = next->m_nStartCycle - remove->m_nStartCycle;
		m_nMaxCol -= offset;
		m_nStartCycle += offset;
		AdjustFixRow();
		for( int i = offset; i > 0; i-- )
			next->m_itemList.RemoveAt( next->m_itemList.FindIndex(i) );
		while( pos ) {
			next = m_rowList.GetNext( pos );
			for( int i = offset; i > 0; i-- )
				next->m_itemList.RemoveAt( next->m_itemList.FindIndex(i) );
		}
	}
	m_rowList.RemoveAt( m_rowList.FindIndex(index) );
	m_nMaxRow--;
	delete remove;

	AdjustClientArea();
}

// When m_nStartCycle or m_nMaxCol changed, call this function
void CExecInstCtrl::AdjustFixRow()
{
	ITEM_ROW* row = m_rowList.GetHead();
	row->m_itemList.RemoveAll();
	UINT cycle = m_nStartCycle;
	ITEM item;
	item.row = 0;
	item.m_TextBkColor = defaultTextBkColor;
	item.m_TextFgColor = defaultTextFgColor;
	for( UINT col = 0; col < m_nMaxCol; col++ ) {
		item.col = col;
		if( col == 0 )
			item.szText = _T("");
		else
			item.szText.Format( "%u", cycle++ );
		row->m_itemList.AddTail( item );
	}
}

// call this function when contents of the control
// or the client rect is changed
void CExecInstCtrl::AdjustClientArea()
{
	//reset scrollbar
	SCROLLINFO si;
	si.fMask = SIF_PAGE | SIF_RANGE;
	si.nMin = 0;
	si.nMax = 0;
	si.nPage = 0;
	SetScrollInfo(SB_HORZ, &si, TRUE);
	SetScrollInfo(SB_VERT, &si, TRUE);
	
	//redraw background
	GetClientRect(&rcClient);
	memDC.FillSolidRect(&rcClient, m_BkColor);

	// calculate image size
	CSize nMargin = memDC.GetTextExtent( _T(" "), 1 );
	m_nFixColWidth = 22 * nMargin.cx;
	m_nColWidth = 7 * nMargin.cx;
	m_nFixRowHeight = m_nRowHeight = nMargin.cy + 4;

	image_size.cy = m_nRowHeight * m_nMaxRow;
	image_size.cx = m_nFixColWidth + (m_nMaxCol - 1) * m_nColWidth;
	
	// check if image size fits the client rect
	rcClient.bottom -= scrollbar_width;
	// VScrollBar
	ShowScrollBar(SB_HORZ);
	si.nMax = m_nMaxCol - 2;
	SetScrollInfo(SB_HORZ, &si, TRUE);

	BOOL y_fit;
	y_fit = (image_size.cy <= rcClient.Height());
	if( !y_fit )
		rcClient.right -= scrollbar_width;
	if( !y_fit ) {
		// show HScrollBar
		ShowScrollBar(SB_VERT);
		si.nMax = m_nMaxRow - 2;
		SetScrollInfo(SB_VERT, &si, TRUE);
	}
}

BOOL CExecInstCtrl::GetItem( int row, int col, ITEM& outItem )
{
	if( row < -1 || row >= m_rowList.GetCount() )
		return FALSE;
	ITEM_ROW* _row = m_rowList.GetAt( m_rowList.FindIndex(row) );
	if( col < -1 || col >= _row->m_itemList.GetCount() )
		return FALSE;
	outItem = _row->m_itemList.GetAt( _row->m_itemList.FindIndex(col) );
	return TRUE;
}

void CExecInstCtrl::DrawItem( int row, int col, BOOL TextOnly, BOOL invalid )
{
	CRect rect;
	if( row == 0 ) rect.top = 0;
	else rect.top = m_nFixRowHeight + (row-1)*m_nRowHeight;
	rect.bottom = m_nFixRowHeight + row*m_nRowHeight - 1;
	if( col == 0 ) rect.left = 0;
	else rect.left = m_nFixColWidth + (col-1)*m_nColWidth;
	rect.right = m_nFixColWidth + col*m_nColWidth - 1;

	if( row == 0 && col == 0 ) ;// do nothing
	else if( row == 0 ) {// fixed row
		rect.OffsetRect( -x_offset, 0 );
		if( rect.left < (int)m_nFixColWidth ) return;
	} else if( col == 0 ) {// fixed col
		rect.OffsetRect( 0, -y_offset );
		if( rect.top < (int)m_nFixRowHeight ) return;
	} else {
		// normal item
		rect.OffsetRect( -x_offset, -y_offset );
		if( rect.right < (int)m_nFixColWidth ||
			rect.bottom < (int)m_nFixRowHeight )
			// can't see, just return
			return;
	}

	ITEM item;
	if( GetItem(row, col, item) ) {
		if( !TextOnly )
			memDC.FillSolidRect( &rect, item.m_TextBkColor );
		memDC.SetTextColor( item.m_TextFgColor );
		if( col == 0 )
			memDC.DrawText( item.szText, &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE );
		else
			memDC.DrawText( item.szText, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	} else if( !TextOnly )
		memDC.FillSolidRect( &rect, defaultTextBkColor );
	if( invalid )
		InvalidateRect( &rect );
}

void CExecInstCtrl::DrawRow( int row, BOOL TextOnly, BOOL invalid )
{
	for( UINT col = 0; col < m_nMaxCol; col++ )
		DrawItem( row, col, TextOnly, invalid );
}

void CExecInstCtrl::DrawCol( int col, BOOL TextOnly, BOOL invalid )
{
	for( UINT row = 0; row < m_nMaxRow; row++ )
		DrawItem( row, col, TextOnly, invalid );
}

void CExecInstCtrl::DrawAll( BOOL invalid )
{
	memDC.FillSolidRect(&rcClient, m_BkColor);
	ShadeCol();
	for( int row = 0; row < m_rowList.GetCount(); row++ )
		DrawRow( row, TRUE/*text only*/, FALSE );
	if( invalid )
		Invalidate();
}

void CExecInstCtrl::ShadeCol()
{
	CRect rect;
	rect.left = m_nFixColWidth + (m_nCurCycle - m_nStartCycle) * m_nColWidth;
	rect.top = 0;
	rect.right = rect.left + m_nColWidth - 1;
	rect.bottom = rcClient.bottom;

	rect.OffsetRect( -x_offset, 0 );
	if( rect.right < (int)m_nFixColWidth ) return;
	memDC.FillSolidRect( &rect, RGB(200,200,200) );
}
