#if !defined(AFX_TEXTCTRL_H__47EB830F_1FEC_46EF_A647_BEDFAEFBDA64__INCLUDED_)
#define AFX_TEXTCTRL_H__47EB830F_1FEC_46EF_A647_BEDFAEFBDA64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextCtrl.h : header file
//

#include <afxtempl.h>

class CTextCtrl : public CWnd
{
// Construction
public:
	CTextCtrl();
	virtual ~CTextCtrl();

// Operations
public:
	void Reset();
	void ResetAndUpdate();

	BOOL SetBackColor(COLORREF color);
	BOOL SetFont(CFont* pFont, BOOL bRedraw = TRUE);

	void AddItem(CString& str);

	BOOL SetItemText(int col, CString& str);
	BOOL SetItemBkColor(int col, COLORREF color);
	BOOL SetItemFgColor(int col, COLORREF color);

	void DrawItem( int col, BOOL bRedraw = TRUE );
	void DrawAll(BOOL bRedraw = TRUE);
	void UpdateAll(BOOL bRedraw = TRUE);

	void FocusItem(int index, COLORREF bkColor = RGB(0,0,0),
		COLORREF fgColor = RGB(255,255,255) );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd);
	//}}AFX_VIRTUAL

protected:
	void SetClientRect();
	BOOL CalcItemRect(int col, CRect& outItemRect, CRect& outTextRect);
	BOOL IsItemVisiable(int index);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextCtrl)
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes
private:
	CWnd*		m_pParentWnd;

	CDC			memDC;
	CFont*		m_pOldFont;
	CBitmap*	m_pOldBitmap;
	CBitmap*	m_pBitmap;

	CRect		rcClient;
	CSize		image_size;
	int			m_nMargin;
	int			scrollbar_width;
	int			x_offset;
	int			y_offset;

	COLORREF	m_BkColor;
	COLORREF	defaultTextBkColor;
	COLORREF	defaultTextFgColor;

	typedef struct {
		CString	 m_strContent;
		CSize	 m_TextSize;
		COLORREF m_TextBkColor;
		COLORREF m_TextFgColor;
	} ITEM;
	CList<ITEM, ITEM&> m_itemList;

	int			m_nTopItemIndex;
	int			m_nLastFocusedItemIndex;
	ITEM		m_LastFocusedItem;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTCTRL_H__47EB830F_1FEC_46EF_A647_BEDFAEFBDA64__INCLUDED_)
