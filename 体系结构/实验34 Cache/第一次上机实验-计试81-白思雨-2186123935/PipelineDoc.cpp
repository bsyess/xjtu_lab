// PipelineDoc.cpp : implementation of the CPipelineDoc class
//

#include "stdafx.h"
#include "Pipeline.h"

#include "PipelineDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPipelineDoc

IMPLEMENT_DYNCREATE(CPipelineDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CPipelineDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CPipelineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPipelineDoc construction/destruction

CPipelineDoc::CPipelineDoc()
{
	// TODO: add one-time construction code here

}

CPipelineDoc::~CPipelineDoc()
{
}

BOOL CPipelineDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	SetTitle( _T("") );

	return TRUE;
}

CRichEditCntrItem* CPipelineDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CPipelineCntrItem(preo, (CPipelineDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CPipelineDoc serialization

void CPipelineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CPipelineDoc diagnostics

#ifdef _DEBUG
void CPipelineDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CPipelineDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPipelineDoc commands

void CPipelineDoc::OnCloseDocument() 
{	
	CRichEditDoc::OnCloseDocument();
}
