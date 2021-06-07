// AsmInstruction.cpp : implementation file
// Download by http://down.liehuo.net

#include "stdafx.h"

#include "AsmInstruction.h"
#include "Error.h"

//
// CLASS ASMINSTRUCTION
CAsmInstruction::CAsmInstruction( CString& label,
	CString& op, ASMKey key, inst_t inst ) : 
	m_strLabel( label ), m_strOp( op ), m_key( key ), m_inst( inst )
{
	m_dest = 0;
	m_nAddress = 0;
}

CAsmInstruction* CAsmInstruction::NextInst( CLexAnalyzer& analyzer )
{
	CString label = _T(""), op = _T("");
	ASMKey key;
	inst_t inst;
	inst.target = _T("");
	CAsmInstruction* pAsmInst = NULL;
	Lex lex = analyzer.NextToken();

	if( lex.key == USER ) {
		label = lex.str;
		analyzer.SkipKey( COLON );
		lex = analyzer.NextToken();
	}

	op = lex.str;
	key = lex.key;
	switch( lex.key ) {
	case LW:
	case SW:
		inst.type = TYPE_I;
		inst.inst.i.rt = analyzer.GetRegNum();
		analyzer.SkipKey();
		inst.inst.i.imm = analyzer.GetDigit();
		if( inst.inst.i.imm < 0 || inst.inst.i.imm > 0xFFFF )
			throw Error( ERROR_ASM_IMM, analyzer.LineNo() );
		analyzer.SkipKey( LEFT_PAR );
		inst.inst.i.rs = analyzer.GetRegNum();
		analyzer.SkipKey( RIGHT_PAR );
		pAsmInst = new CAsmInstruction( label, op, key, inst );
		if( lex.key == LW ) pAsmInst->m_dest = inst.inst.i.rt;
		break;

	case ADD:
	case SUB:
	case MUT:
	case MUL:
	case DIV:
	case AND:
	case OR:
	case XOR:
		inst.type = TYPE_R;
		inst.inst.r.rd = analyzer.GetRegNum();
		analyzer.SkipKey();
		inst.inst.r.rs = analyzer.GetRegNum();
		analyzer.SkipKey();
		inst.inst.r.rt = analyzer.GetRegNum();
		pAsmInst = new CAsmInstruction( label, op, key, inst );
		pAsmInst->m_dest = inst.inst.r.rd;
		break;

	case ADDI:
	case SUBI:
	case MUTI:
	case MULI:
	case DIVI:
	case ANDI:
	case ORI:
	case XORI:
		inst.type = TYPE_I;
		inst.inst.i.rt = analyzer.GetRegNum();
		analyzer.SkipKey();
		inst.inst.i.rs = analyzer.GetRegNum();
		analyzer.SkipKey();
		inst.inst.i.imm = analyzer.GetDigit();
		pAsmInst = new CAsmInstruction( label, op, key, inst );
		pAsmInst->m_dest = inst.inst.i.rt;
		break;

	case BEQZ:
	case BNEZ:
		inst.type = TYPE_I;
		inst.inst.i.rs = analyzer.GetRegNum();
		analyzer.SkipKey();
		inst.target = analyzer.GetString();
		pAsmInst = new CAsmInstruction( label, op, key, inst );
		break;

	case J:
		inst.type = TYPE_J;
		inst.target = analyzer.GetString();
		pAsmInst = new CAsmInstruction( label, op, key, inst );
		break;

	case JR:
		inst.type = TYPE_I;
		inst.inst.i.rs = analyzer.GetRegNum();
		pAsmInst = new CAsmInstruction( label, op, key, inst );
		break;

	case TRAP:
		inst.type = TYPE_J;
		inst.inst.j.offset = analyzer.GetDigit();
		pAsmInst = new CAsmInstruction( label, op, key, inst );
		break;

	case NOP:
		inst.type = TYPE_R;
		inst.inst.r.rs = inst.inst.r.rt = inst.inst.r.rd = 0;
		pAsmInst = new CAsmInstruction( label, op, key, inst );
		break;

	case _EOF:
		break;
	default:
		throw Error( ERROR_ASM_INST, analyzer.LineNo(), lex.str );
	}

	return pAsmInst;
}

