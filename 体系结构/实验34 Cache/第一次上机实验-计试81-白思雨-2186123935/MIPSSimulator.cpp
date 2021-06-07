// MIPSSimulator.cpp : implementation file
//

#include "stdafx.h"
#include "pipeline.h"
#include "MIPSSimulator.h"
#include "Error.h"

#include <malloc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString MIPSStage[] =
{
	"IF", "ID", "EX", "MEM", "WB", "STALL", "IDLE", "COMPLETE"
};

/////////////////////////////////////////////////////////
// Global
CMIPSSimulator simulator;

/////////////////////////////////////////////////////////
// CLASS CMIPSSIMULATOR
/////////////////////////////////////////////////////////
// Construction
CMIPSSimulator::CMIPSSimulator()
{
	m_pInsts = NULL;
	m_pExecInsts = new CExecInst(1);
	data = NULL;

	/****************************************
	 * Configurations
	 ****************************************/
	m_bForwardingEnable = TRUE;
	m_nBranchMethod = kFreeze;
	// delays
	m_nAddDelay = 1;
	m_nMulDelay = 5;
	m_nDivDelay = 19;
	// ALU numbers
	m_nAddNum = 1;
	m_nMulNum = 1;
	m_nDivNum = 1;
	// is ALU pipelined
	m_bAddPipelined = TRUE;
	m_bMulPipelined = TRUE;
	m_bDivPipelined = FALSE;
	// memory
	m_nMemSize = 0x1000;
	m_nDataSize = 0x100;
	m_bBigEnding = FALSE;

	Reset();
}

CMIPSSimulator::~CMIPSSimulator()
{
	if( m_pExecInsts ) delete m_pExecInsts;
	if( m_pInsts ) delete m_pInsts;
	if( data ) free( data );
	if( data_bak ) free( data_bak );
	if( m_TraceFile.m_hFile != CFile::hFileNull )
		m_TraceFile.Close();
}

void CMIPSSimulator::ResetProgram()
{
	m_bTrace = FALSE;
	m_bNewStep = FALSE;
	m_nState = kNone;
	// Program Counter
	PC = m_nDataSize;

	if( m_pExecInsts->next ) { 
		delete m_pExecInsts->next; 
		m_pExecInsts->next = NULL;
	}
	if( m_pInsts ) { delete m_pInsts; m_pInsts = NULL; }
	memset( &STAT, 0, sizeof(STAT) );
}

void CMIPSSimulator::Reset()
{
	m_bTrace = FALSE;
	m_bNewStep = FALSE;
	m_nState = kNone;
	// Program Counter
	PC = m_nDataSize;

	if( m_pExecInsts->next ) { 
		delete m_pExecInsts->next; 
		m_pExecInsts->next = NULL;
	}
	if( m_pInsts ) { delete m_pInsts; m_pInsts = NULL; }
	if( data ) memset( data, 0, m_nDataSize );
	memset( reg, 0, sizeof(reg) );
	memset( &STAT, 0, sizeof(STAT) );

	ClearIFIDReg();
	ClearIDEXReg();
	ClearEXMEMReg();
	ClearMUL_EXMEMReg();
	ClearDIV_EXMEMReg();
	ClearMEMWBReg();
	ClearMUL_MEMWBReg();
	ClearDIV_MEMWBReg();
}

void CMIPSSimulator::CreateDataMem()
{
	if( data == NULL ) {
		data = (int*)malloc( m_nDataSize );
		memset( data, 0, m_nDataSize );
	} else {
		UINT len = _msize( data );
		if( m_nDataSize != len )
			data = (int*)realloc( data, m_nDataSize );
		if( len < m_nDataSize )
			memset( &data[len/4], 0, m_nDataSize - len );
	}

	if( m_pInsts ) {
		PC = m_nDataSize;
		// asign addresses
		AsignAddress();
		// Resolve labels in J-TYPE instructions
		ResolveLabels();
	}
}

void CMIPSSimulator::ClearDataMem()
{
	memset( data, 0, _msize(data) );
}

void CMIPSSimulator::FreeDataMem()
{
	free( data ); data = NULL;
}

void CMIPSSimulator::BackupMem()
{
	data_bak = (int*)realloc(data_bak, _msize(data));
	memcpy( data_bak, data, _msize(data) );
}

void CMIPSSimulator::RollBackMem()
{
	ASSERT( _msize(data) == _msize(data_bak) );
	memcpy( data, data_bak, _msize(data) );
}

void CMIPSSimulator::BackupReg()
{
	for( int i = 0; i < 32; i++ )
		reg_bak[i] = reg[i].content;
}

void CMIPSSimulator::RollBackReg()
{
	CSlot slot;
	for( int i = 0; i < 32; i++ ) {
		slot.content = reg_bak[i];
		reg[i] = slot;
	}
}

BOOL CMIPSSimulator::IsReadyForExec()
{
	if( data && m_pInsts && m_pInsts->m_instList.GetCount() )
		return TRUE;
	return FALSE;
}

