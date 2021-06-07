// line.cpp : implementation file
//

#include "stdafx.h"
#include "line.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLine

CLine::CLine()
{
	Init();
}

CLine::~CLine()
{
	m_pointArray.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
// CLine message handlers

void CLine::Init()
{
	m_penStyle = PS_SOLID;
	m_penWidth = 1;
	m_penColor = RGB( 0, 0, 0 );
	m_bkColor = RGB( 225,255,255 );

	m_bkMode = OPAQUE;
	m_drawMode = R2_COPYPEN;

	m_bAttached = FALSE;
	m_bArrow = TRUE;
}

void CLine::Reset()
{
	Init();
	m_pointArray.RemoveAll();
}

void CLine::SetPenStyle(int nStyle)
{
	m_penStyle = nStyle;
}

void CLine::SetPenWidth(int nWidth)
{
	m_penWidth = nWidth;
}

void CLine::SetPenColor(COLORREF clr)
{
	m_penColor = clr;
}

void CLine::SetBkColor( COLORREF clr )
{
	m_bkColor = clr;
}

void CLine::SetBkMode(int bkMode)
{
	m_bkMode = bkMode;
}

void CLine::SetDrawMode(int drawMode)
{
	m_drawMode = drawMode;
}

void CLine::SetAttached( BOOL bAttached )
{
	m_bAttached = bAttached;
}

void CLine::PolyAdd( CPoint& point )
{
	m_pointArray.Add( point );
}

void CLine::PolyAdd( int x, int y )
{
	m_pointArray.Add( CPoint(x, y) );
}

void CLine::Draw( CDC* pDC, int penStyle, int penWidth, COLORREF penColor )
{
	m_penStyle = penStyle;
	m_penWidth = penWidth;
	m_penColor = penColor;

	CPen pen;
	pen.CreatePen( m_penStyle, m_penWidth, m_penColor );
	CPen* oldPen = (CPen*)pDC->SelectObject( &pen );
	int oldBkMode = pDC->SetBkMode( m_bkMode );
	int oldDrawMode = pDC->SetROP2( m_drawMode );

	CPoint start, end;
	start = m_pointArray[0];
	if( m_bAttached ) {
		// Draw attach point
		CRect rect;// attach point
		rect.left = start.x - 2;
		rect.right = start.x + 3;// ellipse NOT include the right and bottom of the rect
		rect.top = start.y - 2;
		rect.bottom = start.y + 3;

		CBrush brush, oldBrush;
		brush.CreateSolidBrush( m_penColor );
		CBrush* pOldBrush = (CBrush*)pDC->SelectObject( brush );
		oldBrush.FromHandle((HBRUSH)pOldBrush);

		pDC->Ellipse( &rect );

		pDC->SelectObject( &oldBrush );
	}

	// Draw lines
	pDC->MoveTo( start );
	for( int i = 1; i < m_pointArray.GetSize(); i++ ) {
		end = m_pointArray[i];
		pDC->LineTo( end );
	}

	if( m_bArrow ) {
		// Draw Arrows
		CPoint pt1, pt2, pt3, pt4;
		pt1.x = pt4.x = end.x - 7;
		pt2.x = pt3.x = end.x - 7;
		pt1.y = end.y - 2;
		pt2.y = end.y - 1;
		pt3.y = end.y + 1;
		pt4.y = end.y + 2;
		pDC->MoveTo( pt1 ); pDC->LineTo( end );
		pDC->MoveTo( pt2 ); pDC->LineTo( end );
		pDC->MoveTo( pt3 ); pDC->LineTo( end );
		pDC->MoveTo( pt4 ); pDC->LineTo( end );
	}

	// restore
	pDC->SetROP2( oldDrawMode );
	pDC->SetBkMode( oldBkMode );
	pDC->SelectObject( oldPen );
}

void CLine::Erase( CDC* pDC )
{
	Draw( pDC, m_penStyle, m_penWidth, m_bkColor );
}
