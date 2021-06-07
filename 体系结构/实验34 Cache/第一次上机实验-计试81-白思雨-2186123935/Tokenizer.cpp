// Tokenizer.cpp : implementation file
//

#include "stdafx.h"

#include "Tokenizer.h"
#include "Error.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTokenizer

CTokenizer::CTokenizer(CString &string)
{
	m_bPushedBack = FALSE;
	m_bEolIsSignificant = TRUE;
	m_bSlSlComments = TRUE;
	m_bSlStComments = TRUE;
	m_bSharpComments = FALSE;
	m_bSemicolonComments = TRUE;
	m_bForceLower = TRUE;
	m_iLineNo = 1;			// the first line
	m_iChar = 0;
	m_peekc = ' ';
	m_sString = string;
	m_sString += -1;
}

CTokenizer::~CTokenizer()
{
}

void CTokenizer::PushBack()
{
	m_bPushedBack = TRUE;
}

// Specifies that EOL is significant or not
void CTokenizer::EolIsSignificant(BOOL bFlag)
{
	m_bEolIsSignificant = bFlag;
}

// Enable C Style comments
void CTokenizer::SlStComments(BOOL bFlag)
{
	m_bSlStComments = bFlag;
}

void CTokenizer::SharpComments(BOOL bFlag)
{
	m_bSharpComments = bFlag;
}

void CTokenizer::SemicolonComments(BOOL bFlag)
{
	m_bSemicolonComments = bFlag;
}

// Enable C++ Style comments
void CTokenizer::SlSlComments(BOOL bFlag)
{
	m_bSlSlComments = bFlag;
}

// Enable / disable case sensitivity
void CTokenizer::LowerCaseMode(BOOL bFlag)
{
	m_bForceLower = bFlag;
}

// gives the next Token, returns the token type
int CTokenizer::NextToken()
{
	if ( m_bPushedBack )
	{
		m_bPushedBack = FALSE;
		return m_tType;
	}
	int c = m_peekc;
	m_sVal = _T("");
	
	if ( c == EOF )
		return m_tType = TT_EOF;
	
	// is this a space 
	while ( ::isspace( c ) ) {
		if (c == '\r') {
			m_iLineNo++;
			c = GetChar();
			if ( c == '\n' )
				c = GetChar();
			if ( m_bEolIsSignificant ) {
				m_peekc = c;
				return m_tType = TT_EOL;
			}
		} else {
			if ( c == '\n' ) {
				m_iLineNo++;
				if ( m_bEolIsSignificant ) {
					m_peekc = ' ';
					return m_tType = TT_EOL;
				}
			}
			c = GetChar();
		}

		if ( c == EOF )
			return m_tType = TT_EOF;
	}
	
	// is this a number
	if ( ::isdigit( c ) || c == '.' || c == '-' ) {
		BOOL neg = FALSE;
		if ( c == '-' )	{
			c = GetChar();
			if ( c != '.' && !::isdigit( c ) ) {
				m_peekc = c;
				return  m_tType = '-';
			}
			neg = TRUE;
		}
		double v = 0;
		int decexp = 0;
		int seendot = 0;
		while (true) {
			if (c == '.' && seendot == 0)
				seendot = 1;
			else if ( ::isdigit( c ) ) {
				v = v* 10 + (c - '0');
				decexp += seendot;
			} else
				break;
			c = GetChar();
		}
		m_peekc = c;
		if ( decexp != 0 ) {
			double denom = 10;
			decexp--;
			while ( decexp > 0 ) {
				denom *= 10;
				decexp --;
			}
			v = v/denom;
		} else if (seendot == 1) {
			m_iChar --;
			m_peekc = '.';
			seendot = 0;
		}
		m_dVal = neg ? -v : v;
		if (seendot==0)
			return m_tType = TT_INTEGER;
		else
			return m_tType = TT_REAL;
	}
	
	// is this a word
	if ( ::isalpha( c ) || c == '_' ) {
		int i = 0;
		m_sVal = _T("");
		do {
			m_sVal = m_sVal + (TCHAR) c;
			c = GetChar();			
		} while ( ::isalnum( c ) || c == '_' );
		m_peekc = c;
		if ( m_bForceLower )
			m_sVal.MakeLower ();
		return m_tType = TT_WORD;
	}

	// now the string
	if ( c == '\'' ) {
		m_sVal = _T("");
		m_tType = TT_STRING;
		m_peekc = ' ';
		int i = 0;
		while ( (c = GetChar()) != EOF && c != '\'' )
			m_sVal = m_sVal + (TCHAR) c;
		if( c != '\'' )
			throw Error( ERROR_ASM_STRING, m_iLineNo );
		return m_tType;
	}

	// and now the comment
	// "//" or "/*...*/"
	if ( c == '/' && ( m_bSlSlComments || m_bSlStComments ) ) {
		c = GetChar();
		if ( c == '*' && m_bSlStComments ) {
			int prevc = 0;
			while ( (c = GetChar()) != '/' || prevc != '*' ) {
				if ( c == '\n' )
					m_iLineNo++;
				if ( c == EOF )
					return m_tType = TT_EOF;
				prevc = c;
			}
			m_peekc = ' ';
			return NextToken();
		} else {
			if (c == '/' && m_bSlSlComments) {
				while ( (c = GetChar()) != '\n' && c != '\r' );
				m_peekc = c;
				return NextToken();
			} else {
				m_peekc = c;
				return m_tType = '/';
			}
		}
	}
	// '#' or ';' comments
	if( ((c == '#') && m_bSharpComments) ||
		((c == ';') && m_bSemicolonComments) ) {
		while ( (c = GetChar()) != '\n' && c != '\r' );
		m_peekc = c;
		return NextToken();
	}

	m_peekc = ' ';
	return m_tType = c;
}

int CTokenizer::LineNo()
{
	return m_iLineNo;
}

CString CTokenizer::GetStrValue()
{
	CString ret;
	switch (m_tType)
	{
	case TT_EOF:
		ret = "EOF";
		break;
	case TT_EOL:
		ret = "EOL";
		break;
	case TT_WORD:
		ret = m_sVal;
		break;
	case TT_STRING:
		ret = m_sVal;
		break;
	case TT_INTEGER:
	case TT_REAL:
		ret.Format("%g",m_dVal);
		break;
	default:
		ret.Format ( "\'%c\'",(char) m_tType) ;
	}
	return ret;
}

double CTokenizer::GetNumValue()
{
	return m_dVal;
}
