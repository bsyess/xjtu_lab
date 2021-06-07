// LexAnalyzer.cpp : implementation file
//

#include "stdafx.h"

#include "LexAnalyzer.h"
#include "Error.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString ASMKeyList[] =
{
	"lw", "sw", 
	"add", "sub", "mut", "mul", "div",
	"and", "or", "xor", 
	"addi", "subi", "muti", "muli", "divi",
	"andi", "ori", "xori",
	"beqz", "bnez", "j", "jr", "trap", "nop", 
	":", ",", "#", "(", ")"
};

/////////////////////////////////////////////////////////////////////////////
// CLexAnalyzer

CLexAnalyzer::CLexAnalyzer( CString& str ) :
	CTokenizer( str )
{
	m_bPushedBack = FALSE;

	MapKeyword();
}

CLexAnalyzer::~CLexAnalyzer()
{
}

void CLexAnalyzer::MapKeyword()
{
	m_KeyIndex.RemoveAll();
	m_KeyIndex.InitHashTable( MAX_KW );

	for( int i = 0; i < sizeof( ASMKeyList ) / sizeof( *ASMKeyList ); i++ )
		m_KeyIndex[ ASMKeyList[i] ] = (ASMKey) i;
}

Lex& CLexAnalyzer::NextToken()
{
	if (m_bPushedBack)
	{
		m_bPushedBack = FALSE;
		return m_Lex;
	}

	ASMKey key;
	int val = CTokenizer::NextToken();
	
	if( val == TT_EOF )
	{
		m_Lex.key = _EOF;
		m_Lex.str = "EOF";
		return m_Lex;
	}

	if( val == TT_WORD ) {
		if( m_KeyIndex.Lookup( m_sVal, key ) )
			m_Lex.key = key;
		else if( IsRegister(m_sVal) )
			m_Lex.key = REGISTER;
		else 
			m_Lex.key = USER;
		m_Lex.str = m_sVal;
	} else if( val == TT_INTEGER || val == TT_REAL ) {
		m_Lex.key = DIGIT;
		m_Lex.str = GetStrValue();
	} else if( ::strchr( ":,#()", val ) ) {
		m_Lex.str = (TCHAR)val;
		m_Lex.key = m_KeyIndex[ m_Lex.str ];
	} else if( val == TT_STRING ) {
		m_Lex.key = STRING;
		m_Lex.str = m_sVal;
	} else if( val == TT_EOL )
		return NextToken();
	else
		throw Error( ERROR_ASM_INPUT, LineNo() );

	return m_Lex;
}

void CLexAnalyzer::PushBack()
{
	m_bPushedBack = TRUE;
}

BOOL CLexAnalyzer::IsRegister( CString& str )
{
	int num;
	if( ::sscanf((LPCTSTR)str, "r%d", &num) == 1 )
		if( (num >= 0 && num < 10 && str.GetLength() == 2) ||
			(num >= 10 && num < MAX_REGISTER && str.GetLength() == 3) ) {
			m_dVal = (double)num;
			return TRUE;
		}
	return FALSE;
}

UINT CLexAnalyzer::GetRegNum()
{
	Lex lex = NextToken();
	if( lex.key != REGISTER )
		throw Error( ERROR_ASM_INPUT, LineNo() );
	return (UINT)m_dVal;
}

int CLexAnalyzer::GetDigit()
{
	Lex lex = NextToken();
	if( lex.key == SHARP )
		lex = NextToken();
	if( lex.key != DIGIT )
		throw Error( ERROR_ASM_INPUT, LineNo() );
	return (int)m_dVal;
}

CString CLexAnalyzer::GetString()
{
	Lex lex = NextToken();
	if( lex.key != USER )
		throw Error( ERROR_ASM_INPUT, LineNo() );
	return lex.str;
}

BOOL CLexAnalyzer::SkipKey( ASMKey key )
{
	Lex lex = NextToken();
	if( lex.key != key )
		throw Error( ERROR_ASM_INPUT, LineNo() );
	return TRUE;
}