BOOL CMIPSSimulator::LoadInstFromFile( LPCTSTR pathname )
{
	CFile cfile;
	// open the file
	try {
		cfile.Open( pathname, CFile::modeRead );
	} catch( CFileException& ) {
		CString temp;
		temp.Format( "failed to open\n%s", pathname );
		AfxMessageBox( temp );
		return FALSE;
	}
	// read the whole content
	CString strBuf;
	char buf[ 4100 ];
	int len = 0;
	try {
		while( (len = cfile.Read(buf, 4096)) > 0 ) {
			buf[len] = '\0';
			strBuf += (CString)buf;
		}
		strBuf += "\r\n";
	} catch( CFileException& ) {
		CString temp;
		temp.Format( "error occurs while reading\n%s", pathname );
		AfxMessageBox( temp );
		cfile.Close();
		return FALSE;
	}
	cfile.Close();// close the file
	try {
		// construct the Instructions object
		m_pInsts = new CInstructions( strBuf );
		if( m_pInsts->m_instList.IsEmpty() ) {
			delete m_pInsts; m_pInsts = NULL;
			return FALSE;
		}
		// asign addresses
		AsignAddress();
		// Resolve labels in J-TYPE instructions
		ResolveLabels();
	} catch( Error& e ) {
		AfxMessageBox( e.GetStrError() );
		return FALSE;
	}

	strBuf.Empty();
	return TRUE;
}

BOOL CMIPSSimulator::Trace( LPCTSTR pathname )
{
	// close the file if necessary
	if( m_TraceFile.m_hFile != CFile::hFileNull )
		m_TraceFile.Close();
	// create the output file
	CFileException e;
	if( !m_TraceFile.Open( pathname, CFile::modeCreate |
		CFile::modeWrite, &e ) ) {
		CString temp;
		temp.Format( "failed to open %s\n%s", pathname, e.m_cause );
		AfxMessageBox( temp );
		return FALSE;
	}
	m_bTrace = TRUE;
	return TRUE;
}

void CMIPSSimulator::StopTrace()
{
	if( m_TraceFile.m_hFile != CFile::hFileNull )
		m_TraceFile.Close();
}

/////////////////////////////////////////////////////////
// Asign memory addresses and Resolve labels
void CMIPSSimulator::AsignAddress()
{
	UINT address = m_nDataSize;
	POSITION pos = m_pInsts->m_instList.GetHeadPosition();
	while( pos ) {
		CAsmInstruction* pInst = m_pInsts->m_instList.GetNext( pos );
		pInst->m_nAddress = address;
		address += 4;
	}
}

int CMIPSSimulator::FindTargetAddress( CString& target )
{
	POSITION pos = m_pInsts->m_instList.GetHeadPosition();
	while( pos ) {
		CAsmInstruction* pInst = m_pInsts->m_instList.GetNext( pos );
		if( pInst->m_strLabel == target )
			return pInst->m_nAddress;
	}
	return -1;
}

void CMIPSSimulator::ResolveLabels()
{
	POSITION pos = m_pInsts->m_instList.GetHeadPosition();
	while( pos ) {
		CAsmInstruction* pInst = m_pInsts->m_instList.GetNext( pos );
		if( pInst->m_key == J || pInst->m_key == BEQZ || pInst->m_key == BNEZ ) {
			int address = FindTargetAddress( pInst->m_inst.target );
			if( address < 0 )
				throw Error( ERROR_ASM_TARGET, 0, pInst->m_inst.target );
			if( pInst->m_key == J )
				pInst->m_inst.inst.j.offset = address>>2;
			else {
				int offset = address - pInst->m_nAddress - 4;
				pInst->m_inst.inst.i.imm = offset;
			}
		}
	}
}

int CMIPSSimulator::FindIndexFromAddress( UINT address )
{
	int index = 0;
	POSITION pos = m_pInsts->m_instList.GetHeadPosition();
	while( pos ) {
		CAsmInstruction* pInst;
		pInst = m_pInsts->m_instList.GetNext( pos );
		if( pInst->m_nAddress == address )
			return index;
		index++;
	}
	return -1;
}

//

/////////////////////////////////////////////////////////
// Clear MIPS CPU Registers
void CMIPSSimulator::ClearIFIDReg()
{
	IFID.NPC = 0;
	IFID.IR = NULL;
}

void CMIPSSimulator::ClearIDEXReg()
{
	IDEX.A = 0;
	IDEX.B = 0;
	IDEX.Imm = 0;
	IDEX.IR = NULL;
}

void CMIPSSimulator::ClearEXMEMReg()
{
	EXMEM.ALUOutput = 0;
	EXMEM.B = 0;
	EXMEM.IR = NULL;
}

void CMIPSSimulator::ClearMUL_EXMEMReg()
{
	MUL_EXMEM.ALUOutput = 0;
	MUL_EXMEM.B = 0;
	MUL_EXMEM.IR = NULL;
}

void CMIPSSimulator::ClearDIV_EXMEMReg()
{
	DIV_EXMEM.ALUOutput = 0;
	DIV_EXMEM.B = 0;
	DIV_EXMEM.IR = NULL;
}

void CMIPSSimulator::ClearMEMWBReg()
{
	MEMWB.ALUOutput = 0;
	MEMWB.LMD = 0;
	MEMWB.IR = NULL;
}

void CMIPSSimulator::ClearMUL_MEMWBReg()
{
	MUL_MEMWB.ALUOutput = 0;
	MUL_MEMWB.LMD = 0;
	MUL_MEMWB.IR = NULL;
}

void CMIPSSimulator::ClearDIV_MEMWBReg()
{
	DIV_MEMWB.ALUOutput = 0;
	DIV_MEMWB.LMD = 0;
	DIV_MEMWB.IR = NULL;
}
//

