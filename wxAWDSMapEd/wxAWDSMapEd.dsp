# Microsoft Developer Studio Project File - Name="wxAWDSMapEd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=wxAWDSMapEd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wxAWDSMapEd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wxAWDSMapEd.mak" CFG="wxAWDSMapEd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wxAWDSMapEd - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "wxAWDSMapEd - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wxAWDSMapEd - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "resource" /I "$(WX280)/contrib/include" /I "$(WX280)/include/msvc" /I "$(WX280)/include" /I "$(WX280)/lib/vc_lib/msw/wx" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"precomp.h" /FD /Zm600 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comctl32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib wxbase28.lib wxbase28_net.lib wxbase28_xml.lib wxexpat.lib wxjpeg.lib wxmsw28_adv.lib wxmsw28_core.lib wxmsw28_html.lib wxmsw28_media.lib wxmsw28_xrc.lib wxpng.lib wxregex.lib wxtiff.lib wxzlib.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcmt" /out:"bin/AWSMapEditor.exe" /libpath:"$(WX280)/lib/vc_lib"
# SUBTRACT LINK32 /incremental:yes /map

!ELSEIF  "$(CFG)" == "wxAWDSMapEd - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "resource" /I "$(WX280)/contrib/include" /I "$(WX280)/include/msvc" /I "$(WX280)/include" /I "$(WX280)/lib/vc_lib/msw/wx" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"precomp.h" /FD /GZ /Zm600 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comctl32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib winmm.lib wxbase28d.lib wxbase28d_net.lib wxbase28d_xml.lib wxexpatd.lib wxjpegd.lib wxmsw28d_adv.lib wxmsw28d_core.lib wxmsw28d_html.lib wxmsw28d_media.lib wxmsw28d_xrc.lib wxpngd.lib wxregexd.lib wxtiffd.lib wxzlibd.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"msvcrt msvcrtd libcmtd" /out:"bin/AWSMapEditord.exe" /pdbtype:sept /libpath:"$(WX280)/lib/vc_lib"
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "wxAWDSMapEd - Win32 Release"
# Name "wxAWDSMapEd - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Source\AppMain.cpp

!IF  "$(CFG)" == "wxAWDSMapEd - Win32 Release"

!ELSEIF  "$(CFG)" == "wxAWDSMapEd - Win32 Debug"

# ADD CPP /I "../resource"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Source\DialogInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\DialogPreferences.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\DialogSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\DialogStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\DrawPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Element.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FrameMain.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Map.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Page.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\precomp.cpp
# ADD CPP /Yc"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\Resource\resource.rc
# ADD BASE RSC /l 0x416 /i "Resource"
# ADD RSC /l 0x416 /i "Resource" /i "$(WX263)/include"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Source\AppMain.h
# End Source File
# Begin Source File

SOURCE=.\Source\DialogInformation.h
# End Source File
# Begin Source File

SOURCE=.\Source\DialogPreferences.h
# End Source File
# Begin Source File

SOURCE=.\Source\DialogSettings.h
# End Source File
# Begin Source File

SOURCE=.\Source\DialogStatus.h
# End Source File
# Begin Source File

SOURCE=.\Source\DrawPanel.h
# End Source File
# Begin Source File

SOURCE=.\Source\DrawPanel_spritesheets.h
# End Source File
# Begin Source File

SOURCE=.\Source\Element.h
# End Source File
# Begin Source File

SOURCE=.\Source\Element_Defaults.h
# End Source File
# Begin Source File

SOURCE=.\Source\FrameMain.h
# End Source File
# Begin Source File

SOURCE=.\Source\Map.h
# End Source File
# Begin Source File

SOURCE=.\Source\Page.h
# End Source File
# Begin Source File

SOURCE=.\Source\precomp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Resource\application.manifest
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\blank.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\bullseye.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\cdrom.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\colours.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\computer.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\cross.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\csquery.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\drive.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\file1.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\floppy.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\folder1.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\folder2.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\hand.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\magnif1.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\pbrush.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\pencil.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\pntleft.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\pntright.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\removble.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\rightarr.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\roller.cur
# End Source File
# Begin Source File

SOURCE=.\Resource\wx\msw\wx.manifest
# End Source File
# Begin Source File

SOURCE=.\Resource\wxAWDSMapEd.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\wxAWDSMapFile.ico
# End Source File
# End Group
# End Target
# End Project
