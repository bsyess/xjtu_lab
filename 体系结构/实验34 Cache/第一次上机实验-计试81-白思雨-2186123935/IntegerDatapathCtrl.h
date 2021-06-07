#if !defined(AFX_INTEGERDATAPATHCTRL_H__F788873B_4AC0_4162_ADB2_D5EE81027DEC__INCLUDED_)
#define AFX_INTEGERDATAPATHCTRL_H__F788873B_4AC0_4162_ADB2_D5EE81027DEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IntegerDatapathCtrl.h : header file
//

#include "line.h"

/////////////////////////////////////////////////////////////////////////////
// CIntegerDatapathCtrl window

class CIntegerDatapathCtrl : public CWnd
{
// Construction
public:
	CIntegerDatapathCtrl();
	virtual ~CIntegerDatapathCtrl();

// Attributes
public:
	CWnd*		m_pParentWnd;

	CDC			memDC;
	CFont*		m_pOldFont;
	CBitmap*	m_pOldBitmap;
	CBitmap*	m_pBitmap;
	CRect		rcClient;

	int			m_penStyle;
	int			m_penWidth;
	COLORREF	m_penColor;
	COLORREF	m_regColor;
	COLORREF	m_bkColor;

	int			m_IFPenStyle;
	int			m_IFPenWidth;
	COLORREF	m_IFPenColor;
	CString		m_IFStr;

	int			m_IDPenStyle;
	int			m_IDPenWidth;
	COLORREF	m_IDPenColor;
	CString		m_IDStr;

	int			m_EXPenStyle;
	int			m_EXPenWidth;
	COLORREF	m_EXPenColor;
	CString		m_EXStr;

	int			m_MEMPenStyle;
	int			m_MEMPenWidth;
	COLORREF	m_MEMPenColor;
	CString		m_MEMStr;

	int			m_WBPenStyle;
	int			m_WBPenWidth;
	COLORREF	m_WBPenColor;
	CString		m_WBStr;

	// IF lines
	CLine l1, l2, l3, l4, l5, l6, l7;
	// ID lines
	CLine l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, l19;
	// EX lines
	CLine l20, l21, l22, l23, l24, l25, l26;
	// MEM lines
	CLine l27, l28, l29, l30, l31;
	// WB lines
	CLine l32, l33, l34, l35;

// Operations
public:
	void SetPenStyle( int style ) { m_penStyle = style; }
	void SetPenWidth( int width ) { m_penWidth = width; }
	void SetPenColor( COLORREF color ) { m_penColor = color; }
	void SetRegColor( COLORREF color ) { m_regColor = color; }
	void SetBkColor( COLORREF color ) { m_bkColor = color; }

	void Reset();
	void NextCycle( BOOL bRedraw = TRUE );

private:
	void InitLines();
	void DrawAll();

	void IFCircuits();
	void IFLines( int penStyle = PS_SOLID, int penWidth = 1,
		COLORREF penColor = RGB(0,0,0), CString& str = CString("") );
	void RestoreIFLines( BOOL bCore = TRUE );

	void IFIDRegs();

	void IDCircuits();
	void IDLines( int penStyle = PS_SOLID, int penWidth = 1,
		COLORREF penColor = RGB(0,0,0), CString& str = CString("") );
	void RestoreIDLines( BOOL bCore = TRUE );
	
	void IDEXRegs();

	void EXCircuits();
	void EXLines( int penStyle = PS_SOLID, int penWidth = 1,
		COLORREF penColor = RGB(0,0,0), CString& str = CString("") );
	void RestoreEXLines( BOOL bCore = TRUE );

	void EXMEMRegs();
	
	void MEMCircuits();
	void MEMLines( int penStyle = PS_SOLID, int penWidth = 1,
		COLORREF penColor = RGB(0,0,0), CString& str = CString("") );
	void RestoreMEMLines( BOOL bCore = TRUE );

	void MEMWBRegs();

	void WBCircuits();
	void WBLines( int penStyle = PS_SOLID, int penWidth = 1,
		COLORREF penColor = RGB(0,0,0), CString& str = CString("") );
	void RestoreWBLines( BOOL bCore = TRUE );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntegerDatapathCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd);
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CIntegerDatapathCtrl)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTEGERDATAPATHCTRL_H__F788873B_4AC0_4162_ADB2_D5EE81027DEC__INCLUDED_)
