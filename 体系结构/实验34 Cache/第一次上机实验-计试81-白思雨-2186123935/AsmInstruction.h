#if !defined(AFX_ASMINSTRUCTION_H__253DF22C_4D68_4A38_B477_DCEEEAFC94AB__INCLUDED_)
#define AFX_ASMINSTRUCTION_H__253DF22C_4D68_4A38_B477_DCEEEAFC94AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "LexAnalyzer.h"

// AsmInstruction.h : header file
//
typedef enum {
	TYPE_I,
	TYPE_R,
	TYPE_J
} inst_type_t;

typedef struct {
	inst_type_t type;
	union {
		// I-type
		struct {
			UINT opcode : 6;
			UINT rs		: 5;
			UINT rt		: 5;
			int  imm	: 16;
		} i;
		
		// R-type
		struct {
			UINT opcode : 6;
			UINT rs		: 5;
			UINT rt		: 5;
			UINT rd		: 5;
			UINT shamt	: 5;
			UINT funct	: 6;
		} r;
		
		// J-type
		struct {
			UINT opcode : 6;
			int  offset	: 26;
		} j;
	} inst;
	CString target;// used in BEQZ, BNEZ and J instruction
} inst_t;

class CAsmInstruction
{
public:
	// call only by this fuction
	static CAsmInstruction* NextInst( CLexAnalyzer& analyzer );
	static CAsmInstruction* IdleInst();// construct a NOP inst
	
	~CAsmInstruction() {}
	CString InstString();
	CString InstWithLabel();
	CString InstWithLabelAddress();
	
protected:
	CAsmInstruction( CString& label, CString& op, ASMKey key, inst_t inst );

	// Attributes
public:
	CString m_strLabel;
	CString	m_strOp;
	ASMKey	m_key;
	inst_t	m_inst;
	int		m_dest;

	UINT	m_nAddress;
};

class CInstructions
{
public:
	CInstructions( CString& str );
	~CInstructions();

	void Reset();

private:
	void parse( CString& str );

	// Attributes
public:
	CList<CAsmInstruction*, CAsmInstruction*> m_instList;
};

#endif // !defined(AFX_ASMINSTRUCTION_H__253DF22C_4D68_4A38_B477_DCEEEAFC94AB__INCLUDED_)
