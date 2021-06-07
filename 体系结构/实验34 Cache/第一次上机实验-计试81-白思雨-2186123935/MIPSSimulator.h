#if !defined(AFX_MIPSSIMULATOR_H__326A7887_14EC_4B1A_BC5D_F261892FAB90__INCLUDED_)
#define AFX_MIPSSIMULATOR_H__326A7887_14EC_4B1A_BC5D_F261892FAB90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MIPSSimulator.h : header file
//
#include <afxtempl.h>
#include "AsmInstruction.h"

//
// CLASS CSlot
enum
{
	kReady,	kWrite
};

class CSlot {
public:
	CSlot() : content(0), forward(0), 
		status(kReady), write_count(0) {}
	~CSlot() {}

public:
	int content, forward, status, write_count;
};

// MIPS Pipeline stages control
enum
{
	IF, ID, EX, MEM, WB, STALL, IDLE, COMPLETE
};

extern CString MIPSStage[];
typedef CArray<UINT, UINT> UINT_ARRAY;

//
// CLASS CMIPSSimulator
class CExecInst;// forward

class CMIPSSimulator
{
public:
	CMIPSSimulator();
	~CMIPSSimulator();

public:
	// Execution
	void Start();
	void NextCycle();
	void PrevCycle();
	void CycleTo( int cycle );

	BOOL IsExecComplete();
	int  GetCurCycle();
	int  GetCurStep();
	BOOL GetStageArray( CExecInst* pExecInst, UINT_ARRAY& outStageArray );
	BOOL HasNewStep();
	CExecInst* GetNewExecInst();
	BOOL HasInstComplete(UINT_ARRAY& outCompleteArray);
	BOOL HasIdleInstComplete();

public:
	BOOL LoadInstFromFile( LPCTSTR pathname );
	BOOL Trace( LPCTSTR pathname );
	void StopTrace();
	BOOL IsReadyForExec();

	void Reset();
	void ResetProgram();
	void CreateDataMem();
	void ClearDataMem();
	void FreeDataMem();

	void BackupMem();
	void RollBackMem();
	void BackupReg();
	void RollBackReg();
	void RollBackToStartState();

	void ClearIFIDReg();
	void ClearIDEXReg();
	void ClearEXMEMReg();
	void ClearMUL_EXMEMReg();
	void ClearDIV_EXMEMReg();
	void ClearMEMWBReg();
	void ClearMUL_MEMWBReg();
	void ClearDIV_MEMWBReg();

	BOOL SetPC(UINT address);
	CAsmInstruction* FetchInst();

	int  FindIndexFromAddress( UINT address );

private:
	// Help routines
	void AsignAddress();
	int  FindTargetAddress( CString& target );
	void ResolveLabels();
	void CalcStat(CAsmInstruction* pInst);

public:
	CInstructions* m_pInsts;
	CExecInst*	m_pExecInsts;// It's relied on m_pInsts;

	CFile		m_TraceFile;
	BOOL		m_bTrace;
	BOOL		m_bNewStep;

	/****************************************
	 * Configurations
	 ****************************************/
	// Execution mode: Forwarding enable or disable
	BOOL m_bForwardingEnable;
	// Branch hazards - Four strategies:
	// Freeze(or Flush), Predicted-taken, Predicted-not-taken, Delayed
	// NOTE: On MIPS 5-stage integer pipeline, 
	// Freeze(or Flush) and Predicted-taken are the same
	enum {
		kFreeze,
		kPredictedTaken,
		kPredictedNotTaken,
		kDelayedBranch
	};
	UINT m_nBranchMethod;
	// MIPS CPU STATE
	enum {
		kNone,
		kRun,
		kComplete
	};
	UINT m_nState;
	// delays (stages or cycles)
	UINT m_nAddDelay;
	UINT m_nMulDelay;
	UINT m_nDivDelay;
	// ALU numbers
	UINT m_nAddNum;
	UINT m_nMulNum;
	UINT m_nDivNum;
	// is ALU pipelined?
	BOOL m_bAddPipelined;
	BOOL m_bMulPipelined;
	BOOL m_bDivPipelined;
	// memory
	UINT m_nMemSize;
	UINT m_nDataSize;
	BOOL m_bBigEnding;
	// end of configurations

