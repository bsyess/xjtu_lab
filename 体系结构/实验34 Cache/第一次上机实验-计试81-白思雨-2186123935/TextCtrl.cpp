// TextCtrl.cpp : implementation file
//

#include "stdafx.h"

#include "TextCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextCtrl

CTextCtrl::CTextCtrl()
{
	Reset();
}

CTextCtrl::~CTextCtrl()
{
	if(memDC.GetSafeHdc() != NULL)
	{
		memDC.SelectObject( m_pOldBitmap );
		if( m_pBitmap != NULL )
			delete m_pBitmap;

		memDC.SelectObject( m_pOldFont );
	}
}

BEGIN_MESSAGE_MAP(CTextCtrl, CWnd)
	//{{AFX_MSG_MAP(CTextCtrl)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTextCtrl message handlers

void CTextCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if( memDC.GetSafeHdc() != NULL )
		dc.BitBlt( 0, 0, rcClient.Width(), rcClient.Height(), &memDC, 0, 0, SRCCOPY );
}

BOOL CTextCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd)
{
	m_pParentWnd = pParentWnd;
	scrollbar_width = GetSystemMetrics(SM_CXVSCROLL);

	// create window
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,AfxGetApp()->LoadStandardCursor(IDC_IBEAM));
	BOOL ret = CWnd::CreateEx( WS_EX_CLIENTEDGE, className, NULL, dwStyle, 
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
		NewFont.CreateFont( -13, 0, 0, 0, FW_NORMAL, 0, 0,
			0, 134, 3, 2, 1, 2, "Arial" );
		m_pOldFont = memDC.SelectObject( &NewFont );
		memDC.SetBkMode( TRANSPARENT );
	}
	memDC.FillSolidRect( &rcClient, m_BkColor );
	m_nMargin = memDC.GetTextExtent( _T(" "), 1 ).cx;

	// set copyright
	CRect staticRect;
	staticRect.right = rcClient.right;
	staticRect.left = staticRect.right - 18 * m_nMargin;
	staticRect.bottom = rcClient.bottom;
	staticRect.top = rcClient.bottom - 16;
	memDC.DrawText( _T("作者：计试81白思雨"), staticRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE );

	return ret;
}

void CTextCtrl::Reset()
{
	image_size = CSize(0,0);
	x_offset = 0;
	y_offset = 0;
	m_nTopItemIndex = 0;

	m_BkColor = RGB(225,255,255);
	defaultTextBkColor = RGB(225,255,255);
	defaultTextFgColor = RGB(0,0,0);

	m_itemList.RemoveAll();
	m_nLastFocusedItemIndex = -1;
}

void CTextCtrl::ResetAndUpdate()
{
	Reset();
	UpdateAll();
}

BOOL CTextCtrl::SetBackColor(COLORREF color)
{
	m_BkColor = color;
	return TRUE;
}

BOOL CTextCtrl::SetFont(CFont* pFont, BOOL bRedraw/*= TRUE*/)
{
	memDC.SelectObject( pFont );
	if( bRedraw ) Invalidate();
	return TRUE;
}

void CTextCtrl::AddItem(CString& str)
{
	ITEM item;
	item.m_strContent = str;
	item.m_TextBkColor = defaultTextBkColor;
	item.m_TextFgColor = defaultTextFgColor;
	item.m_TextSize = memDC.GetTextExtent( str );
	item.m_TextSize += CSize( 2*m_nMargin, m_nMargin / 2 );

	if( image_size.cx < item.m_TextSize.cx )
		image_size.cx = item.m_TextSize.cx;
	image_size.cy += item.m_TextSize.cy;
	
	m_itemList.AddTail( item );
}

BOOL CTextCtrl::SetItemText(int col, CString& str)
{
	ITEM& item = m_itemList.GetAt( m_itemList.FindIndex(col) );
	item.m_strContent = str;
	int cy = item.m_TextSize.cy;
	item.m_TextSize = memDC.GetTextExtent( str );
	item.m_TextSize += CSize( 2*m_nMargin, 1*m_nMargin );

	if( image_size.cx < item.m_TextSize.cx )
		image_size.cx = item.m_TextSize.cx;
	image_size.cy += (item.m_TextSize.cy - cy);

	return TRUE;
}