// Set Program Counter
BOOL CMIPSSimulator::SetPC(UINT address)
{
	POSITION pos = m_pInsts->m_instList.GetHeadPosition();
	while( pos ) {
		CAsmInstruction* pInst = m_pInsts->m_instList.GetNext( pos );
		if( pInst->m_nAddress == address ) {
			PC = address;
			return TRUE;
		}
	}
	return FALSE;
}

// fetch instruction pointed by PC;
CAsmInstruction* CMIPSSimulator::FetchInst()
{
	CAsmInstruction* pInst = NULL;
	POSITION pos = m_pInsts->m_instList.GetHeadPosition();
	while( pos ) {
		pInst = m_pInsts->m_instList.GetNext( pos );
		if( pInst->m_nAddress == PC ) {
			CalcStat( pInst );
			m_bNewStep = TRUE;
			/*
			 * trace instructions
			 */
			if( m_bTrace ) {
				CString temp;
				temp.Format( "STEP:%3d CYCLE:%3d  %s\r\n", GetCurStep(),
					GetCurCycle() + 1, (LPCTSTR)pInst->InstWithLabelAddress() );
				try {
					m_TraceFile.Write( (LPCTSTR)temp, temp.GetLength() );
					m_TraceFile.Flush();
				} catch( CFileException* e ) {
					temp.Format( "%s", e->m_cause );
					AfxMessageBox( temp );
				}
			}

			return pInst;
		}
	}
	return NULL;
}

void CMIPSSimulator::CalcStat(CAsmInstruction* pInst)
{
	STAT.steps++;
	// increase instruction count
	int* p = (int*)&STAT;
	p[(int)pInst->m_key]++;
}

/////////////////////////////////////////////////////////
// Execution

void CMIPSSimulator::Start()
{
	ASSERT( m_pExecInsts->next == NULL );
	ASSERT( data != NULL );

	// trace
	if( m_bTrace ) {
		CString temp = _T("Program start:\r\n");
		m_TraceFile.Write( (LPCTSTR)temp, temp.GetLength() );
		m_TraceFile.Flush();
	}

	m_nState = kRun;
	BackupMem();
	BackupReg();
	m_nStartPC = PC;
	m_pExecInsts->m_nCurCycle = 1;
	m_pExecInsts->FetchInst();
	STAT.cycles = 0;
}

void CMIPSSimulator::NextCycle()
{
	if( m_nState == kComplete ) return;
	if( IsExecComplete() ) m_nState = kComplete;

	m_bNewStep = FALSE;
	m_nLastPC = PC;
	if( m_pExecInsts->next )
		m_pExecInsts->next->NextCycle();
	STAT.cycles++;
}

void CMIPSSimulator::PrevCycle()
{
	CycleTo( STAT.cycles - 1 );
}

void CMIPSSimulator::RollBackToStartState()
{
	m_nState = kRun;
	PC = m_nStartPC;
	RollBackMem();
	RollBackReg();
	memset( &STAT, 0, sizeof(STAT) );
	if( m_pExecInsts->next ) {
		delete m_pExecInsts->next; m_pExecInsts->next = NULL;
	}

	// trace
	if( m_bTrace ) {
		CString temp = _T("Program restart:\r\n");
		m_TraceFile.Write( (LPCTSTR)temp, temp.GetLength() );
		m_TraceFile.Flush();
	}

	m_pExecInsts->m_nCurCycle = 1;
	m_pExecInsts->FetchInst();
	STAT.cycles = 0;
}

void CMIPSSimulator::CycleTo( int cycle )
{
	RollBackToStartState();
	while( STAT.cycles < cycle )
		NextCycle();
}

int CMIPSSimulator::GetCurCycle()
{
	return STAT.cycles;
}

int CMIPSSimulator::GetCurStep()
{
	return STAT.steps;
}

// The space pExecInst pointed is deallocated after this function
BOOL CMIPSSimulator::GetStageArray( CExecInst* pExecInst,
	UINT_ARRAY& outStageArray )
{
	BOOL found = FALSE;
	CExecInst* next = m_pExecInsts->next;
	while( next ) {
		if( next == pExecInst ) {
			found = TRUE; break;
		}
		next = next->next;
	}
	if( !found ) {
#ifdef _DEBUG
		AfxMessageBox( "CMIPSSimulator::GetStageArray(..) error." );
#endif //_DEBUG
		return FALSE;// It should not occur.
	}
	// close trace
	BOOL bTrace = m_bTrace; m_bTrace = FALSE;
	UINT nCurCycle = pExecInst->m_nCurCycle;
	outStageArray.Add( pExecInst->m_nLastStage );
	while( pExecInst->m_nCurStage != COMPLETE ) {
		NextCycle();
		outStageArray.Add( pExecInst->m_nLastStage );
	}
	// Roll back
	CycleTo( nCurCycle );
	// 
	m_bTrace = bTrace;
	return TRUE;
}

BOOL CMIPSSimulator::HasNewStep()
{
	return m_bNewStep;
}

CExecInst* CMIPSSimulator::GetNewExecInst()
{
	CExecInst* next = m_pExecInsts->next;
	while( next && next->next ) {
		next = next->next;
	}
	return next;
}

BOOL CMIPSSimulator::HasInstComplete(UINT_ARRAY& outCompleteArray)
{
	outCompleteArray.RemoveAll();
	CExecInst* next = m_pExecInsts->next;
	while( next ) {
		if( next->m_nCurStage == COMPLETE && next->pInst->m_key != IDLE_INST )
			outCompleteArray.Add( next->pInst->m_nAddress );
		next = next->next;
	}
	if( outCompleteArray.GetSize() > 0 ) return TRUE;
	return FALSE;
}

