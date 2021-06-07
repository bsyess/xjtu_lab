// IntegerDatapathCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "pipeline.h"
#include "IntegerDatapathCtrl.h"
#include "MIPSSimulator.h"

#include "MemDlg.h"
#include "RegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntegerDatapathCtrl

CIntegerDatapathCtrl::CIntegerDatapathCtrl()
{
	m_penStyle = PS_SOLID;
	m_penWidth = 1;
	m_penColor = RGB( 0, 0, 0 );
	m_regColor = RGB( 200, 200, 200 );
	m_bkColor = RGB( 225,255,255 );
}

CIntegerDatapathCtrl::~CIntegerDatapathCtrl()
{
	if(memDC.GetSafeHdc() != NULL)
	{
		memDC.SelectObject( m_pOldBitmap );
		if( m_pBitmap != NULL )
			delete m_pBitmap;

		memDC.SelectObject( m_pOldFont );
	}
}


BEGIN_MESSAGE_MAP(CIntegerDatapathCtrl, CWnd)
	//{{AFX_MSG_MAP(CIntegerDatapathCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CIntegerDatapathCtrl message handlers

void CIntegerDatapathCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if( memDC.GetSafeHdc() != NULL )
		dc.BitBlt( 0, 0, rcClient.Width(), rcClient.Height(), &memDC, 0, 0, SRCCOPY );
}

BOOL CIntegerDatapathCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd)
{
	m_pParentWnd = pParentWnd;

	// create window
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	BOOL ret = CWnd::CreateEx( NULL, className, NULL, dwStyle, 
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
		NewFont.CreateFont( -9, 0, 0, 0, FW_SEMIBOLD, 0, 0,
			0, 134, 3, 2, 1, 2, "Microsoft Sans Serif" );
		m_pOldFont = memDC.SelectObject( &NewFont );
		memDC.SetBkMode( TRANSPARENT );// use TRANSPARENT
	}

	memDC.FillSolidRect( &rcClient, m_bkColor );
	InitLines();
	DrawAll();

	return ret;
}

void CIntegerDatapathCtrl::Reset()
{
	RestoreIFLines( FALSE );
	RestoreIDLines( FALSE );
	RestoreEXLines( FALSE );
	RestoreMEMLines( FALSE );
	RestoreWBLines( FALSE );
	
	DrawAll();
	Invalidate();
}

void CIntegerDatapathCtrl::NextCycle( BOOL bRedraw )
{
	Reset();

	CExecInst* next = simulator.m_pExecInsts->next;
	while( next ) {
		if( next->m_nLastStage == IF && next->pInst->m_key != IDLE_INST )
			IFLines( PS_SOLID, 3, next->color, next->pInst->InstString() );
		else if( next->m_nLastStage == ID && next->pInst->m_key != IDLE_INST )
			IDLines( PS_SOLID, 3, next->color, next->pInst->InstString() );
		else if( next->m_nLastStage == EX && next->pInst->m_key != IDLE_INST &&
			next->pInst->m_key != MUL && next->pInst->m_key != MUT &&
			next->pInst->m_key != DIV && next->pInst->m_key != MULI	&&
			next->pInst->m_key != MUTI && next->pInst->m_key != DIVI )
			EXLines( PS_SOLID, 3, next->color, next->pInst->InstString() );
		else if( next->m_nLastStage == MEM && next->pInst->m_key != IDLE_INST &&
			next->pInst->m_key != MUL && next->pInst->m_key != MUT &&
			next->pInst->m_key != DIV && next->pInst->m_key != MULI	&&
			next->pInst->m_key != MUTI && next->pInst->m_key != DIVI )
			MEMLines( PS_SOLID, 3, next->color, next->pInst->InstString() );
		else if( next->m_nLastStage == WB && next->pInst->m_key != IDLE_INST &&
			next->pInst->m_key != SW )
			WBLines( PS_SOLID, 3, next->color, next->pInst->InstString() );

		next = next->next;
	}

	if( bRedraw ) Invalidate();
}

/********************************************************
 * draw circuits
 ********************************************************/
