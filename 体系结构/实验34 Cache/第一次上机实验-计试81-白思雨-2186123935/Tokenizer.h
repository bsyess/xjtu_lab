#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tokenizer.h : header file
//

// now should be defined the token types
#define TT_EOF		-1
#define TT_EOL		'\n'
#define TT_INTEGER	-2
#define TT_REAL		-3
#define TT_WORD		-4
#define TT_STRING	'\''

class CTokenizer : public CObject
{
public:
	CTokenizer(CString& string);	// Constructor
	virtual ~CTokenizer();		    // Destructor

private:
	inline TCHAR GetChar()		// inline function
	{ 
		return m_sString[m_iChar++]; 
	}

	CString m_sString;			// the tokenized string

	BOOL m_bSlSlComments;		// Slash slash comments enabled
	BOOL m_bSlStComments;		// Slash star comments enabled
	BOOL m_bSharpComments;		// Sharp '#' comments enabled
	BOOL m_bSemicolonComments;	// Semicolon ';' comments enabled
	BOOL m_bEolIsSignificant;	// Specifies that EOL is significant or not
	BOOL m_bForceLower;			// Enable / disable case sensitivity
	BOOL m_bPushedBack;			//Enable Pushed Back

	int m_peekc;
	int m_iLineNo;
	int m_tType	;				// The last read token type
	
protected:
	CString	m_sVal;				// the value of the token
	double	m_dVal;
	int		m_iChar;			// the index of the current character

public:
	double GetNumValue();
	virtual CString GetStrValue();
	int LineNo();
	void PushBack();
	int NextToken();		// gives the next Token, returns the token type
	void LowerCaseMode(BOOL bFlag);	// Enable / disable case sensitivity
	void SlSlComments(BOOL bFlag);	// Enable C++ Style comments
	void SlStComments(BOOL bFlag);	// Enable C Style comments
	void SharpComments(BOOL bFlag);
	void SemicolonComments(BOOL bFlag);
	void EolIsSignificant(BOOL bFlag);	// Specifies that EOL is significant or not
};

#endif