BOOL CMIPSSimulator::HasIdleInstComplete()
{
	CExecInst* next = m_pExecInsts->next;
	while( next ) {
		if( next->m_nCurStage == COMPLETE && next->pInst->m_key == IDLE_INST )
			return TRUE;
		next = next->next;
	}
	return FALSE;
}

BOOL CMIPSSimulator::IsExecComplete()
{
	if( m_pExecInsts->next == NULL )
		return TRUE;
	return FALSE;
}








/////////////////////////////////////////////////////////
// CLASS CEXECINST
/////////////////////////////////////////////////////////
// Construction
CExecInst::CExecInst( int cycle, CAsmInstruction* inst,
					 CExecInst* prev, CExecInst* next )
{
	m_nStartCycle	= cycle;
	m_nCurCycle		= cycle - 1;
	m_nCurMulCycle	= 0;
	m_nCurDivCycle	= 0;
	m_nCurStage		= IF;
	m_nLastStage	= IF;
	m_bBranchTaken	= TRUE;
	m_bStall		= FALSE;
	m_bIdle			= FALSE;

	m_nA			= 0;
	m_nB			= 0;
	m_nImm			= 0;
	
	pInst = inst;
	// link the previous and next node
	this->prev = prev;
	this->next = next;
	if( prev ) prev->next = this;
	if( next ) next->prev = this;

	// prevent data hazards
	m_bForward	= FALSE;
	m_bForwardReady = FALSE;
	m_bReadFromForward = FALSE;
}

CExecInst::~CExecInst()
{
	if( pInst && pInst->m_key == IDLE_INST )// create by Freeze()
		delete pInst;
	if( prev ) prev->next = NULL;
	if( next ) {
		next->prev = NULL;
		delete next;
	}
}

// MIPS CPU: DO ONE CYCLE
void CExecInst::NextCycle()
{
	m_nCurCycle++;

	// for stageComplete() delete itself
	CExecInst* pNextExecInst = next;

	switch( m_nCurStage ) {
	case IF:
		stageIF(); break;
	case ID:
		stageID();
		pNextExecInst = next;// this stage load the next instruction
		break;
	case EX:
		stageEX(); break;
	case MEM:
		stageMEM(); break;
	case WB:
		stageWB(); break;
	case COMPLETE:
		stageComplete();
	}

	// Recursive call
	if( pNextExecInst ) pNextExecInst->NextCycle();
}

// stall call
void CExecInst::Stall()
{
	m_bStall = TRUE;
	if( next ) next->Stall();
}

// idle call, clear next stage registers
void CExecInst::Idle()
{
	m_bIdle = TRUE;
}

// Fetch the next instruction...
COLORREF ColorArray[] = 
{
	RGB(255,0,0), RGB(128,0,0), RGB(0,0,255),
	RGB(0,128,0), RGB(0,0,160), RGB(255,0,255),
	RGB(128,128,0), RGB(0,64,128), RGB(0,128,128),
	RGB(255,128,0)
};

void CExecInst::FetchInst()
{
	CAsmInstruction* pInst = simulator.FetchInst();
	if( pInst ) {
		CExecInst* pExecInst = new CExecInst( m_nCurCycle,
			pInst, this, this->next );
		pExecInst->color = ColorArray[m_nCurCycle % 10];
	}
}

// Freeze the pipeline, deleting any instructions after the branch
void CExecInst::Freeze()
{
	simulator.m_bNewStep = TRUE;

	CAsmInstruction* pInst = CAsmInstruction::IdleInst();
	CExecInst* pExecInst = new CExecInst( m_nCurCycle, pInst, this, this->next );
	pExecInst->Idle();
	pExecInst->color = ColorArray[m_nCurCycle % 10];
}

/////////////////////////////////////////////////////////
// MIPS CPU Registers Access
int CExecInst::GetRegContent(UINT reg)
{
	if( reg < 32 )
		return simulator.reg[reg].content;
	throw Error(ERROR_MIPS_REG_OUTRANGE, reg);
}

int CExecInst::GetRegForward(UINT reg)
{
	if( reg < 32 )
		return simulator.reg[reg].forward;
	throw Error(ERROR_MIPS_REG_OUTRANGE, reg);
}

int CExecInst::GetRegStatus(UINT reg)
{
	if( reg < 32 )
		return simulator.reg[reg].status;
	throw Error(ERROR_MIPS_REG_OUTRANGE, reg);
}

int CExecInst::GetRegData(UINT reg)
{
	if( reg < 32 ) {
		if( m_bReadFromForward ) {
			m_bReadFromForward = FALSE;
			return simulator.reg[reg].forward;
		} else
			return simulator.reg[reg].content;
	}
	throw Error(ERROR_MIPS_REG_OUTRANGE, reg);
}

void CExecInst::SetRegContent(UINT reg, int content)
{
	if( reg < 32 ) {
		if( reg > 0 ) {// R0 is always be 0
			simulator.reg[reg].content = content;
			if( simulator.reg[reg].write_count > 0 )
				simulator.reg[reg].write_count--;
			if( simulator.reg[reg].write_count == 0 )
				simulator.reg[reg].status = kReady;
			else
				simulator.reg[reg].status = kWrite;
		}
	} else
		throw Error(ERROR_MIPS_REG_OUTRANGE, reg);
}

