; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPipelineDoc
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pipeline.h"
LastPage=0

ClassCount=22
Class1=CAsmEditDoc
Class2=CAsmEditFrame
Class3=CMiniSQLView
Class4=CChildFrame
Class5=CExecInstCtrl
Class6=CMainFrame
Class7=CMemDlg
Class8=CPipelineApp
Class9=CAboutDlg
Class10=CPipelineDoc
Class11=CPipelineView
Class12=CRegDlg
Class13=CSimConfigDlg
Class14=CSimulatorDlg
Class15=CTextCtrl
Class16=CXPButton

ResourceCount=15
Resource1=IDR_PIPELITYPE
Resource2=IDD_RESET
Resource3=IDD_SIM_DLG
Resource4=IDR_PIPELITYPE_CNTR_IP
Resource5=IDD_CYCLE_FROM
Resource6=IDR_MAINFRAME
Resource7=IDR_CRYSTAL
Resource8=IDD_TRACE
Resource9=IDD_MEMDLG
Resource10=IDR_ASMTYPE
Class17=CMIPSPipelineDlg
Resource11=IDD_ABOUTBOX
Class18=CCycleDlg
Resource12=IDD_SIM_CONFIG
Class19=CTraceDlg
Resource13=IDD_MIPS_PIPELINE
Class20=CResetDlg
Resource14=IDD_REGDLG
Class21=CStatDlg
Class22=CIntegerDatapathCtrl
Resource15=IDD_STAT

[CLS:CAsmEditDoc]
Type=0
BaseClass=CDocument
HeaderFile=AsmEditDoc.h
ImplementationFile=AsmEditDoc.cpp

[CLS:CAsmEditFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=AsmEditFrame.h
ImplementationFile=AsmEditFrame.cpp

[CLS:CMiniSQLView]
Type=0
HeaderFile=AsmEditView.h
ImplementationFile=AsmEditView.cpp

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CExecInstCtrl]
Type=0
BaseClass=CWnd
HeaderFile=ExecInstCtrl.h
ImplementationFile=ExecInstCtrl.cpp
LastObject=CExecInstCtrl
Filter=W
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame

[CLS:CMemDlg]
Type=0
BaseClass=CDialog
HeaderFile=MemDlg.h
ImplementationFile=MemDlg.cpp

[CLS:CPipelineApp]
Type=0
BaseClass=CWinApp
HeaderFile=Pipeline.h
ImplementationFile=Pipeline.cpp
LastObject=CPipelineApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Pipeline.cpp
ImplementationFile=Pipeline.cpp
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[CLS:CPipelineDoc]
Type=0
BaseClass=CRichEditDoc
HeaderFile=PipelineDoc.h
ImplementationFile=PipelineDoc.cpp
LastObject=CPipelineDoc

[CLS:CPipelineView]
Type=0
BaseClass=CRichEditView
HeaderFile=PipelineView.h
ImplementationFile=PipelineView.cpp
LastObject=CPipelineView

[CLS:CRegDlg]
Type=0
BaseClass=CDialog
HeaderFile=RegDlg.h
ImplementationFile=RegDlg.cpp

[CLS:CSimConfigDlg]
Type=0
BaseClass=CDialog
HeaderFile=SimConfigDlg.h
ImplementationFile=SimConfigDlg.cpp

[CLS:CSimulatorDlg]
Type=0
BaseClass=CDialog
HeaderFile=SimulatorDlg.h
ImplementationFile=SimulatorDlg.cpp
LastObject=IDC_BTN_STOP
Filter=D
VirtualFilter=dWC

[CLS:CTextCtrl]
Type=0
BaseClass=CWnd
HeaderFile=TextCtrl.h
ImplementationFile=TextCtrl.cpp
LastObject=CTextCtrl

[CLS:CXPButton]
Type=0
BaseClass=CButton
HeaderFile=XPButton.h
ImplementationFile=XPButton.cpp

[DLG:IDD_MEMDLG]
Type=1
Class=CMemDlg
ControlCount=3
Control1=IDC_MEM_GRID,MFCGridCtrl,1350631424
Control2=IDC_RADIO_BIGENDING,button,1342177289
Control3=IDC_RADIO_LITTLEENDING,button,1342177289

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308492
Control2=IDOK,button,1342373889
Control3=IDC_STATIC_LUXIAOCHUN,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_REGDLG]
Type=1
Class=CRegDlg
ControlCount=3
Control1=IDC_REG_GRID,MFCGridCtrl,1350631424
Control2=IDC_RADIO_HEX,button,1342177289
Control3=IDC_RADIO_DEC,button,1342177289

[DLG:IDD_SIM_CONFIG]
Type=1
Class=CSimConfigDlg
ControlCount=27
Control1=IDC_RADIO_FREEZE,button,1342177289
Control2=IDC_RADIO_PREDICT_TOKEN,button,1342177289
Control3=IDC_RADIO_PREDICT_NOT_TOKEN,button,1342177289
Control4=IDC_RADIO_DELAYED_BRANCH,button,1342177289
Control5=IDC_RADIO_FORWARDING,button,1342177289
Control6=IDC_RADIO_NOT_FORWARDING,button,1342177289
Control7=IDC_SLIDER1,msctls_trackbar32,1342242840
Control8=IDC_SLIDER2,msctls_trackbar32,1342242840
Control9=IDC_SLIDER3,msctls_trackbar32,1342242840
Control10=IDOK,button,1342242816
Control11=IDCANCEL,button,1342242816
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT1,edit,1342244992
Control21=IDC_EDIT2,edit,1342244992
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_EDIT3,edit,1342244992
Control26=ID_BTN_MEM,button,1342242816
Control27=ID_BTN_REG,button,1342242816