void CIntegerDatapathCtrl::InitLines()
{
	// IF
	CRect rect;
	l1.PolyAdd( 40, 165 ); l1.PolyAdd( 72, 165 );

	l2.PolyAdd( 47, 165 ); l2.PolyAdd( 47, 138 ); l2.PolyAdd( 59, 138 );
	l2.SetAttached();

	l3.PolyAdd( 47, 96 ); l3.PolyAdd( 59, 96 );

	l4.PolyAdd( 125, 195 ); l4.PolyAdd( 144, 195 );
	rect.left = 125; rect.right = 144; rect.top = 180; rect.bottom = 194;
	memDC.DrawText( "IR", &rect, DT_CENTER | DT_VCENTER );

	l5.PolyAdd( 92, 128 ); l5.PolyAdd( 108, 128 );

	l6.PolyAdd( 125, 120 ); l6.PolyAdd( 144, 120 );

	l7.PolyAdd( 131, 120 ); l7.PolyAdd( 131, 70 ); l7.PolyAdd( 10, 70 );
	l7.PolyAdd( 10, 165 ); l7.PolyAdd( 20, 165 );
	l7.SetAttached();

	// ID
	l8.PolyAdd( 165, 120 ); l8.PolyAdd( 230, 120 );
	l8.PolyAdd( 230, 90 ); l8.PolyAdd( 270, 90 );

	l9.PolyAdd( 165, 195 ); l9.PolyAdd( 170, 195 );
	l9.PolyAdd( 170, 159 ); l9.PolyAdd( 232, 159 );
	// text "IR6..10"
	rect.left = 170; rect.right = 232; rect.top = 144; rect.bottom = 159;
	memDC.DrawText( "IR6..10", &rect, DT_CENTER | DT_VCENTER );

	l10.PolyAdd( 170, 185 ); l10.PolyAdd( 232, 185 );
	l10.SetAttached();
	// text "IR11..15"
	rect.left = 170; rect.right = 232; rect.top = 170; rect.bottom = 185;
	memDC.DrawText( "IR10..15", &rect, DT_CENTER | DT_VCENTER );

	l11.PolyAdd( 170, 195 ); l11.PolyAdd( 170, 280 ); l11.PolyAdd( 210, 280 );
	l11.SetAttached();
	// text "16"
	rect.left = 200; rect.right = 210; rect.top = 265; rect.bottom = 280;
	memDC.DrawText( "16", &rect, DT_CENTER | DT_VCENTER );

	l12.PolyAdd( 170, 280 ); l12.PolyAdd( 170, 310 ); l12.PolyAdd( 350, 310 );
	l12.SetAttached();

	l13.PolyAdd( 250, 280 ); l13.PolyAdd( 350, 280 );
	// text "32"
	rect.left = 252; rect.right = 270; rect.top = 265; rect.bottom = 280;
	memDC.DrawText( "32", &rect, DT_LEFT | DT_VCENTER );

	l14.PolyAdd( 288, 280 ); l14.PolyAdd( 288, 140 ); l14.PolyAdd( 245, 140 );
	l14.PolyAdd( 245, 50 ); l14.PolyAdd( 270, 50 );
	l14.SetAttached();

	l15.PolyAdd( 284, 220 ); l15.PolyAdd( 350, 220 );

	l16.PolyAdd( 284, 176 ); l16.PolyAdd( 350, 176 );

	l17.PolyAdd( 292, 176 ); l17.PolyAdd( 292, 115 ); l17.PolyAdd( 304, 115 );
	l17.SetAttached();

	l18.PolyAdd( 340, 115 ); l18.PolyAdd( 344, 115 ); l18.PolyAdd( 344, 24 );
	l18.PolyAdd( 116, 24 ); l18.PolyAdd( 116, 100 );
	l18.SetArrow( FALSE );

	l19.PolyAdd( 303, 70 ); l19.PolyAdd( 321, 70 ); l19.PolyAdd( 321, 32 );
	l19.PolyAdd( 97, 32 ); l19.PolyAdd( 97, 110 ); l19.PolyAdd( 108, 110 );

	// EX
	l20.PolyAdd( 371, 176 ); l20.PolyAdd( 430, 176 );

	l21.PolyAdd( 371, 225 ); l21.PolyAdd( 400, 225 );

	l22.PolyAdd( 417, 225 ); l22.PolyAdd( 430, 225 );

	l23.PolyAdd( 380, 225 ); l23.PolyAdd( 380, 250 ); l23.PolyAdd( 480, 250 );
	l23.SetAttached();

	l24.PolyAdd( 371, 280 ); l24.PolyAdd( 390, 280 ); 
	l24.PolyAdd( 390, 235 ); l24.PolyAdd( 400, 235 );

	l25.PolyAdd( 371, 310 ); l25.PolyAdd( 480, 310 );

	l26.PolyAdd( 470, 199 ); l26.PolyAdd( 480, 199 );

	// MEM
	l27.PolyAdd( 501, 199 ); l27.PolyAdd( 540, 199 );

	l28.PolyAdd( 520, 199 ); l28.PolyAdd( 520, 270 ); l28.PolyAdd( 605, 270 );
	l28.SetAttached();

	l29.PolyAdd( 501, 250 ); l29.PolyAdd( 540, 250 );

	l30.PolyAdd( 590, 225 ); l30.PolyAdd( 605, 225 );
	
	l31.PolyAdd( 501, 310 ); l31.PolyAdd( 605, 310 );

	// WB
	l32.PolyAdd( 626, 225 ); l32.PolyAdd( 650, 225 );

	l33.PolyAdd( 626, 270 ); l33.PolyAdd( 638, 270 );
	l33.PolyAdd( 638, 245 ); l33.PolyAdd( 650, 245 );

	l34.PolyAdd( 626, 310 ); l34.PolyAdd( 660, 310 ); l34.PolyAdd( 660, 328 );
	l34.PolyAdd( 175, 328 ); l34.PolyAdd( 175, 211 ); l34.PolyAdd( 232, 211 );
	// text "MEM/WB.IR
	rect.left = 172; rect.right = 232; rect.top = 196, rect.bottom = 211;
	memDC.DrawText( "MEMWB.IR", &rect, DT_LEFT | DT_VCENTER );

	l35.PolyAdd( 668, 235 ); l35.PolyAdd( 680, 235 ); l35.PolyAdd( 680, 336 );
	l35.PolyAdd( 180, 336 ); l35.PolyAdd( 180, 237 ); l35.PolyAdd( 232, 237 );
}