void CExecInst::SetRegForward(UINT reg, int forward)
{
	if( reg < 31 ) {
		// R0 is always be 0
		if( reg > 0 && simulator.m_bForwardingEnable ) {
			simulator.reg[reg].forward = forward;
			m_bForward = TRUE;
		}
	} else
		throw Error(ERROR_MIPS_REG_OUTRANGE, reg);
}

void CExecInst::SetRegStatus(UINT reg, int status)
{
	if( reg < 31 ) {
		if( reg > 0 ) {// R0 is always be 0
			simulator.reg[reg].status = status;
			if( status == kWrite )
				simulator.reg[reg].write_count++;
		}
	} else
		throw Error(ERROR_MIPS_REG_OUTRANGE, reg);
}

int CExecInst::GetImm()
{
	if( pInst->m_inst.type == TYPE_I )
		return (int)pInst->m_inst.inst.i.imm;
	return 0;
}
//

/////////////////////////////////////////////////////////
int CExecInst::ReadMem(UINT address)
{
	if( address < simulator.m_nDataSize )
		return simulator.data[address/4];
	throw Error(ERROR_MIPS_MEM_OUTRANGE, address);
}

void CExecInst::WriteMem(UINT address, int content)
{
	if( address < simulator.m_nDataSize )
		simulator.data[address/4] = content;
	else
		throw Error(ERROR_MIPS_MEM_OUTRANGE, address);
}

/////////////////////////////////////////////////////////
// Stage Operations
// IF
void CExecInst::stageIF()
{
	if( m_bStall ) {
		// stall this cycle, remain in stage IF
		m_nLastStage = STALL;
		m_bStall = FALSE;
	} else if( m_bIdle ) {
		// clear cpu registers and go to next stage
		m_nLastStage = IDLE;
		m_nCurStage = ID;
		simulator.ClearIFIDReg();
	} else {
		// put results into IF/ID registers and
		// go to next stage
		m_nLastStage = IF;
		m_nCurStage = ID;// Go to next cycle
		simulator.PC += 4;
		simulator.IFID.IR = pInst;
		simulator.IFID.NPC = simulator.PC;
	}
}

// ID
void CExecInst::stageID()
{
	if( m_bStall ) {
		// stall this cycle, remain in stage ID
		m_nLastStage = STALL;
		m_bStall = FALSE;
	} else if( m_bIdle ) {
		// Read in the next instruction.
		// clear cpu registers and go to next stage
		FetchInst();
		m_nLastStage = IDLE;
		m_nCurStage = EX;
		simulator.ClearIDEXReg();
	} else {
		// Read in the next instruction, decode
		// Put results into ID/EX registers and go to next stage.
		m_nLastStage = ID;
		m_nCurStage = EX;// Go to next cycle
		switch( pInst->m_inst.type ) {
		case TYPE_R:
			// fetch next instruction
			if( next == NULL ) FetchInst();
			SetRegStatus(pInst->m_inst.inst.r.rd, kWrite);
			simulator.IDEX.A = GetRegContent(pInst->m_inst.inst.r.rs);
			simulator.IDEX.B = GetRegContent(pInst->m_inst.inst.r.rt);
			simulator.IDEX.Imm = 0;
			simulator.IDEX.IR = pInst;
			// If forwarding is disable, check data hazards
			if( !simulator.m_bForwardingEnable &&
				(GetRegStatus(pInst->m_inst.inst.r.rs) == kWrite ||
				GetRegStatus(pInst->m_inst.inst.r.rt) == kWrite) ) {
				m_nLastStage = STALL;
				m_nCurStage = ID;
				if( next ) next->Stall();
				return;
			}
			break;

		case TYPE_I:
			// set register status
			if( pInst->m_key != SW && pInst->m_key != BEQZ &&
				pInst->m_key != BNEZ && pInst->m_key != JR )
				SetRegStatus(pInst->m_inst.inst.i.rt, kWrite);
			simulator.IDEX.A = GetRegContent(pInst->m_inst.inst.i.rs);
			simulator.IDEX.B = GetRegContent(pInst->m_inst.inst.i.rt);
			simulator.IDEX.Imm = GetImm();
			simulator.IDEX.IR = pInst;
			// If forwarding is disable, check data hazards
			if( !simulator.m_bForwardingEnable &&
				(GetRegStatus(pInst->m_inst.inst.r.rs) == kWrite ||
				(pInst->m_key == SW)?(GetRegStatus(pInst->m_inst.inst.r.rt) == kWrite):FALSE) ) {
				m_nLastStage = STALL;
				m_nCurStage = ID;
				if( next ) next->Stall();
				return;
			}
			// For BEQZ and BNEZ, use different Branch strategies
			if( pInst->m_key == BEQZ || pInst->m_key == BNEZ || pInst->m_key == JR ) {
				// Methods
				if( simulator.m_nBranchMethod == CMIPSSimulator::kFreeze ||
					simulator.m_nBranchMethod == CMIPSSimulator::kPredictedTaken ) {
					// Freeze and Branch-Taken methods, 
					// they are the same in 5-stage integer pipeline
					// read in the next instruction, NOP
					if( !next )	Freeze();
				} else {
					// Predicted-Not-Taken and Delayed slot,
					// fetch the next instruction
					// read in the next instruction, NORMAL
					if( !next ) FetchInst();
				}
				if( HasDataHazards(pInst->m_inst.inst.i.rs) ) {
					// Data hazzard, stall
					m_nLastStage = STALL;
					m_nCurStage = ID;
					if( next ) next->Stall();
					return;
				}
				// for conditional branch BEQZ and BNEZ
				// check if taken, and updata PC
				if( pInst->m_key == BEQZ ) {
					if( GetRegData(pInst->m_inst.inst.i.rs) == 0 ) {
						m_bBranchTaken = TRUE;
						simulator.PC = simulator.IFID.NPC + simulator.IDEX.Imm;
						if( simulator.m_nBranchMethod == CMIPSSimulator::kPredictedNotTaken ||
							simulator.m_nBranchMethod == CMIPSSimulator::kDelayedBranch )
							simulator.PC -= 4;
					}
				} else if( pInst->m_key == BNEZ ) {
					if( GetRegData(pInst->m_inst.inst.i.rs) != 0 ) {
						m_bBranchTaken = TRUE;
						simulator.PC = simulator.IFID.NPC + simulator.IDEX.Imm;
						if( simulator.m_nBranchMethod == CMIPSSimulator::kPredictedNotTaken ||
							simulator.m_nBranchMethod == CMIPSSimulator::kDelayedBranch )
							simulator.PC -= 4;
					}
				} else {
					// JR
					simulator.PC = GetRegData( pInst->m_inst.inst.i.rs );
				}
			} else
				// fetch next instruction
				if( !next ) FetchInst();
			break;

		case TYPE_J:
			if( pInst->m_key == TRAP ) 
				// program completes
				// just RETURN, do NOT fetch any instruction following
				return;
			else if( pInst->m_key == J ) {
				// j name
				simulator.IDEX.A = 0;
				simulator.IDEX.B = 0;
				simulator.IDEX.Imm = 0;
				simulator.IDEX.IR = pInst;
				// Methods
				if( simulator.m_nBranchMethod == CMIPSSimulator::kFreeze ||
					simulator.m_nBranchMethod == CMIPSSimulator::kPredictedTaken ) {
					// Freeze and Branch-Taken methods, 
					// they are the same in 5-stage integer pipeline
					Freeze();
				} else {
					// Predicted-Not-Taken and Delayed slot,
					// fetch the next instruction
					FetchInst();
				}
				// update PC
				simulator.PC &= 0xF0000000;
				simulator.PC += pInst->m_inst.inst.j.offset<<2;
			}
			break;
		}
	}
}

