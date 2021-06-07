#if !defined(AFX_EXECINSTCTRL_H__EF7DE60E_53D7_43EF_8546_6158313058E2__INCLUDED_)
#define AFX_EXECINSTCTRL_H__EF7DE60E_53D7_43EF_8546_6158313058E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExecInstCtrl.h : header file
//

#include <afxtempl.h>
#include "MIPSSimulator.h"

/////////////////////////////////////////////////////////////////////////////
// CExecInstCtrl window

class CExecInstCtrl : public CWnd
{
// Construction
public:
	CExecInstCtrl();
	virtual ~CExecInstCtrl();

// Attributes
public:
	CWnd*		m_pParentWnd;

	CDC			memDC;
	CFont*		m_pOldFont;
	CBitmap*	m_pOldBitmap;
	CBitmap*	m_pBitmap;

	CRect		rcClient;
	CSize		image_size;
	int			scrollbar_width;
	int			x_offset;
	int			y_offset;

	COLORREF	m_BkColor;
	COLORREF	defaultTextBkColor;
	COLORREF	defaultTextFgColor;

	typedef struct {
		COLORREF m_TextBkColor;
		COLORREF m_TextFgColor;
		int		 row;
		int      col;
		CString  szText;
	} ITEM;
	typedef struct {
		CList<ITEM, ITEM&> m_itemList;
		int			m_nAddress;
		UINT		m_nStartCycle;
	} ITEM_ROW;
	CList<ITEM_ROW*, ITEM_ROW*> m_rowList;

	UINT	m_nMaxRow;
	UINT	m_nMaxCol;
	UINT	m_nStartCycle;
	UINT	m_nCurCycle;
	UINT_ARRAY addressArray;// store addresses of completed instructions
	BOOL    m_bInstComplete;
	BOOL	m_bIdleInstComplete;

	UINT	m_nFixRowHeight;
	UINT	m_nRowHeight;
	UINT	m_nFixColWidth;
	UINT	m_nColWidth;

	enum {
		kNone, kRun, kComplete
	} m_nState;

// Operations
public:
	void NextCycle( BOOL bRedraw = TRUE );

	void Reset();
	void ResetAndUpdate();

	BOOL SetBackColor(COLORREF color);
	BOOL SetFont(CFont* pFont, BOOL bRedraw = TRUE);

	void AddExecInst( int address, COLORREF textColor,
		CString& instString, int StartCycle, UINT_ARRAY& StageArray );
	void RemoveExecInst( int address );

	void AdjustFixRow();
	void AdjustClientArea();

	BOOL GetItem( int row, int col, ITEM& outItem );

	void DrawItem( int row, int col, BOOL TextOnly = TRUE, BOOL invalid = TRUE );
	void DrawRow( int row, BOOL TextOnly = TRUE, BOOL invalid = TRUE );
	void DrawCol( int col, BOOL TextOnly = TRUE, BOOL invalid = TRUE );
	void DrawAll( BOOL invalid = TRUE );
	void ShadeCol();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExecInstCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CExecInstCtrl)
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXECINSTCTRL_H__EF7DE60E_53D7_43EF_8546_6158313058E2__INCLUDED_)
