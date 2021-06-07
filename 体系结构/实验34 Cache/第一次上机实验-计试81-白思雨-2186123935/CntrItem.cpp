// CntrItem.cpp : implementation of the CPipelineCntrItem class
// Download by http://down.liehuo.net

#include "stdafx.h"
#include "Pipeline.h"

#include "PipelineDoc.h"
#include "PipelineView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPipelineCntrItem implementation

IMPLEMENT_SERIAL(CPipelineCntrItem, CRichEditCntrItem, 0)

CPipelineCntrItem::CPipelineCntrItem(REOBJECT* preo, CPipelineDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CPipelineCntrItem::~CPipelineCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CPipelineCntrItem diagnostics

#ifdef _DEBUG
void CPipelineCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CPipelineCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