CAsmInstruction* CAsmInstruction::IdleInst()
{
	inst_t inst;
	inst.type = TYPE_R;
	inst.inst.r.rs = inst.inst.r.rt = inst.inst.r.rd = 0;
	CAsmInstruction* pInst = new CAsmInstruction(CString(_T("")),
		CString("idle"), IDLE_INST, inst);
	pInst->m_nAddress = (UINT)-1;
	return pInst;
}

CString CAsmInstruction::InstString()
{
	CString temp;

	switch( m_key ) {
	case LW:
	case SW:
		temp.Format( "%s      r%d, %d(r%d)", (LPCTSTR)m_strOp,
			m_inst.inst.i.rt, m_inst.inst.i.imm, m_inst.inst.i.rs );
		break;

	case ADD:
	case SUB:
	case MUT:
	case MUL:
	case DIV:
	case AND:
	case XOR:
		temp.Format( "%s     r%d, r%d, r%d", (LPCTSTR)m_strOp,
			m_inst.inst.r.rd, m_inst.inst.r.rs, m_inst.inst.r.rt );
		break;

	case OR:
		temp.Format( "%s      r%d, r%d, r%d", (LPCTSTR)m_strOp,
			m_inst.inst.r.rd, m_inst.inst.r.rs, m_inst.inst.r.rt );
		break;

	case ADDI:
	case SUBI:
	case MUTI:
	case MULI:
	case DIVI:
	case ANDI:
	case XORI:
		temp.Format( "%s    r%d, r%d, %d", (LPCTSTR)m_strOp, 
			m_inst.inst.i.rt, m_inst.inst.i.rs, m_inst.inst.i.imm );
		break;

	case ORI:
		temp.Format( "%s     r%d, r%d, %d", (LPCTSTR)m_strOp, 
			m_inst.inst.i.rt, m_inst.inst.i.rs, m_inst.inst.i.imm );
		break;

	case BEQZ:
	case BNEZ:
		temp.Format( "%s    r%d, %s", (LPCTSTR)m_strOp,
			m_inst.inst.i.rs, (LPCTSTR)m_inst.target );
		break;

	case J:
		temp.Format( "%s       %s", (LPCTSTR)m_strOp,
			(LPCTSTR)m_inst.target );
		break;

	case JR:
		temp.Format( "%s      r%d", (LPCTSTR)m_strOp,
			m_inst.inst.i.rs );
		break;

	case TRAP:
		temp.Format( "%s    #%d", (LPCTSTR)m_strOp,
			m_inst.inst.j.offset );
		break;

	case IDLE_INST:
		temp = "idle";
		break;

	default:
		temp = _T("");
	}

	return temp;
}

CString CAsmInstruction::InstWithLabel()
{
	CString temp;
	if( !m_strLabel.IsEmpty() ) {
		temp += m_strLabel;
		temp += _T(": ");
	}
	if( temp.GetLength() < 10 )
		for( int i = temp.GetLength(); i < 10; i++ )
			temp += _T(" ");
	temp += InstString();
	return temp;
}

CString CAsmInstruction::InstWithLabelAddress()
{
	CString temp;
	temp.Format( "(0x%.8X) ", m_nAddress );
	temp += InstWithLabel();
	return temp;
}

//
// CLASS CINSTRUCTIONS
CInstructions::CInstructions( CString& str )
{
	parse( str );
}

CInstructions::~CInstructions()
{
	while( !m_instList.IsEmpty() ) {
		CAsmInstruction* pInst = m_instList.RemoveHead();
		delete pInst;
	}
}

void CInstructions::parse( CString& str )
{
	CLexAnalyzer analyzer( str );
	CAsmInstruction* pAsmInst = NULL;

	pAsmInst = CAsmInstruction::NextInst( analyzer );
	while( pAsmInst ) {
		m_instList.AddTail( pAsmInst );
		pAsmInst = CAsmInstruction::NextInst( analyzer );
	}
}

void CInstructions::Reset()
{
	m_instList.RemoveAll();
}