// EX
void CExecInst::stageEX()
{
	if( pInst->m_key == MUL || pInst->m_key == MULI ||
		pInst->m_key == MUT || pInst->m_key == MUTI ||
		pInst->m_key == DIV || pInst->m_key == DIVI )
		// DON'T STALL
		m_bStall = FALSE;

	if( m_bStall ) {
		// stall this cycle, remain in stage EX
		m_nLastStage = STALL;
		m_bStall = FALSE;
	} else if( m_bIdle ) {
		m_nLastStage = IDLE;
		m_nCurStage = MEM;
		simulator.ClearEXMEMReg();
	} else {
		m_nLastStage = EX;
		m_nCurStage = MEM;// Go to next cycle
		simulator.EXMEM.B = simulator.IDEX.B;
		simulator.EXMEM.IR = pInst;
		switch( pInst->m_inst.type ) {
		case TYPE_R:
			if( m_nCurMulCycle == 0 && m_nCurDivCycle == 0 ) {
				if( HasDataHazards(pInst->m_inst.inst.r.rs) ) {
					// Data hazard, stall
					m_nLastStage = STALL;
					m_nCurStage = EX;
					if( next ) next->Stall();
					return;
				} else
					m_nA = GetRegData(pInst->m_inst.inst.r.rs);
				if(	HasDataHazards(pInst->m_inst.inst.r.rt) ) {
					// Data hazard, stall
					m_nLastStage = STALL;
					m_nCurStage = EX;
					if( next ) next->Stall();
					return;
				} else
					m_nB = GetRegData(pInst->m_inst.inst.r.rt);
			}
			switch( pInst->m_key ) {
			case IDLE_INST:
			case ADD:
				simulator.EXMEM.ALUOutput = m_nA + m_nB;
				SetRegForward(pInst->m_inst.inst.r.rd, simulator.EXMEM.ALUOutput);
				break;

			case SUB:
				simulator.EXMEM.ALUOutput = m_nA - m_nB;
				SetRegForward(pInst->m_inst.inst.r.rd, simulator.EXMEM.ALUOutput);
				break;

			case MUL:
			case MUT:
				m_nCurMulCycle++;
				if( (UINT)m_nCurMulCycle < simulator.m_nMulDelay ) {
					// go to next EX cycle
					m_nLastStage = EX;
					m_nCurStage = EX;
				} else {
					simulator.MUL_EXMEM.ALUOutput = m_nA * m_nB;
					simulator.MUL_EXMEM.IR = pInst;
					SetRegForward(pInst->m_inst.inst.r.rd, simulator.MUL_EXMEM.ALUOutput);
				}
				break;

			case DIV:
				if( !m_nCurDivCycle ) {
					// begin DIV cycle
					// DIV line is not piped
					if( HasStructualHazards() ) {
						// structual hazards, stall
						m_nLastStage = STALL;
						m_nCurStage = EX;
						if( next ) next->Stall();
						return;
					}
				}
				m_nCurDivCycle++;
				if( (UINT)m_nCurDivCycle < simulator.m_nDivDelay ) {
					// go to next EX cycle
					m_nLastStage = EX;
					m_nCurStage = EX;
				} else {
					simulator.DIV_EXMEM.ALUOutput = m_nA / m_nB;
					simulator.DIV_EXMEM.IR = pInst;
					SetRegForward(pInst->m_inst.inst.r.rd, simulator.DIV_EXMEM.ALUOutput);
				}
				break;

			case AND:
				simulator.EXMEM.ALUOutput = m_nA & m_nB;
				SetRegForward(pInst->m_inst.inst.r.rd, simulator.EXMEM.ALUOutput);
				break;

			case OR:
				simulator.EXMEM.ALUOutput = m_nA | m_nB;
				SetRegForward(pInst->m_inst.inst.r.rd, simulator.EXMEM.ALUOutput);
				break;

			case XOR:
				simulator.EXMEM.ALUOutput = m_nA ^ m_nB;
				SetRegForward(pInst->m_inst.inst.r.rd, simulator.EXMEM.ALUOutput);
				break;
			}
			break;// TYPE_R

		case TYPE_I:
			if( m_nCurMulCycle == 0 && m_nCurDivCycle == 0 ) {
				if( HasDataHazards(pInst->m_inst.inst.i.rs) ) {
					// Data hazard, stall
					m_nLastStage = STALL;
					m_nCurStage = EX;
					if( next ) next->Stall();
					return;
				}
				m_nA = GetRegData(pInst->m_inst.inst.r.rs);
				m_nImm = GetImm();
			}
			switch( pInst->m_key ) {
			case LW:
			case SW:
				simulator.EXMEM.ALUOutput = m_nA + m_nImm;
				break;

			case ADDI:
				simulator.EXMEM.ALUOutput = m_nA + m_nImm;
				SetRegForward(pInst->m_inst.inst.r.rt, simulator.EXMEM.ALUOutput);
				break;

			case SUBI:
				simulator.EXMEM.ALUOutput = m_nA - m_nImm;
				SetRegForward(pInst->m_inst.inst.r.rt, simulator.EXMEM.ALUOutput);
				break;

			case MULI:
			case MUTI:
				m_nCurMulCycle++;
				if( (UINT)m_nCurMulCycle < simulator.m_nMulDelay ) {
					// go to next EX cycle
					m_nLastStage = EX;
					m_nCurStage = EX;
				} else {
					simulator.MUL_EXMEM.ALUOutput = m_nA * m_nImm;
					simulator.MUL_EXMEM.IR = pInst;
					SetRegForward(pInst->m_inst.inst.r.rd, simulator.MUL_EXMEM.ALUOutput);
				}
				break;

			case DIVI:
				if( !m_nCurDivCycle ) {
					// begin DIVI cycle
					// DIV line is not piped
					if( HasStructualHazards() ) {
						// structual hazards, stall
						m_nLastStage = STALL;
						m_nCurStage = EX;
						if( next ) next->Stall();
						return;
					}
				}
				m_nCurDivCycle++;
				if( (UINT)m_nCurDivCycle < simulator.m_nDivDelay ) {
					// go to next EX cycle
					m_nLastStage = EX;
					m_nCurStage = EX;
				} else {
					simulator.DIV_EXMEM.ALUOutput = m_nA / m_nImm;
					simulator.DIV_EXMEM.IR = pInst;
					SetRegForward(pInst->m_inst.inst.r.rd, simulator.DIV_EXMEM.ALUOutput);
				}
				break;

			case ANDI:
				simulator.EXMEM.ALUOutput = m_nA & m_nImm;
				SetRegForward(pInst->m_inst.inst.r.rt, simulator.EXMEM.ALUOutput);
				break;

			case ORI:
				simulator.EXMEM.ALUOutput = m_nA | m_nImm;
				SetRegForward(pInst->m_inst.inst.r.rt, simulator.EXMEM.ALUOutput);
				break;

			case XORI:
				simulator.EXMEM.ALUOutput = m_nA ^ m_nImm;
				SetRegForward(pInst->m_inst.inst.r.rt, simulator.EXMEM.ALUOutput);
				break;

			case BEQZ:
			case BNEZ:
				// For conditional branch BEQZ and BNEZ,
				// if we use Predicted-Not-Taken and result is taken,
				// make the following instruction IDLE
				if( simulator.m_nBranchMethod == CMIPSSimulator::kPredictedNotTaken &&
					m_bBranchTaken == TRUE )
					if( next ) next->Idle();
				break;

			case JR:
				// For unconditional branch JR,
				// if we use Predicted-Not-Taken,
				// make the following instruction IDLE
				if( simulator.m_nBranchMethod == CMIPSSimulator::kPredictedNotTaken )
					if( next ) next->Idle();
				break;
			// default: // do nothing
			}
			break;// TYPE_I

		case TYPE_J:
			if( pInst->m_key == TRAP )
				return;
			else if( pInst->m_key == J ) {
				// For unconditional branch J,
				// if we use Predicted-Not-Taken,
				// make the following instruction IDLE
				if( simulator.m_nBranchMethod == CMIPSSimulator::kPredictedNotTaken )
					if( next ) next->Idle();
				break;
			}
			break;// TYPE_J
		}
	}
}