	/****************************************
	 * MIPS CPU Hardware simulator
	 ****************************************/
	int*  data;
	int*  data_bak;
	int	  reg_bak[32];
	CSlot reg[32];

	UINT PC;
	UINT m_nStartPC;
	UINT m_nLastPC;

	// MIPS CPU Registers
	// IF/ID
	struct {
		int	NPC;
		CAsmInstruction* IR;
	} IFID;
	// ID/EX
	struct {
		int A;
		int B;
		int Imm;
		CAsmInstruction* IR;
	} IDEX;
	// EX/MEM
	struct {
		int ALUOutput;
		int B;
		CAsmInstruction* IR;
	} EXMEM/*integer*/, MUL_EXMEM, DIV_EXMEM;
	// MEMWB
	struct {
		int ALUOutput;
		int LMD;
		CAsmInstruction* IR;
	} MEMWB/*integer*/, MUL_MEMWB, DIV_MEMWB;
	// end of MIPS CPU Hardware simulator

	// Statistics
	struct {
		int nLW, nSW;
		int nADD, nSUB, nMUT, nMUL, nDIV;
		int nAND, nOR, nXOR;
		int nADDI, nSUBI, nMUTI, nMULI, nDIVI;
		int nANDI, nORI, nXORI;
		int nBEQZ, nBNEZ, nJ, nJR, nTRAP, nNOP;
		int cycles, steps;
	} STAT;
};// End of CMIPSSimulator

/**********************************************
 * Global
 **********************************************/
extern CMIPSSimulator simulator;





//
// CLASS CExecInst
class CExecInst
{
friend class CMIPSSimulator;
public:
	CExecInst( int cycle, CAsmInstruction* inst = NULL,
		CExecInst* prev = NULL, CExecInst* next = NULL );
	~CExecInst();

	void NextCycle();

private:
	// Can only be called in the class
	void Stall();
	void Idle();
	void FetchInst();
	void Freeze();

	// MIPS Registers access
	int  GetRegContent(UINT reg);
	int  GetRegForward(UINT reg);
	int  GetRegStatus(UINT reg);
	int  GetRegData(UINT reg);
	void SetRegContent(UINT reg, int content);
	void SetRegForward(UINT reg, int forward);
	void SetRegStatus(UINT reg, int status);
	int  GetImm();

	// MIPS Memory access
	int  ReadMem(UINT address);
	void WriteMem(UINT address, int content);

	// Stages
	void stageIF();
	void stageID();
	void stageEX();
	void stageMEM();
	void stageWB();
	void stageComplete();

	BOOL HasStructualHazards();
	BOOL HasDataHazards(int src);
	BOOL HasWAWHazards();

	// attributes
public:
	COLORREF color;
	CAsmInstruction* pInst;

	int  m_nStartCycle;
	int  m_nCurCycle;
	int  m_nCurMulCycle;
	int  m_nCurDivCycle;
	UINT m_nCurStage;
	UINT m_nLastStage;

	CExecInst* prev;
	CExecInst* next;

private:
	BOOL m_bForward;
	BOOL m_bForwardReady;
	BOOL m_bReadFromForward;

	BOOL m_bBranchTaken;
	BOOL m_bStall;
	BOOL m_bIdle;

	// used in long-cycle pipeline, like MUL, DIV...
	int  m_nA;
	int	 m_nB;
	int  m_nImm;
};// End of CExecInst

#endif // !defined(AFX_MIPSSIMULATOR_H__326A7887_14EC_4B1A_BC5D_F261892FAB90__INCLUDED_)
