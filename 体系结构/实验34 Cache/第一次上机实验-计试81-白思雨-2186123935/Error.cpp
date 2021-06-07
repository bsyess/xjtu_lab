// Error.cpp : implementation file
// Download by http://down.liehuo.net

#include "stdafx.h"
#include "Error.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString Error::GetStrError()
{
	CString ret = _T("");

	switch( m_id ) {
	case ERROR_ASM_LABEL:
		ret.Format( "Error in label format." );
		break;

	case ERROR_ASM_STRING:
		ret.Format( "Syntax error in line %d. Maybe '\'' is forgot.", 
					m_param );
		break;

	case ERROR_ASM_INPUT:
		ret.Format( "Syntax error in line %d.", m_param );
		break;

	case ERROR_ASM_INST:
		ret.Format( "Systax error in line %d. Unknown op: \"%s\".",
			m_param, m_strComment );
		break;

	case ERROR_ASM_IMM:
		ret.Format( "Syntax error in line %d."
					"Immediate can't be greater than 0xFFFF.", m_param );
		break;

	case ERROR_ASM_TARGET:
		ret.Format( "Syntax error, label \"%s\" undefined.",
					(LPCTSTR)m_strComment );
		break;

	case ERROR_MIPS_REG_OUTRANGE:
		ret.Format( "Register %u is out of range(r0 - r31, total 32).",
			(UINT)m_param );
		break;

	case ERROR_MIPS_MEM_OUTRANGE:
		ret.Format( "Address %u is out of range.", (UINT)m_param );
		break;
	}

	return ret;
}
