// Pipeline.cpp : Defines the class behaviors for the application.
// Download by http://down.liehuo.net

#include "stdafx.h"
#include "Pipeline.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "PipelineDoc.h"
#include "PipelineView.h"

#include "AsmEditDoc.h"
#include "AsmEditFrame.h"
#include "AsmEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPipelineApp

BEGIN_MESSAGE_MAP(CPipelineApp, CWinApp)
	//{{AFX_MSG_MAP(CPipelineApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPipelineApp construction

CPipelineApp::CPipelineApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPipelineApp object

CPipelineApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPipelineApp initialization

BOOL CPipelineApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("MIPS Pipeline Simulator"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	// serve as the connection between documents, frame windows and views.
	
	// for console
	m_pConsoleDocTemplate = new CMultiDocTemplate(
		IDR_PIPELITYPE,
		RUNTIME_CLASS(CPipelineDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CPipelineView));
	m_pConsoleDocTemplate->SetContainerInfo(IDR_PIPELITYPE_CNTR_IP);
	AddDocTemplate(m_pConsoleDocTemplate);

	// for MIPS asm editor
	m_pAsmEditDocTemplate = new CMultiDocTemplate(
		IDR_ASMTYPE,
		RUNTIME_CLASS(CAsmEditDoc),
		RUNTIME_CLASS(CAsmEditFrame),
		RUNTIME_CLASS(CAsmEditView));
	AddDocTemplate(m_pAsmEditDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// Create MIPS Simulator dialog
	m_pSimulatorDlg = new CSimulatorDlg();
	m_pSimulatorDlg->Create(IDD_SIM_DLG);
	m_pSimulatorDlg->ShowWindow(SW_SHOW);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPipelineApp message handlers

void CPipelineApp::CreateEditView()
{
	ASSERT(m_pAsmEditDocTemplate);

	CDocument* pDoc = NULL;
	CFrameWnd* pFrame = NULL;

	pDoc = m_pAsmEditDocTemplate->CreateNewDocument();
	if( pDoc ) {
		pFrame = (CFrameWnd*)m_pAsmEditDocTemplate->CreateNewFrame(pDoc, NULL);
		if( pFrame )	{
			m_pAsmEditDocTemplate->SetDefaultTitle(pDoc);
			if( !pDoc->OnNewDocument() ) {
				pFrame->DestroyWindow();
				pFrame = NULL;
			} else
				m_pAsmEditDocTemplate->InitialUpdateFrame(pFrame, pDoc, TRUE);
		} else
			delete pDoc;
	}

	if (pFrame == NULL || pDoc == NULL)
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
}

void CPipelineApp::OnFileNew() 
{
	m_pConsoleDocTemplate->OpenDocumentFile(NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include "hyperlink.h"
#include "XPButton.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CXPButton	m_btnOK;
	CHyperLink	m_sLu;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_STATIC_LUXIAOCHUN, m_sLu);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_sLu.SetURL( _T("mailto:bsyess@bsyess.top") );
	
	return TRUE;
}

// App command to run the dialog
void CPipelineApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