[DLG:IDD_SIM_DLG]
Type=1
Class=CSimulatorDlg
ControlCount=14
Control1=IDC_BTN_CONFIGURE,button,1342242816
Control2=IDC_BTN_EDIT,button,1342242816
Control3=IDC_BTN_LOAD,button,1342242816
Control4=IDC_BTN_RESET,button,1342242816
Control5=IDC_BTN_STEP_FORWARD,button,1342242816
Control6=IDC_BTN_STEP_BACK,button,1342242816
Control7=IDC_BTN_NEXT_CYCLE,button,1342242816
Control8=IDC_BTN_PREVIOUS_CYCLE,button,1342242816
Control9=IDC_BTN_GO,button,1342242816
Control10=IDC_BTN_STAT,button,1342242816
Control11=IDC_BTN_QUIT,button,1342242816
Control12=IDC_BTN_TRACE,button,1342242816
Control13=IDC_ASM_TEXT,static,1342177287
Control14=IDC_BTN_STOP,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_ASMTYPE]
Type=1
Class=?
Command1=ID_ASM_FILE_NEW
Command2=ID_ASM_FILE_OPEN
Command3=ID_ASM_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
CommandCount=6

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

[MNU:IDR_PIPELITYPE]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[MNU:IDR_PIPELITYPE_CNTR_IP]
Type=1
Class=?
Command1=ID_FILE_SAVE
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

[MNU:IDR_CRYSTAL]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_REDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_SELECT_ALL
CommandCount=6

[MNU:IDR_ASMTYPE]
Type=1
Class=?
Command1=ID_ASM_FILE_NEW
Command2=ID_ASM_FILE_OPEN
Command3=ID_ASM_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_PASTE_SPECIAL
Command10=ID_EDIT_SELECT_ALL
Command11=ID_EDIT_FIND
Command12=ID_EDIT_REPEAT
Command13=ID_EDIT_REPLACE
Command14=ID_APP_ABOUT
CommandCount=14

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_SELECT_ALL
Command2=ID_EDIT_COPY
Command3=ID_EDIT_FIND
Command4=ID_EDIT_REPLACE
Command5=ID_FILE_NEW
Command6=ID_FILE_OPEN
Command7=ID_FILE_PRINT
Command8=ID_FILE_SAVE
Command9=ID_EDIT_PASTE
Command10=ID_CANCEL_EDIT_CNTR
Command11=ID_EDIT_REPEAT
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_OLE_EDIT_PROPERTIES
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[ACL:IDR_PIPELITYPE_CNTR_IP]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

[ACL:IDR_ASMTYPE]
Type=1
Class=?
Command1=ID_ASM_FILE_NEW
Command2=ID_ASM_FILE_OPEN
Command3=ID_ASM_FILE_SAVE
CommandCount=3

[DLG:IDD_MIPS_PIPELINE]
Type=1
Class=CMIPSPipelineDlg
ControlCount=3
Control1=IDC_EXECINST_CTRL,static,1342177287
Control2=IDC_COPYRIGHT,static,1342308352
Control3=IDC_DATAPATH,static,1342177287

[CLS:CMIPSPipelineDlg]
Type=0
HeaderFile=MIPSPipelineDlg.h
ImplementationFile=MIPSPipelineDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMIPSPipelineDlg
VirtualFilter=dWC

[DLG:IDD_CYCLE_FROM]
Type=1
Class=CCycleDlg
ControlCount=5
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=ID_BTN_DEFAULT,button,1342242816
Control4=IDC_STATIC,static,1342308353
Control5=IDC_EDIT1,edit,1350639745

[CLS:CCycleDlg]
Type=0
HeaderFile=CycleDlg.h
ImplementationFile=CycleDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_BTN_DEFAULT
VirtualFilter=dWC

[DLG:IDD_TRACE]
Type=1
Class=CTraceDlg
ControlCount=4
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631553
Control4=IDC_STATIC,static,1342308352

[CLS:CTraceDlg]
Type=0
HeaderFile=TraceDlg.h
ImplementationFile=TraceDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTraceDlg
VirtualFilter=dWC

[DLG:IDD_RESET]
Type=1
Class=CResetDlg
ControlCount=5
Control1=ID_BTN_ALL,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=ID_BTN_PROGRAM,button,1342242816
Control4=ID_BTN_CONFIG,button,1342242816
Control5=ID_BTN_RESTART,button,1342242816

[CLS:CResetDlg]
Type=0
HeaderFile=ResetDlg.h
ImplementationFile=ResetDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_BTN_RESTART

[DLG:IDD_STAT]
Type=1
Class=CStatDlg
ControlCount=1
Control1=IDC_STAT,MFCGridCtrl,1350631424

[CLS:CStatDlg]
Type=0
HeaderFile=StatDlg.h
ImplementationFile=StatDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CStatDlg
VirtualFilter=dWC

[CLS:CIntegerDatapathCtrl]
Type=0
HeaderFile=IntegerDatapathCtrl.h
ImplementationFile=IntegerDatapathCtrl.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CIntegerDatapathCtrl

