#if !defined(AFX_ATTR_H__7E293507_70EF_4665_B402_B38DAD7BB164__INCLUDED_)
#define AFX_ATTR_H__7E293507_70EF_4665_B402_B38DAD7BB164__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Line.h : header file
//

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CLine

class CLine
{
public:
	CLine();
	virtual ~CLine();

// Attributes
public:
	int			m_penStyle;
	int			m_penWidth;
	COLORREF	m_penColor;
	COLORREF	m_bkColor;

	int			m_bkMode;
	int			m_drawMode;

	BOOL		m_bAttached;
	BOOL		m_bArrow;

	CArray<CPoint, CPoint&> m_pointArray;// line poly point
										 // note: only support vertical or horizontal lines

// Operations
public:
	void Init();
	void Reset();

	void SetPenStyle( int nStyle );
	void SetPenWidth( int nWidth );
	void SetPenColor( COLORREF clr );
	void SetBkColor( COLORREF clr );

	void SetBkMode( int bkMode = OPAQUE );
	void SetDrawMode( int drawMode = R2_COPYPEN );

	void SetAttached( BOOL bAttached = TRUE );
	void SetArrow( BOOL bArrow = TRUE ) { m_bArrow = bArrow; }

	void PolyAdd( CPoint& point );
	void PolyAdd( int x, int y );
	void Draw( CDC* pDC, int penStyle = PS_SOLID, int penWidth = 1, COLORREF penColor = RGB(0,0,0) );
	void Erase( CDC* pDC );
};

#endif // !defined(AFX_ATTR_H__7E293507_70EF_4665_B402_B38DAD7BB164__INCLUDED_)
