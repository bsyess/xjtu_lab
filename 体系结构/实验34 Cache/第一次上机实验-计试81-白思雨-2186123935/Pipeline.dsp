# Microsoft Developer Studio Project File - Name="Pipeline" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Pipeline - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Pipeline.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Pipeline.mak" CFG="Pipeline - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Pipeline - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Pipeline - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Pipeline - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../bin/MIPS Simulator.exe"

!ELSEIF  "$(CFG)" == "Pipeline - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../bin/MIPS Simulator - debug version.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Pipeline - Win32 Release"
# Name "Pipeline - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AsmEditDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AsmEditFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\AsmEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\AsmInstruction.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\CycleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Error.cpp
# End Source File
# Begin Source File

SOURCE=.\ExecInstCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\hyperlink.cpp
# End Source File
# Begin Source File

SOURCE=.\IntegerDatapathCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\LexAnalyzer.cpp
# End Source File
# Begin Source File

SOURCE=.\line.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MIPSAsmGrammar.cpp
# End Source File
# Begin Source File

SOURCE=.\MIPSPipelineDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MIPSSimulator.cpp
# End Source File
# Begin Source File

SOURCE=.\Pipeline.cpp
# End Source File
# Begin Source File

SOURCE=.\Pipeline.rc
# End Source File
# Begin Source File

SOURCE=.\PipelineDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PipelineView.cpp
# End Source File
# Begin Source File

SOURCE=.\RegDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SimConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SimulatorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TextCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Tokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\TraceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XPButton.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AsmEditDoc.h
# End Source File
# Begin Source File

SOURCE=.\AsmEditFrame.h
# End Source File
# Begin Source File

SOURCE=.\AsmEditView.h
# End Source File
# Begin Source File

SOURCE=.\AsmInstruction.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\CycleDlg.h
# End Source File
# Begin Source File

SOURCE=.\Error.h
# End Source File
# Begin Source File

SOURCE=.\ExecInstCtrl.h
# End Source File
# Begin Source File

SOURCE=.\hyperlink.h
# End Source File
# Begin Source File

SOURCE=.\IntegerDatapathCtrl.h
# End Source File
# Begin Source File

SOURCE=.\LexAnalyzer.h
# End Source File
# Begin Source File

SOURCE=.\line.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MemDlg.h
# End Source File
# Begin Source File

SOURCE=.\MIPSPipelineDlg.h
# End Source File
# Begin Source File

SOURCE=.\MIPSSimulator.h
# End Source File
# Begin Source File

SOURCE=.\Pipeline.h
# End Source File
# Begin Source File

SOURCE=.\PipelineDoc.h
# End Source File
# Begin Source File

SOURCE=.\PipelineView.h
# End Source File
# Begin Source File

SOURCE=.\RegDlg.h
# End Source File
# Begin Source File

SOURCE=.\ResetDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SimConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\SimulatorDlg.h
# End Source File
# Begin Source File

SOURCE=.\StatDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TextCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Tokenizer.h
# End Source File
# Begin Source File

SOURCE=.\TraceDlg.h
# End Source File
# Begin Source File

SOURCE=.\XPButton.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\res\asmtype.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_pipe.ico
# End Source File
# Begin Source File

SOURCE=.\res\Pipeline.ico
# End Source File
# Begin Source File

SOURCE=.\res\Pipeline.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PipelineDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "GridCtrl"

# PROP Default_Filter "*.h *.cpp"
# Begin Source File

SOURCE=.\GridCtrl\CellRange.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\ComboGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\ComboGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\InPlaceList.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\InPlaceList.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\TitleTip.h
# End Source File
# End Group
# Begin Group "Crystal"

# PROP Default_Filter "*.h *.cpp"
# Begin Source File

SOURCE=.\Crystal\CCrystalEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalEditView.h
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalEditView.inl
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextBuffer.h
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextBuffer.inl
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextView.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextView.h
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextView.inl
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextView2.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CEDEFS.H
# End Source File
# Begin Source File

SOURCE=.\Crystal\CEditReplaceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CEditReplaceDlg.h
# End Source File
# Begin Source File

SOURCE=.\Crystal\CFindTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CFindTextDlg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
