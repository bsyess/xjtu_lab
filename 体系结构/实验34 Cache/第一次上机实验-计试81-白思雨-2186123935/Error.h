#if !defined(AFX_ERROR_H__6A381C9B_C266_4DED_90BF_8296A513E8BF__INCLUDED_)
#define AFX_ERROR_H__6A381C9B_C266_4DED_90BF_8296A513E8BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum
{
	ERROR_ASM_LABEL,
	ERROR_ASM_STRING,
	ERROR_ASM_INPUT,
	ERROR_ASM_INST,
	ERROR_ASM_IMM,
	ERROR_ASM_TARGET,

	ERROR_MIPS_REG_OUTRANGE,
	ERROR_MIPS_MEM_OUTRANGE
};

class Error
{
public:
	Error( int id, int param = 0, const CString& comment = _T("") ) :
	  m_id( id ), m_param( param ), m_strComment( comment ) {}
	  ~Error(){}

// Attributes
public:
	int m_id;
	int m_param;
	CString m_strComment;

// Operations
public:
	CString GetStrError();
};

#endif // !defined(AFX_ERROR_H__6A381C9B_C266_4DED_90BF_8296A513E8BF__INCLUDED_)