// MEM
void CExecInst::stageMEM()
{
	if( m_bForward ) m_bForwardReady = TRUE;
	if( m_bStall ) {
		// stall this cycle, remain in stage MEM
		m_nLastStage = STALL;
		m_bStall = FALSE;
	} else if( m_bIdle ) {
		// clear cpu registers and go to next stage
		m_nLastStage = IDLE;
		m_nCurStage = WB;
		simulator.ClearMEMWBReg();
	} else {
		// put results into MEM/WB registers and
		// go to next stage
		m_nLastStage = MEM;
		m_nCurStage = WB;// Go to next cycle
		simulator.MEMWB.ALUOutput = simulator.EXMEM.ALUOutput;
		simulator.MEMWB.IR = pInst;
		simulator.MUL_MEMWB.ALUOutput = simulator.MUL_EXMEM.ALUOutput;
		simulator.MUL_MEMWB.IR = pInst;
		simulator.DIV_MEMWB.ALUOutput = simulator.DIV_EXMEM.ALUOutput;
		simulator.DIV_MEMWB.IR = pInst;
		if( pInst->m_key == LW ) {
			simulator.MEMWB.LMD = ReadMem(simulator.EXMEM.ALUOutput);
			SetRegForward(pInst->m_inst.inst.i.rt, simulator.MEMWB.LMD);
		} else if( pInst->m_key == SW ) {
			if( HasDataHazards(pInst->m_inst.inst.i.rt) ) {
				// This is actually RAW hazards
				m_nLastStage = STALL;
				m_nCurStage = MEM;
				if( next ) next->Stall();
				return;
			}
			// write memory
			WriteMem(simulator.EXMEM.ALUOutput,
				GetRegData(pInst->m_inst.inst.i.rt) );
		}
	}
}