// Call InitLines() prior to this function if first call
void CIntegerDatapathCtrl::DrawAll()
{
//	memDC.FillSolidRect( &rcClient, m_bkColor );
	IFCircuits();
	IFIDRegs();
	IDCircuits();
	IDEXRegs();
	EXCircuits();
	EXMEMRegs();
	MEMCircuits();
	MEMWBRegs();
	WBCircuits();
}

// IF
void CIntegerDatapathCtrl::IFCircuits()
{
	CPen pen;
	pen.CreatePen( m_penStyle, m_penWidth, m_penColor );
	CPen* pOldPen = (CPen*)memDC.SelectObject( &pen );

	CBrush brush, oldBrush;
	brush.CreateSolidBrush( m_bkColor );
	CBrush* pOldBrush = (CBrush*)memDC.SelectObject( brush );
	oldBrush.FromHandle((HBRUSH)pOldBrush);

	CRect rect;

	// PC rectangle
	rect.left = 20; rect.top = 138; rect.right = 40; rect.bottom = 192;
	memDC.Rectangle( &rect );
	// text "PC"
	rect.top = 159; rect.bottom = 171;
	memDC.DrawText( "PC", &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK );

	// Instruction Memory
	rect.left = 72; rect.top = 155; rect.right = 125; rect.bottom = 220;
	memDC.Rectangle( &rect );
	// text "instruction memory"
	rect.top = 170; rect.bottom = 200;
	memDC.DrawText( "Instr\nmemory", &rect, DT_CENTER | DT_VCENTER );

	// ADD
	CPoint poly[8];
	poly[0] = CPoint( 59, 128 ); poly[1] = CPoint( 59, 147 );
	poly[2] = CPoint( 92, 131 ); poly[3] = CPoint( 92, 104 );
	poly[4] = CPoint( 59, 88 );  poly[5] = CPoint( 59, 107 );
	poly[6] = CPoint( 67, 118 ); poly[7] = CPoint( 59, 128 );
	memDC.Polyline( poly, 8 );
	// text "ADD"
	rect.left = 67; rect.top = 112; rect.right = 95, rect.bottom = 123;
	memDC.DrawText( "ADD", &rect, DT_LEFT | DT_VCENTER );
	// text "4"
	rect.left = 40; rect.right = 47; rect.top = 90; rect.bottom = 102;
	memDC.DrawText( "4", &rect, DT_CENTER | DT_VCENTER );

	// Mux
	rect.left = 108; rect.right = 125; rect.top = 100; rect.bottom = 140;
	memDC.RoundRect( &rect, CPoint(17, 17) );
	// text "Mux"
	memDC.DrawText( "M\nu\nx", &rect, DT_CENTER | DT_VCENTER );

	IFLines( m_penStyle, m_penWidth, m_penColor );

	memDC.SelectObject( &oldBrush );
	memDC.SelectObject( pOldPen );
}

