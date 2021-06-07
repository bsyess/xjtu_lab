// AsmEditDoc.cpp : implementation file
// Download by http://down.liehuo.net

#include "stdafx.h"
#include "pipeline.h"

#include "AsmEditDoc.h"
#include "AsmEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsmEditDoc

IMPLEMENT_DYNCREATE(CAsmEditDoc, CDocument)

CAsmEditDoc::CAsmEditDoc()
{
	memset(&m_lf, 0, sizeof(m_lf));
	m_lf.lfWeight = FW_NORMAL;
	m_lf.lfCharSet = DEFAULT_CHARSET;
	m_lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_lf.lfQuality = DEFAULT_QUALITY;
	m_lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	strcpy(m_lf.lfFaceName, "宋体");

	m_UserMsg = RegisterWindowMessage(ASMEDITMSG);
}

BOOL CAsmEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//((CWnd*)m_viewList.GetHead())->SetWindowText(NULL);
	m_TextBuffer.InitNew();
	SetTitle( "- MIPS ASM Editor" );
	
	return TRUE;
}

CAsmEditDoc::~CAsmEditDoc()
{
}

BEGIN_MESSAGE_MAP(CAsmEditDoc, CDocument)
	//{{AFX_MSG_MAP(CAsmEditDoc)
	ON_COMMAND(ID_ASM_FILE_OPEN, OnAsmFileOpen)
	ON_COMMAND(ID_ASM_FILE_NEW, OnAsmFileNew)
	ON_COMMAND(ID_ASM_FILE_SAVE, OnAsmFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAsmEditDoc diagnostics

#ifdef _DEBUG
void CAsmEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAsmEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAsmEditDoc serialization

void CAsmEditDoc::Serialize(CArchive& ar)
{
	CCrystalEditView* pView = (CCrystalEditView*)m_viewList.GetHead();
	ASSERT_VALID(pView);
	ASSERT_KINDOF(CCrystalEditView, pView);

	if (ar.IsStoring())	
	{
	} 
	else 
	{
	}

	ASSERT_VALID(this);
}

/////////////////////////////////////////////////////////////////////////////
// CAsmEditDoc commands

BOOL CAsmEditDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	return m_TextBuffer.LoadFromFile(lpszPathName);
}

BOOL CAsmEditDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	return m_TextBuffer.SaveToFile(lpszPathName);
}

void CAsmEditDoc::DeleteContents() 
{
	CDocument::DeleteContents();
	m_TextBuffer.FreeAll();
}

void CAsmEditDoc::OnCloseDocument() 
{
	if( m_TextBuffer.IsModified() ) {
		int ret = AfxMessageBox( "文件已经改变,要保存吗?",
			MB_YESNOCANCEL | MB_ICONQUESTION );
		if( ret == IDCANCEL ) return;
		else if( ret == IDYES )
			this->OnFileSave();
	}
	
	lpszPathName.Empty();
	CPipelineApp* pApp = (CPipelineApp*)AfxGetApp();
	pApp->m_pSimulatorDlg->SendMessage(m_UserMsg, ML_CLOSED, 0);

	CDocument::OnCloseDocument();
}

void CAsmEditDoc::OnAsmFileOpen() 
{
	// Before file is to be open,
	// check if the current document has been modified
	if( m_TextBuffer.IsModified() ) {
		int ret = AfxMessageBox( "文件已经改变,要保存吗?",
			MB_YESNOCANCEL | MB_ICONQUESTION );
		if( ret == IDCANCEL ) return;
		else if( ret == IDYES )
			this->OnFileSave();
	}

	// construct a file box to open files
	BOOL bOpenFileDialog = TRUE;
	CFileDialog *pDlg = new CFileDialog(bOpenFileDialog, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"MIPS汇编文件 (*.mips)|*.mips|所有文件 (*.*)|*.*||");
	pDlg->m_ofn.lpstrTitle = "打开MIPS汇编文件";

	if( (pDlg->DoModal() == IDOK) ){
		lpszPathName = pDlg->GetPathName();
		// delete contents
		m_TextBuffer.FreeAll();
		// load file
		m_TextBuffer.LoadFromFile(lpszPathName);
		// update all views
		UpdateAllViews( NULL );
	}
}

void CAsmEditDoc::OnAsmFileNew() 
{
	// Before creating a new document,
	// check if the current document has been modified
	if( m_TextBuffer.IsModified() ) {
		int ret = AfxMessageBox( "文件已经改变,要保存吗?",
			MB_YESNOCANCEL | MB_ICONQUESTION );
		if( ret == IDCANCEL ) return;
		else if( ret == IDYES )
			this->OnFileSave();
	}

	// delete contents
	m_TextBuffer.FreeAll();
	lpszPathName.Empty();
	// init
	m_TextBuffer.InitNew();
	// update all views
	UpdateAllViews( NULL );
}

void CAsmEditDoc::OnAsmFileSave() 
{
	if( m_TextBuffer.IsModified() )
		if( lpszPathName.IsEmpty() )
			OnFileSave();
		else
			m_TextBuffer.SaveToFile( lpszPathName );
}