void CExecInst::stageWB()
{
	if( m_bForward ) m_bForwardReady = TRUE;
	if( m_bStall ) {
		// stall this cycle, remain in stage WB
		m_nLastStage = STALL;
		m_bStall = FALSE;
	} else if( m_bIdle ) {
		// complete
		m_nLastStage = IDLE;
		m_nCurStage = COMPLETE;
	} else {
		// check if WAW hazards occur
		if( HasWAWHazards() ) {
			m_nLastStage = STALL;
			if( next ) next->Stall();
			return;
		}
		// put results into MEM/WB registers and
		// go to next stage
		m_nLastStage = WB;
		m_nCurStage = COMPLETE;// Go to next cycle
		switch( pInst->m_inst.type ) {
		case TYPE_R:
			if( pInst->m_key == MUL || pInst->m_key == MUT )
				SetRegContent(pInst->m_inst.inst.r.rd, simulator.MUL_MEMWB.ALUOutput);
			else if( pInst->m_key == DIV )
				SetRegContent(pInst->m_inst.inst.r.rd, simulator.DIV_MEMWB.ALUOutput);
			else
				SetRegContent(pInst->m_inst.inst.r.rd, simulator.MEMWB.ALUOutput);
			break;

		case TYPE_I:
			switch( pInst->m_key ) {
			case MULI:
			case MUTI:
				SetRegContent(pInst->m_inst.inst.i.rt, simulator.MUL_MEMWB.ALUOutput);
				break;
			case DIVI:
				SetRegContent(pInst->m_inst.inst.i.rt, simulator.DIV_MEMWB.ALUOutput);
				break;
			case ADDI:
			case SUBI:
			case ANDI:
			case ORI:
			case XORI:
				SetRegContent(pInst->m_inst.inst.i.rt, simulator.MEMWB.ALUOutput);
				break;
			case LW:
				SetRegContent(pInst->m_inst.inst.i.rt, simulator.MEMWB.LMD);
			}
			break;

		case TYPE_J:
			if( pInst->m_key == TRAP )
				//simulator.m_nState = CMIPSSimulator::kComplete;
				return;
			break;
		}
	}
}

// When this instruction execution complete...
void CExecInst::stageComplete()
{
	if( prev ) prev->next = next;
	if( next ) next->prev = prev;
	prev = next = NULL;
	// destroy itself
	delete this;
}

// check if it has structual hazards
// DIV line are not piped
BOOL CExecInst::HasStructualHazards()
{
	CExecInst* p = this->prev;
	while( p ) {
		if( (pInst->m_key == DIV || pInst->m_key == DIVI) &&
			(p->pInst) &&
			(p->pInst->m_key == DIV || p->pInst->m_key == DIVI) )
			// DIV or DIVI line has been hold
			return TRUE;
		p = p->prev;
	}
	return FALSE;
}

// check if it has data hazards
// if not, must be followed by GetRegData()
BOOL CExecInst::HasDataHazards(int src)
{
	m_bReadFromForward = FALSE;// reset
	if( simulator.reg[src].status == kWrite ) {
		CExecInst* p = this->prev;
		while( p ) {
			if( p->pInst && p->pInst->m_dest == src ) {
				if( p->m_bForwardReady ) {
					// forwarding
					m_bReadFromForward = TRUE;
					break;
				} else
					// has data hazards
					return TRUE;
			}
			p = p->prev;
		}
	}
	return FALSE;
}

// WAW Hazards, Write simutaneously
// stall in WB stage
BOOL CExecInst::HasWAWHazards()
{
	if( pInst->m_dest > 0 ) {
		CExecInst* p = this->prev;
		while( p ) {
			if( (p->pInst) &&
				(p->pInst->m_dest > 0 /*will write back*/) &&
				(p->m_nLastStage == WB) )
				return TRUE;
			p = p->prev;
		}
	}
	return FALSE;
}