void CIntegerDatapathCtrl::IFLines( int penStyle, int penWidth, COLORREF penColor, CString& str )
{
	m_IFPenStyle = penStyle;
	m_IFPenWidth = penWidth;
	m_IFPenColor = penColor;
	m_IFStr = str;

	l1.Draw( &memDC, penStyle, penWidth, penColor );
	l2.Draw( &memDC, penStyle, penWidth, penColor );
	l3.Draw( &memDC, penStyle, penWidth, penColor );
	l4.Draw( &memDC, penStyle, penWidth, penColor );
	l5.Draw( &memDC, penStyle, penWidth, penColor );
	l6.Draw( &memDC, penStyle, penWidth, penColor );
	l7.Draw( &memDC, penStyle, penWidth, penColor );

	// show current instructions
	CRect rect( 0, 0, 144, 20 );
	COLORREF clr = memDC.SetTextColor( penColor );
	memDC.DrawText( str, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK );
	memDC.SetTextColor( clr );
}

void CIntegerDatapathCtrl::RestoreIFLines( BOOL bCore )
{
	IFLines( m_IFPenStyle, m_IFPenWidth, m_bkColor, m_IFStr );
	m_IFStr = _T("");
	if( bCore )	IFLines( m_penStyle, m_penWidth, m_penColor );
}

// IF/ID
void CIntegerDatapathCtrl::IFIDRegs()
{
	CPen pen;
	pen.CreatePen( m_penStyle, m_penWidth, m_penColor );
	CPen* pOldPen = (CPen*)memDC.SelectObject( &pen );

	CBrush brush, oldBrush;
	brush.CreateSolidBrush( m_regColor );
	CBrush* pOldBrush = (CBrush*)memDC.SelectObject( brush );
	oldBrush.FromHandle((HBRUSH)pOldBrush);

	CRect rect( 144, 75, 165, 320 );
	memDC.Rectangle( &rect );
	// text "IF/ID"
	rect.left = 140; rect.right = 170; rect.top = 60; rect.bottom = 74;
	memDC.DrawText( "IF/ID", &rect, DT_CENTER | DT_VCENTER );

	memDC.SelectObject( &oldBrush );
	memDC.SelectObject( pOldPen );
}

// ID
void CIntegerDatapathCtrl::IDCircuits()
{
	CPen pen;
	pen.CreatePen( m_penStyle, m_penWidth, m_penColor );
	CPen* pOldPen = (CPen*)memDC.SelectObject( &pen );

	CBrush brush1, oldBrush1;
	brush1.CreateSolidBrush( RGB(197, 197, 243) );
	CBrush* pOldBrush = (CBrush*)memDC.SelectObject( brush1 );
	oldBrush1.FromHandle((HBRUSH)pOldBrush);

	// Registers
	CRect rect( 232, 146, 284, 250 );
	memDC.Rectangle( &rect );
	// text "Registers"
	rect.top = 192; rect.bottom = 205;
	memDC.DrawText( "Registers", &rect, DT_CENTER | DT_VCENTER );

	memDC.SelectObject( &oldBrush1 );

	CBrush brush2, oldBrush2;
	brush2.CreateSolidBrush( m_bkColor );
	pOldBrush = (CBrush*)memDC.SelectObject( brush2 );
	oldBrush2.FromHandle((HBRUSH)pOldBrush);
	// Sign-extend
	rect.left = 210; rect.right = 250; rect.top = 255; rect.bottom = 305;
	memDC.Ellipse( &rect );
	// text "Sign-extend"
	rect.top = 265; rect.bottom = 290;
	memDC.DrawText( "Sign-\nextend", &rect, DT_CENTER | DT_VCENTER );

	// Zero?
	rect.left = 304; rect.right = 340; rect.top = 100; rect.bottom = 130;
	memDC.Rectangle( &rect );
	// rext "Zero?"
	rect.top = 108;
	memDC.DrawText( "Zero?", &rect, DT_CENTER | DT_VCENTER );

	// ADD
	CPoint poly[8];
	poly[0] = CPoint( 270, 80 ); poly[1] = CPoint( 270, 100 );
	poly[2] = CPoint( 303, 84 ); poly[3] = CPoint( 303, 56 );
	poly[4] = CPoint( 270, 40 );  poly[5] = CPoint( 270, 60 );
	poly[6] = CPoint( 278, 70 ); poly[7] = CPoint( 270, 80 );
	memDC.Polyline( poly, 8 );
	// text "ADD"
	rect.left = 278; rect.top = 65; rect.right = 300, rect.bottom = 80;
	memDC.DrawText( "ADD", &rect, DT_LEFT | DT_VCENTER );

	IDLines( m_penStyle, m_penWidth, m_penColor );

	memDC.SelectObject( &oldBrush2 );
	memDC.SelectObject( pOldPen );
}

