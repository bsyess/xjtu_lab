#if !defined(AFX_LEXANALYZER_H__AB6A94C5_5F1E_402E_B185_BECAEE10706F__INCLUDED_)
#define AFX_LEXANALYZER_H__AB6A94C5_5F1E_402E_B185_BECAEE10706F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LexAnalyzer.h : header file
//

#include <afxtempl.h>
#include "Tokenizer.h"

#define MAX_KW			100
#define MAX_REGISTER	32

enum ASMKey
{
	LW, SW,
	ADD, SUB, MUT, MUL, DIV,
	AND, OR, XOR,
	ADDI, SUBI, MUTI, MULI, DIVI,
	ANDI, ORI, XORI,
	BEQZ, BNEZ, J, JR, TRAP, NOP,
	COLON, SEPARATOR, SHARP, LEFT_PAR, RIGHT_PAR,
	REGISTER, IDLE_INST, USER, DIGIT, STRING, _EOF
};

struct Lex
{
	ASMKey	key;
	CString	str;
};

class CLexAnalyzer : public CTokenizer
{
public:
	CLexAnalyzer( CString& str );
	virtual ~CLexAnalyzer();

	void	MapKeyword(void);
	void	PushBack();
	Lex&	NextToken();

public:
	// Help routines
	UINT GetRegNum();
	int GetDigit();
	CString GetString();
	BOOL SkipKey( ASMKey key = SEPARATOR );

private:
	BOOL	IsRegister( CString& str );

private:
	BOOL m_bPushedBack;
	struct Lex m_Lex;
	CMap<CString, LPCSTR, ASMKey, ASMKey> m_KeyIndex;
};

#endif // !defined(AFX_LEXANALYZER_H__AB6A94C5_5F1E_402E_B185_BECAEE10706F__INCLUDED_)