BOOL CTextCtrl::SetItemBkColor(int col, COLORREF color)
{
	ITEM& item = m_itemList.GetAt( m_itemList.FindIndex(col) );
	item.m_TextBkColor = color;
	return TRUE;
}

BOOL CTextCtrl::SetItemFgColor(int col, COLORREF color)
{
	ITEM& item = m_itemList.GetAt( m_itemList.FindIndex(col) );
	item.m_TextFgColor = color;
	return TRUE;
}

void CTextCtrl::SetClientRect()
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
	
	//check image size
	BOOL x_fit;
	BOOL y_fit;
	x_fit = (image_size.cx <= rcClient.Width());
	if( !x_fit )
		rcClient.bottom -= scrollbar_width;
	y_fit = (image_size.cy <= rcClient.Height());
	if( !y_fit ) {
		rcClient.right -= scrollbar_width;
		x_fit = (image_size.cx <= rcClient.Width());
	}
	if( !x_fit ) {
		// show scrollbar
		ShowScrollBar(SB_HORZ);
		// update scrollbar
		SCROLLINFO si;
		si.fMask = SIF_PAGE | SIF_RANGE;
		si.nMin = 0;
		si.nMax = image_size.cx - 1;
		si.nPage = rcClient.Width();
		SetScrollInfo(SB_HORZ, &si, TRUE);
	}
	if( !y_fit ) {
		// show scrollbar
		ShowScrollBar(SB_VERT);
		// update scrollbar
		SCROLLINFO si;
		si.fMask = SIF_PAGE | SIF_RANGE;
		si.nMin = 0;
		si.nMax = m_itemList.GetCount() - 1;
		si.nPage = 0;
		SetScrollInfo(SB_VERT, &si, TRUE);
	}
}

BOOL CTextCtrl::CalcItemRect(int col, CRect& outItemRect, CRect& outTextRect)
{
	int index = 0;
	ITEM item = m_itemList.GetAt( m_itemList.FindIndex(index) );
	outItemRect.bottom = -1;
	while( TRUE ) {
		outItemRect.top = outItemRect.bottom + 1;
		outItemRect.bottom += item.m_TextSize.cy;
		if( index == col ) break;
		if( ++index >= m_itemList.GetCount() )
			return FALSE;
		item = m_itemList.GetAt( m_itemList.FindIndex(index) );
	}
	// calculate logical item rect
	outItemRect.left = 0;
	outItemRect.right = rcClient.Width();
	outItemRect.OffsetRect( 0, -y_offset );

	// calculate logical text rect
	outTextRect.CopyRect( outItemRect );
	outTextRect.right = outTextRect.left + item.m_TextSize.cx;
	outTextRect.OffsetRect( m_nMargin - x_offset, m_nMargin/4 );

	return TRUE;
}

void CTextCtrl::DrawItem( int col, BOOL bRedraw )
{
	CRect rcItemRect, rcTextRect;

	ITEM item = m_itemList.GetAt( m_itemList.FindIndex(col) );
	CalcItemRect(col, rcItemRect, rcTextRect);

	memDC.FillSolidRect( rcItemRect, item.m_TextBkColor );
	memDC.SetTextColor( item.m_TextFgColor );
	memDC.DrawText( item.m_strContent, rcTextRect,
		DT_LEFT | DT_VCENTER | DT_SINGLELINE );

	if( bRedraw ) InvalidateRect(rcItemRect);
}

void CTextCtrl::DrawAll( BOOL bRedraw )
{
	memDC.FillSolidRect( rcClient, m_BkColor );
	for( int index = 0; index < m_itemList.GetCount(); index++ )
		DrawItem( index, FALSE );
	if( bRedraw ) Invalidate();
}

void CTextCtrl::UpdateAll( BOOL bRedraw )
{
	SetClientRect();
	DrawAll( bRedraw );
}

void CTextCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nSmall = 1;
	int nLarge = 20;

	if(pScrollBar == GetScrollBarCtrl(SB_HORZ))
	{
		if(nSBCode == SB_LEFT || nSBCode == SB_LINELEFT)
			x_offset -= nSmall;
		if(nSBCode == SB_PAGELEFT)
			x_offset -= nLarge;
		if(nSBCode == SB_RIGHT || nSBCode == SB_LINERIGHT)
			x_offset += nSmall;
		if(nSBCode == SB_PAGERIGHT)
			x_offset += nLarge;
		if(nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
			x_offset = (int)nPos;
		if(x_offset < 0)
			x_offset = 0;
		if(x_offset > image_size.cx - rcClient.Width())
			x_offset = image_size.cx - rcClient.Width();
		SetScrollPos(SB_HORZ, x_offset, TRUE);
		DrawAll();
	}
}

void CTextCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int oldOffset = y_offset, nDownOffset = 0, nUpOffset = 0;

	if( m_nTopItemIndex < m_itemList.GetCount() - 1 ) {
		ITEM item = m_itemList.GetAt( m_itemList.FindIndex(m_nTopItemIndex) );
		nDownOffset = item.m_TextSize.cy;
	}
	if( m_nTopItemIndex > 0 ) {
		ITEM item = m_itemList.GetAt( m_itemList.FindIndex(m_nTopItemIndex - 1) );
		nUpOffset = item.m_TextSize.cy;
	}
	
	if(pScrollBar == GetScrollBarCtrl(SB_VERT))
	{
		if(nSBCode == SB_TOP || nSBCode == SB_LINEUP || nSBCode == SB_PAGEUP) {
			y_offset -= nUpOffset;
			if( m_nTopItemIndex > 0 )
				m_nTopItemIndex--;
		} else if(nSBCode == SB_BOTTOM || nSBCode == SB_LINEDOWN ||	nSBCode == SB_PAGEDOWN) {
			y_offset += nDownOffset;
			if( m_nTopItemIndex < m_itemList.GetCount() - 1 )
				m_nTopItemIndex++;
		} else if(nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) {
			m_nTopItemIndex = (int)nPos;
			y_offset = 0;
			for( int i = 0; i < m_nTopItemIndex; i++ ) {
				ITEM item = m_itemList.GetAt( m_itemList.FindIndex(i) );
				y_offset += item.m_TextSize.cy;
			}
		}
		SetScrollPos(SB_VERT, m_nTopItemIndex, TRUE);
		DrawAll();
	}
}

BOOL CTextCtrl::IsItemVisiable(int index)
{
	CRect rcItemRect, rcTextRect;
	
	CalcItemRect(index, rcItemRect, rcTextRect);
	if( rcItemRect.top >= 0 && rcItemRect.bottom < rcClient.Height() )
		return TRUE;
	return FALSE;
}

void CTextCtrl::FocusItem(int index, COLORREF bkColor, COLORREF fgColor)
{
	if( index < 0 || index >= m_itemList.GetCount() )
		return;

	// make it visiable
	CRect rcItemRect, rcTextRect;
	CalcItemRect(index, rcItemRect, rcTextRect);
	if( rcItemRect.top < 0 || 
		rcItemRect.bottom >= rcClient.Height() ||
		x_offset != 0 ) {
		x_offset = 0;
		y_offset += rcItemRect.top;
		m_nTopItemIndex = index;
		SetScrollPos(SB_VERT, m_nTopItemIndex, TRUE);
		DrawAll();
	}

	// change its color
	if( index == m_nLastFocusedItemIndex ) return;
	if( m_nLastFocusedItemIndex >= 0 ) {
		ITEM& item = m_itemList.GetAt( m_itemList.FindIndex(m_nLastFocusedItemIndex) );
		item = m_LastFocusedItem;
		DrawItem( m_nLastFocusedItemIndex );
	}
	m_nLastFocusedItemIndex = index;
	m_LastFocusedItem = m_itemList.GetAt( m_itemList.FindIndex(index) );
	SetItemBkColor( index, bkColor );
	SetItemFgColor( index, fgColor );
	DrawItem( index );
}