void CIntegerDatapathCtrl::IDLines( int penStyle, int penWidth, COLORREF penColor, CString& str )
{
	m_IDPenStyle = penStyle;
	m_IDPenWidth = penWidth;
	m_IDPenColor = penColor;
	m_IDStr = str;

	l8.Draw( &memDC, penStyle, penWidth, penColor );
	l9.Draw( &memDC, penStyle, penWidth, penColor );
	l10.Draw( &memDC, penStyle, penWidth, penColor );
	l11.Draw( &memDC, penStyle, penWidth, penColor );
	l12.Draw( &memDC, penStyle, penWidth, penColor );
	l13.Draw( &memDC, penStyle, penWidth, penColor );
	l14.Draw( &memDC, penStyle, penWidth, penColor );
	l15.Draw( &memDC, penStyle, penWidth, penColor );
	l16.Draw( &memDC, penStyle, penWidth, penColor );
	l17.Draw( &memDC, penStyle, penWidth, penColor );
	l18.Draw( &memDC, penStyle, penWidth, penColor );
	l19.Draw( &memDC, penStyle, penWidth, penColor );

	// show current instructions
	CRect rect( 165, 0, 350, 20 );
	COLORREF clr = memDC.SetTextColor( penColor );
	memDC.DrawText( str, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK );
	memDC.SetTextColor( clr );
}

void CIntegerDatapathCtrl::RestoreIDLines( BOOL bCore )
{
	IDLines( m_IDPenStyle, m_IDPenWidth, m_bkColor, m_IDStr );
	m_IDStr = _T("");
	if( bCore ) IDLines( m_penStyle, m_penWidth, m_penColor );
}

// ID/EX
void CIntegerDatapathCtrl::IDEXRegs()
{
	CPen pen;
	pen.CreatePen( m_penStyle, m_penWidth, m_penColor );
	CPen* pOldPen = (CPen*)memDC.SelectObject( &pen );

	CBrush brush, oldBrush;
	brush.CreateSolidBrush( m_regColor );
	CBrush* pOldBrush = (CBrush*)memDC.SelectObject( brush );
	oldBrush.FromHandle((HBRUSH)pOldBrush);

	CRect rect( 350, 60, 371, 320 );
	memDC.Rectangle( &rect );
	// text "ID/EX"
	rect.left = 348; rect.right = 380; rect.top = 45; rect.bottom = 60;
	memDC.DrawText( "ID/EX", &rect, DT_LEFT | DT_VCENTER );

	memDC.SelectObject( &oldBrush );
	memDC.SelectObject( pOldPen );
}

// EX
void CIntegerDatapathCtrl::EXCircuits()
{
	CPen pen;
	pen.CreatePen( m_penStyle, m_penWidth, m_penColor );
	CPen* pOldPen = (CPen*)memDC.SelectObject( &pen );

	CBrush brush, oldBrush;
	brush.CreateSolidBrush( m_bkColor );
	CBrush* pOldBrush = (CBrush*)memDC.SelectObject( brush );
	oldBrush.FromHandle((HBRUSH)pOldBrush);

	CRect rect;

	// Mux
	rect.left = 400; rect.right = 417; rect.top = 205; rect.bottom = 245;
	memDC.RoundRect( &rect, CPoint(17, 17) );
	// text "Mux"
	memDC.DrawText( "M\nu\nx", &rect, DT_CENTER | DT_VCENTER );

	// ALU
	CPoint poly[8];
	poly[0] = CPoint( 430, 212 ); poly[1] = CPoint( 430, 238 );
	poly[2] = CPoint( 470, 215 ); poly[3] = CPoint( 470, 183 );
	poly[4] = CPoint( 430, 160 );  poly[5] = CPoint( 430, 186 );
	poly[6] = CPoint( 440, 199 ); poly[7] = CPoint( 430, 212 );
	memDC.Polyline( poly, 8 );
	// text "ADD"
	rect.left = 440; rect.top = 193; rect.right = 470, rect.bottom = 205;
	memDC.DrawText( "ALU", &rect, DT_CENTER | DT_VCENTER );

	EXLines( m_penStyle, m_penWidth, m_penColor );

	memDC.SelectObject( &oldBrush );
	memDC.SelectObject( pOldPen );
}

void CIntegerDatapathCtrl::EXLines( int penStyle, int penWidth, COLORREF penColor, CString& str )
{
	m_EXPenStyle = penStyle;
	m_EXPenWidth = penWidth;
	m_EXPenColor = penColor;
	m_EXStr = str;

	l20.Draw( &memDC, penStyle, penWidth, penColor );
	l21.Draw( &memDC, penStyle, penWidth, penColor );
	l22.Draw( &memDC, penStyle, penWidth, penColor );
	l23.Draw( &memDC, penStyle, penWidth, penColor );
	l24.Draw( &memDC, penStyle, penWidth, penColor );
	l25.Draw( &memDC, penStyle, penWidth, penColor );
	l26.Draw( &memDC, penStyle, penWidth, penColor );

	// show current instructions
	CRect rect( 350, 0, 480, 20 );
	COLORREF clr = memDC.SetTextColor( penColor );
	memDC.DrawText( str, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK );
	memDC.SetTextColor( clr );
}

void CIntegerDatapathCtrl::RestoreEXLines( BOOL bCore )
{
	EXLines( m_EXPenStyle, m_EXPenWidth, m_bkColor, m_EXStr );
	m_EXStr = _T("");
	if( bCore ) EXLines( m_penStyle, m_penWidth, m_penColor );
}

// EX/MEM]
void CIntegerDatapathCtrl::EXMEMRegs()
{
	CPen pen;
	pen.CreatePen( m_penStyle, m_penWidth, m_penColor );
	CPen* pOldPen = (CPen*)memDC.SelectObject( &pen );

	CBrush brush, oldBrush;
	brush.CreateSolidBrush( m_regColor );
	CBrush* pOldBrush = (CBrush*)memDC.SelectObject( brush );
	oldBrush.FromHandle((HBRUSH)pOldBrush);

	CRect rect( 480, 80, 501, 320 );
	memDC.Rectangle( &rect );
	// text "EX/MEM"
	rect.left = 460; rect.right = 521; rect.top = 65; rect.bottom = 80;
	memDC.DrawText( "EX/MEM", &rect, DT_CENTER | DT_VCENTER );

	memDC.SelectObject( &oldBrush );
	memDC.SelectObject( pOldPen );
}

// MEM
void CIntegerDatapathCtrl::MEMCircuits()
{
	CPen pen;
	pen.CreatePen( m_penStyle, m_penWidth, m_penColor );
	CPen* pOldPen = (CPen*)memDC.SelectObject( &pen );

	CBrush brush, oldBrush;
	brush.CreateSolidBrush( RGB(197, 197, 243) );
	CBrush* pOldBrush = (CBrush*)memDC.SelectObject( brush );
	oldBrush.FromHandle((HBRUSH)pOldBrush);

	// Data Memory
	CRect rect( 540, 190, 590, 260 );
	memDC.Rectangle( &rect );
	// text "Data memory"
	rect.top = 210;
	memDC.DrawText( "Data\nmemory", &rect, DT_CENTER | DT_VCENTER );

	MEMLines( PS_SOLID, 1, m_penColor );

	memDC.SelectObject( &oldBrush );
	memDC.SelectObject( pOldPen );
}

void CIntegerDatapathCtrl::MEMLines( int penStyle, int penWidth, COLORREF penColor, CString& str )
{
	m_MEMPenStyle = penStyle;
	m_MEMPenWidth = penWidth;
	m_MEMPenColor = penColor;
	m_MEMStr = str;

	l27.Draw( &memDC, penStyle, penWidth, penColor );
	l28.Draw( &memDC, penStyle, penWidth, penColor );
	l29.Draw( &memDC, penStyle, penWidth, penColor );
	l30.Draw( &memDC, penStyle, penWidth, penColor );
	l31.Draw( &memDC, penStyle, penWidth, penColor );

	// show current instructions
	CRect rect( 480, 0, 605, 20 );
	COLORREF clr = memDC.SetTextColor( penColor );
	memDC.DrawText( str, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK );
	memDC.SetTextColor( clr );
}

void CIntegerDatapathCtrl::RestoreMEMLines( BOOL bCore )
{
	MEMLines( m_MEMPenStyle, m_MEMPenWidth, m_bkColor, m_MEMStr );
	m_MEMStr = _T("");
	if( bCore ) MEMLines( m_penStyle, m_penWidth, m_penColor );
}

// MEM/WB
void CIntegerDatapathCtrl::MEMWBRegs()
{
	CPen pen;
	pen.CreatePen( m_penStyle, m_penWidth, m_penColor );
	CPen* pOldPen = (CPen*)memDC.SelectObject( &pen );

	CBrush brush, oldBrush;
	brush.CreateSolidBrush( m_regColor );
	CBrush* pOldBrush = (CBrush*)memDC.SelectObject( brush );
	oldBrush.FromHandle((HBRUSH)pOldBrush);

	CRect rect( 605, 80, 626, 320 );
	memDC.Rectangle( &rect );
	// text "MEM/WB"
	rect.left = 590; rect.right = 640; rect.top = 65; rect.bottom = 80;
	memDC.DrawText( "MEM/WB", &rect, DT_CENTER | DT_VCENTER );

	memDC.SelectObject( &oldBrush );
	memDC.SelectObject( pOldPen );
}

// WB
void CIntegerDatapathCtrl::WBCircuits()
{
	CPen pen;
	pen.CreatePen( m_penStyle, m_penWidth, m_penColor );
	CPen* pOldPen = (CPen*)memDC.SelectObject( &pen );

	CBrush brush, oldBrush;
	brush.CreateSolidBrush( m_bkColor );
	CBrush* pOldBrush = (CBrush*)memDC.SelectObject( brush );
	oldBrush.FromHandle((HBRUSH)pOldBrush);

	// Mux
	CRect rect( 650, 215, 668, 255 );
	memDC.RoundRect( &rect, CPoint(17, 17) );
	// text "Mux"
	memDC.DrawText( "M\nu\nx", &rect, DT_CENTER | DT_VCENTER );

	WBLines( m_penStyle, m_penWidth, m_penColor );

	memDC.SelectObject( &oldBrush );
	memDC.SelectObject( pOldPen );
}

void CIntegerDatapathCtrl::WBLines( int penStyle, int penWidth, COLORREF penColor, CString& str )
{
	m_WBPenStyle = penStyle;
	m_WBPenWidth = penWidth;
	m_WBPenColor = penColor;
	m_WBStr = str;

	l32.Draw( &memDC, penStyle, penWidth, penColor );
	l33.Draw( &memDC, penStyle, penWidth, penColor );
	l34.Draw( &memDC, penStyle, penWidth, penColor );
	l35.Draw( &memDC, penStyle, penWidth, penColor );

	// show current instructions
	CRect rect( 605, 0, 720, 20 );
	COLORREF clr = memDC.SetTextColor( penColor );
	memDC.DrawText( str, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK );
	memDC.SetTextColor( clr );
}

void CIntegerDatapathCtrl::RestoreWBLines( BOOL bCore )
{
	WBLines( m_WBPenStyle, m_WBPenWidth, m_bkColor, m_WBStr );
	m_WBStr = _T("");
	if( bCore ) WBLines( m_penStyle, m_penWidth, m_penColor );
}


void CIntegerDatapathCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	memDC.LPtoDP( &point );

	// Registers rectangle
	do {
		CRect rect1( 232, 146, 284, 250 );
		if( rect1.PtInRect( point ) ) {
			CRegDlg dlg;
			dlg.m_bEditable = FALSE;
			dlg.DoModal();
			break;
		}

		CRect rect2( 540, 190, 590, 260 );
		if( rect2.PtInRect( point ) ) {
			CMemDlg dlg;
			dlg.m_bEditable = FALSE;
			dlg.DoModal();
			break;
		}
	} while( 0 );
	
	CWnd::OnLButtonDown(nFlags, point);
}
